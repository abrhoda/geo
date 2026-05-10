#if !defined(GEO_TMPL_TYPE)
#error "GEO_TMPL_TYPE undefined and required to be set."
#else

#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

/*
 * macros to expand struct names and function names with a GEO_TMPL_TYPE suffix
 */
#define TMPL_CONCAT2(a, b) a##_##b
#define TMPL_CONCAT(a, b) TMPL_CONCAT2(a, b)

#define TMPL_POINT TMPL_CONCAT(GeoPoint, GEO_TMPL_TYPE)
#define TMPL_SEGMENT TMPL_CONCAT(GeoSegment, GEO_TMPL_TYPE)
#define TMPL_GEOMETRY TMPL_CONCAT(GeoGeometry, GEO_TMPL_TYPE)
#define TMPL_FUNC(name) TMPL_CONCAT(name, GEO_TMPL_TYPE)

/******************************************************************************
 * GEO_INTEGER_TEMPLATE DEFINITIONS
 *****************************************************************************/

struct TMPL_POINT {
  GEO_TMPL_TYPE x;
  GEO_TMPL_TYPE y;
};

struct TMPL_SEGMENT {
  struct TMPL_POINT* start;
  struct TMPL_POINT* end;
};

struct TMPL_GEOMETRY {
  struct TMPL_SEGMENT** segments;
  size_t segments_count;
};

enum GeoResult {
  GEO_SUCCESS = 0,
  GEO_ERR_NULL_POINTER = 1,
  GEO_ERR_TOO_SMALL = 2,
  GEO_ERR_OVERFLOW = 3  // unused for now
};

enum GeoOrientation { RIGHT = -1, COLINEAR = 0, LEFT = 1 };

// public forward declaration
enum GeoResult TMPL_FUNC(geo_points_equal)(struct TMPL_POINT const* lhs,
                                            struct TMPL_POINT const* rhs,
                                            bool* is_equal);
enum GeoResult TMPL_FUNC(geo_segments_intersect)(
    struct TMPL_SEGMENT const* segment1, struct TMPL_SEGMENT const* segment2,
    size_t* intersect_count);

enum GeoResult TMPL_FUNC(geo_geometry_is_closed)(
    struct TMPL_GEOMETRY const* geometry, bool* is_closed);
enum GeoResult TMPL_FUNC(geo_geometry_is_simple)(
    struct TMPL_GEOMETRY const* geometry, bool* is_closed);
enum GeoResult TMPL_FUNC(geo_point_in_geometry)(
    struct TMPL_POINT const* point, struct TMPL_GEOMETRY const* geometry,
    bool strict, bool* is_inside);
enum GeoResult TMPL_FUNC(geo_geometry_in_geometry)(
    struct TMPL_GEOMETRY* parent, struct TMPL_GEOMETRY* child, bool strict,
    bool* is_inside);
enum GeoResult TMPL_FUNC(geo_convex_hull)(struct TMPL_POINT** points,
                                           struct TMPL_POINT** convex_hull,
                                           size_t size,
                                           size_t* convex_hull_size);
#ifdef __cplusplus
}
#endif

/*****************************************************************************
 * GEO_INTEGER_TEMPLATE IMPLEMENTATION
 *****************************************************************************/

#ifdef TMPL_IMPL
// private definitions

inline static GEO_TMPL_TYPE dot_product(struct TMPL_POINT const* const vec_ab,
                                        struct TMPL_POINT const* const vec_ac) {
  /* TODO handle overflow */
  return ((vec_ab->x * vec_ac->x) + (vec_ab->y * vec_ac->y));
}

inline static GEO_TMPL_TYPE cross_product(
    struct TMPL_POINT const* const vec_ab,
    struct TMPL_POINT const* const vec_ac) {
  /* TODO handle overflow */
  return (vec_ab->x * vec_ac->y) - (vec_ab->y * vec_ac->x);
}

static enum GeoOrientation orientation(struct TMPL_POINT const* const start,
                                        struct TMPL_POINT const* const end,
                                        struct TMPL_POINT const* const point) {
  struct TMPL_POINT vec_ab = {.x = end->x - start->x, .y = end->y - start->y};
  struct TMPL_POINT vec_ac = {.x = point->x - start->x,
                              .y = point->y - start->y};
  GEO_TMPL_TYPE cross = cross_product(&vec_ab, &vec_ac);
  if (cross == 0) {
    return COLINEAR;
  }
  return cross < 0 ? RIGHT : LEFT;
}

static bool in_disk(struct TMPL_SEGMENT const* const segment,
                    struct TMPL_POINT const* const point) {
  struct TMPL_POINT vec_ap = {.x = segment->start->x - point->x,
                              .y = segment->start->y - point->y};
  struct TMPL_POINT vec_bp = {.x = segment->end->x - point->x,
                              .y = segment->end->y - point->y};
  return dot_product(&vec_ap, &vec_bp) <= 0;
}

static GEO_TMPL_TYPE squared_distance(struct TMPL_POINT const* const point1,
                                      struct TMPL_POINT const* const point2) {
  GEO_TMPL_TYPE diff_x = point2->x - point1->x;
  GEO_TMPL_TYPE diff_y = point2->y - point1->y;
  /* TODO handle overflow */
  return (diff_x * diff_x) + (diff_y * diff_y);
}

static struct TMPL_POINT* global_start_point;
static int compare(const void* first, const void* second) {
  const struct TMPL_POINT* vec_end = *(const struct TMPL_POINT* const*)first;
  const struct TMPL_POINT* point = *(const struct TMPL_POINT* const*)second;
  enum GeoOrientation orientation_p =
      orientation(global_start_point, vec_end, point);

  if (orientation_p == COLINEAR) {
    int distance = (squared_distance(global_start_point, point) >=
                    squared_distance(global_start_point, vec_end));
    return distance == 1 ? -1 : 1;
  }

  /* turn RIGHT into a positive and LEFT into negative to sort properly */
  return -1 * orientation_p;
}

// public definitions
enum GeoResult TMPL_FUNC(geo_points_equal)(struct TMPL_POINT const* lhs,
                                            struct TMPL_POINT const* rhs,
                                            bool* is_equal) {
#ifndef GEO_UNSAFE
  if (lhs == NULL || rhs == NULL) {
    return GEO_ERR_NULL_POINTER;
  }
#endif
  *is_equal = (lhs->x == rhs->x) && (lhs->y == rhs->y);
  return GEO_SUCCESS;
}

enum GeoResult TMPL_FUNC(geo_segments_intersect)(
    struct TMPL_SEGMENT const* const segment1,
    struct TMPL_SEGMENT const* const segment2, size_t* intersect_count) {
  enum GeoOrientation orientation_a;
  enum GeoOrientation orientation_b;
  enum GeoOrientation orientation_c;
  enum GeoOrientation orientation_d;
#ifndef GEO_UNSAFE
  if (segment1 == NULL || segment2 == NULL || segment1->start == NULL ||
      segment1->end == NULL || segment2->start == NULL ||
      segment2->end == NULL) {
    return GEO_ERR_NULL_POINTER;
  }
#endif
  orientation_a = orientation(segment2->start, segment2->end, segment1->start);
  orientation_b = orientation(segment2->start, segment2->end, segment1->end);
  orientation_c = orientation(segment1->start, segment1->end, segment2->start);
  orientation_d = orientation(segment1->start, segment1->end, segment2->end);

  if ((orientation_a * orientation_b < 0) &&
      (orientation_c * orientation_d < 0)) {
    *intersect_count = 1;
    return GEO_SUCCESS;
  }

  *intersect_count = 0;
  if (orientation_a == COLINEAR && in_disk(segment2, segment1->start)) {
    ++(*intersect_count);
  }
  if (orientation_b == COLINEAR && in_disk(segment2, segment1->end)) {
    ++(*intersect_count);
  }
  if (orientation_c == COLINEAR && in_disk(segment1, segment2->start)) {
    ++(*intersect_count);
  }
  if (orientation_d == COLINEAR && in_disk(segment1, segment2->end)) {
    ++(*intersect_count);
  }

  return GEO_SUCCESS;
}

enum GeoResult TMPL_FUNC(geo_geometry_is_closed)(
    struct TMPL_GEOMETRY const* geometry, bool* is_closed) {
  enum GeoResult result = GEO_SUCCESS;
  size_t mod = 0;
#ifndef GEO_UNSAFE
  if (geometry == NULL || geometry->segments == NULL) {
    return GEO_ERR_NULL_POINTER;
  }

  if (geometry->segments_count < 3) {
    return GEO_ERR_TOO_SMALL;
  }
#endif

  for (size_t iter = 0; iter < geometry->segments_count; ++iter) {
    mod = (iter + 1) % geometry->segments_count;
    result =
        TMPL_FUNC(geo_points_equal)(geometry->segments[iter]->end,
                                    geometry->segments[mod]->start, is_closed);

#ifndef GEO_UNSAFE
    if (result != GEO_SUCCESS) {
      return result;
    }
#endif
    if (!(*is_closed)) {
      return GEO_SUCCESS;
    }
  }
  return GEO_SUCCESS;
}

enum GeoResult TMPL_FUNC(geo_geometry_is_simple)(
    struct TMPL_GEOMETRY const* geometry, bool* is_simple) {
  enum GeoResult result = GEO_SUCCESS;
  size_t intersections = 0;
#ifndef GEO_UNSAFE
  if (geometry == NULL || geometry->segments == NULL) {
    return GEO_ERR_NULL_POINTER;
  }

  if (geometry->segments_count < 3) {
    return GEO_ERR_TOO_SMALL;
  }
#endif
  // check that the first and second segments intersect
  result = TMPL_FUNC(geo_segments_intersect)(
      geometry->segments[0], geometry->segments[1], &intersections);

#ifndef GEO_UNSAFE
  if (result != GEO_SUCCESS) {
    return result;
  }
#endif
  if (intersections != 2) {
    *is_simple = false;
    return GEO_SUCCESS;
  }

  // check that the first and last segments intersect
  result = TMPL_FUNC(geo_segments_intersect)(
      geometry->segments[0], geometry->segments[geometry->segments_count - 1],
      &intersections);

#ifndef GEO_UNSAFE
  if (result != GEO_SUCCESS) {
    return result;
  }
#endif
  if (intersections != 2) {
    *is_simple = false;
    return GEO_SUCCESS;
  }

  // no other segments intersect with the first.
  for (size_t i = 2; i < geometry->segments_count - 1; ++i) {
    result = TMPL_FUNC(geo_segments_intersect)(
        geometry->segments[0], geometry->segments[i], &intersections);

#ifndef GEO_UNSAFE
    if (result != GEO_SUCCESS) {
      return result;
    }
#endif
    if (intersections != 0) {
      *is_simple = false;
      return GEO_SUCCESS;
    }
  }

  for (size_t i = 1; i < geometry->segments_count - 1; ++i) {
    result = TMPL_FUNC(geo_segments_intersect)(
        geometry->segments[i], geometry->segments[i + 1], &intersections);

#ifndef GEO_UNSAFE
    if (result != GEO_SUCCESS) {
      return result;
    }
#endif
    if (intersections != 2) {
      *is_simple = false;
      return GEO_SUCCESS;
    }
    for (size_t j = (i + 2); j < geometry->segments_count; ++j) {
      result = TMPL_FUNC(geo_segments_intersect)(
          geometry->segments[i], geometry->segments[j], &intersections);
#ifndef GEO_UNSAFE
      if (result != GEO_SUCCESS) {
        return result;
      }
#endif
      if (intersections != 0) {
        *is_simple = false;
        return GEO_SUCCESS;
      }
    }
  }
  *is_simple = true;
  return GEO_SUCCESS;
}

enum GeoResult TMPL_FUNC(geo_point_in_geometry)(
    struct TMPL_POINT const* point, struct TMPL_GEOMETRY const* geometry,
    bool strict, bool* is_inside) {
  size_t intersections = 0;
  enum GeoOrientation orientation_p;
#ifndef GEO_UNSAFE
  if (geometry == NULL || geometry->segments == NULL || point == NULL) {
    return GEO_ERR_NULL_POINTER;
  }

  if (geometry->segments_count < 3) {
    return GEO_ERR_TOO_SMALL;
  }
#endif
  for (size_t iter = 0; iter < geometry->segments_count; ++iter) {
#ifndef GEO_UNSAFE
    if (geometry->segments[iter] == NULL ||
        geometry->segments[iter]->start == NULL ||
        geometry->segments[iter]->end == NULL) {
      return GEO_ERR_NULL_POINTER;
    }
#endif

    orientation_p = orientation(geometry->segments[iter]->start,
                                geometry->segments[iter]->end, point);
    if (orientation_p == COLINEAR && in_disk(geometry->segments[iter], point)) {
      *is_inside = !strict;
      return GEO_SUCCESS;
    }
    /*
     * checks that a ray from `point` bisects the segment and that the
     * orientation puts the `point` on the appropriate side of the
     * `segment`.
     */
    intersections += (((geometry->segments[iter]->end->y >= point->y) -
                       (geometry->segments[iter]->start->y >= point->y)) *
                      orientation_p) > 0;
  }
  *is_inside = intersections & 1;
  return GEO_SUCCESS;
}

enum GeoResult TMPL_FUNC(geo_geometry_in_geometry)(
    struct TMPL_GEOMETRY* parent, struct TMPL_GEOMETRY* child, bool strict,
    bool* is_inside) {
  enum GeoResult result = GEO_SUCCESS;
#ifndef GEO_UNSAFE
  if (parent == NULL || parent->segments == NULL || child == NULL ||
      child->segments == NULL) {
    return GEO_ERR_NULL_POINTER;
  }

  if (parent->segments_count < 3 || child->segments_count < 3) {
    return GEO_ERR_TOO_SMALL;
  }
#endif
  for (size_t iter = 0; iter < child->segments_count; ++iter) {
#ifndef GEO_UNSAFE
    if (child->segments[iter] == NULL) {
      return GEO_ERR_NULL_POINTER;
    }
#endif
    result = TMPL_FUNC(geo_point_in_geometry)(child->segments[iter]->start,
                                              parent, strict, is_inside);
    if (result != GEO_SUCCESS) {
      return result;
    }

    if (!(*is_inside)) {
      return GEO_SUCCESS;
    }
    result = TMPL_FUNC(geo_point_in_geometry)(child->segments[iter]->end,
                                              parent, strict, is_inside);
    if (result != GEO_SUCCESS) {
      return result;
    }

    if (!(*is_inside)) {
      return GEO_SUCCESS;
    }
  }
  return GEO_SUCCESS;
}

enum GeoResult TMPL_FUNC(geo_convex_hull)(struct TMPL_POINT** points,
                                           struct TMPL_POINT** convex_hull,
                                           size_t size,
                                           size_t* convex_hull_size) {
  /* used to find starting point */
  size_t min_idx = 0;
  GEO_TMPL_TYPE min_y = 0.0F;

#ifndef GEO_UNSAFE
  if (points == NULL || convex_hull == NULL) {
    return GEO_ERR_NULL_POINTER;
  }
  if (size < 3) {
    return GEO_ERR_TOO_SMALL;
  }
#endif
  for (size_t iter = 0; iter < size; ++iter) {
#ifndef GEO_UNSAFE
    if (points[iter] == NULL) {
      return GEO_ERR_NULL_POINTER;
    }
#endif
    if (iter == 0) {
      min_idx = 0;
      min_y = points[0]->y;
      continue;
    }

    if ((points[iter]->y < min_y) ||
        ((points[iter]->y == min_y) && points[iter]->x < points[min_idx]->x)) {
      min_idx = iter;
      min_y = points[iter]->y;
    }
  }

  /* swap (if needed) so p0 is the actual starting point based on y and x
   * coords
   */
  if (min_idx != 0) {
    struct TMPL_POINT* temp = points[0];
    points[0] = points[min_idx];
    points[min_idx] = temp;
  }
  /* setting `start` which is a static global var to "pass a 3rd arg" to
   * qsort.
   * :( */
  global_start_point = points[0];
  /*
   * Sort points by polar angle from starting_point
   *
   *  NOTE: uses orientation instead of actual polar angle because if p[0] and
   * p[x] for a vector, v, then finding orientation of p[x+1] with respect to
   * v tells you which side of v p[x+1] falls on. This tells you the relative
   * angle and not the exact polar angle.
   */
  qsort((void*)&points[1], size - 1, sizeof(struct TMPL_POINT*), compare);
  /*
   * 1. add p0, p1, and p2 onto a stack from the sorted list. The first 2 are
   * guaranteed to be on the hull
   * 2. iterate over points in sorted list in order starting at p2
   * 2a. calcuate orientation of pX compared to the vector formed by p(x-2)
   *    and p(x-1).
   * 2b if CCW, push onto stack. if CW, pop last p(x-1) off the
   *    stack and move back to 2a using p(x-2) and p(x-1) without popped
   * point.
   *
   */
  convex_hull[0] = points[0];
  convex_hull[1] = points[1];
  convex_hull[2] = points[2];
  *convex_hull_size = 3;
  for (size_t iter = *convex_hull_size; iter < size; ++iter) {
    while (orientation(convex_hull[(*convex_hull_size) - 2],
                       convex_hull[(*convex_hull_size) - 1],
                       points[iter]) != LEFT) {
      (*convex_hull_size)--;
    }
    convex_hull[(*convex_hull_size)] = points[iter];
    (*convex_hull_size)++;
  }
  return GEO_SUCCESS;
}
#endif

#undef TMPL_CONCAT
#undef TMPL_CONCAT2
#undef TMPL_POINT
#undef TMPL_SEGMENT
#undef TMPL_GEOMETRY
#undef TMPL_FUNC

#endif
