#include "geo.h"

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

enum geo_orientation { RIGHT = -1, COLINEAR = 0, LEFT = 1 };
inline static float dot_product(struct geo_point const* vec_ab,
                                struct geo_point const* vec_ac);
inline static float cross_product(struct geo_point const* vec_ab,
                                  struct geo_point const* vec_ac);
inline static float squared_distance(struct geo_point const* point1,
                                     struct geo_point const* point2);
static enum geo_orientation orientation(struct geo_point const* start,
                                        struct geo_point const* end,
                                        struct geo_point const* point);
static bool in_disk(struct geo_segment const* segment,
                    struct geo_point const* point);
static int compare(const void* first, const void* second);


inline static float dot_product(struct geo_point const* const vec_ab,
                                struct geo_point const* const vec_ac) {
  return ((vec_ab->x * vec_ac->x) + (vec_ab->y * vec_ac->y));
}

inline static float cross_product(struct geo_point const* const vec_ab,
                                  struct geo_point const* const vec_ac) {
  return (vec_ab->x * vec_ac->y) - (vec_ab->y * vec_ac->x);
}

/*
 * Creates vector AB and AC and finds the cross product. Returns the orientation
 * found from the cross product.
 *
 * returns: -1 if the point is a clockwise (right) turn from segment start ->
 *             end
 *          0 if the point is on segment (colinear) start -> end
 *          1 if the point is a counterclockwise (left) turn from the segment
 *            start -> end
 *
 */
static enum geo_orientation orientation(struct geo_point const* const start,
                                        struct geo_point const* const end,
                                        struct geo_point const* const point) {
  struct geo_point vec_ab;
  struct geo_point vec_ac;
  vec_ab.x = end->x - start->x;
  vec_ab.y = end->y - start->y;
  vec_ac.x = point->x - start->x;
  vec_ac.y = point->y - start->y;
  float cross = cross_product(&vec_ab, &vec_ac);
  if (fabs((double)cross) < GEO_EPSILON) {
    return COLINEAR;
  }
  return cross < 0 ? RIGHT : LEFT;
}

static bool in_disk(struct geo_segment const* const segment,
                    struct geo_point const* const point) {
  struct geo_point vec_ap;
  struct geo_point vec_bp;
  vec_ap.x = (segment->start->x - point->x);
  vec_ap.y = (segment->start->y - point->y);

  vec_bp.x = (segment->end->x - point->x);
  vec_bp.y = (segment->end->y - point->y);
  return dot_product(&vec_ap, &vec_bp) <= 0.0F;
}

inline static float squared_distance(struct geo_point const* point1,
                                     struct geo_point const* point2) {
  return ((point2->x - point1->x) * (point2->x - point1->x)) +
         ((point2->y - point1->y) * (point2->y - point1->y));
}

/*
 * This returns -1 when the point (second) is a CCW turn. 1 if
 * point (second) is a CW turn. 0 if point (second) is equal to vec->end (first)
 *
 * TODO; this uses start as a global variable because orientation requires 3
 * points and compare takes 2 args. I'd like to not use stdlib.h/qsort and then
 * i could get rid of the static `start` variable.
 */
static struct geo_point* global_start_point;
static int compare(const void* first, const void* second) {
  const struct geo_point* vec_end = *(const struct geo_point* const*)first;
  const struct geo_point* point = *(const struct geo_point* const*)second;
  enum geo_orientation orientation_p =
      orientation(global_start_point, vec_end, point);

  if (orientation_p == COLINEAR) {
    int distance = (squared_distance(global_start_point, point) >=
                    squared_distance(global_start_point, vec_end));
    return distance == 1 ? -1 : 1;
  }

  // turn RIGHT into a positive and LEFT into negative to sort properly
  return -1 * orientation_p;
}

int geo_points_equal(struct geo_point const* const lhs,
                     struct geo_point const* const rhs) {
#ifndef GEO_UNSAFE
  if (lhs == NULL || rhs == NULL) {
    return -1;
  }
#endif
  return (fabs((double)lhs->x - rhs->x) < GEO_EPSILON &&
          fabs((double)lhs->y - rhs->y) < GEO_EPSILON);
}

int geo_segments_intersect(struct geo_segment const* const segment1,
                           struct geo_segment const* const segment2) {
#ifndef GEO_UNSAFE
  if (segment1 == NULL || segment2 == NULL || segment1->start == NULL ||
      segment1->end == NULL || segment2->start == NULL ||
      segment2->end == NULL) {
    return -1;
  }
#endif

  int intersect_count = 0;
  enum geo_orientation orientation_a =
      orientation(segment2->start, segment2->end, segment1->start);
  enum geo_orientation orientation_b =
      orientation(segment2->start, segment2->end, segment1->end);
  enum geo_orientation orientation_c =
      orientation(segment1->start, segment1->end, segment2->start);
  enum geo_orientation orientation_d =
      orientation(segment1->start, segment1->end, segment2->end);

  if ((orientation_a * orientation_b < 0) &&
      (orientation_c * orientation_d < 0)) {
    return 1;
  }

  if (orientation_a == COLINEAR && in_disk(segment2, segment1->start)) {
    ++intersect_count;
  }
  if (orientation_b == COLINEAR && in_disk(segment2, segment1->end)) {
    ++intersect_count;
  }
  if (orientation_c == COLINEAR && in_disk(segment1, segment2->start)) {
    ++intersect_count;
  }
  if (orientation_d == COLINEAR && in_disk(segment1, segment2->end)) {
    ++intersect_count;
  }

  return intersect_count;
}

int geo_geometry_is_closed(struct geo_geometry const* const geometry) {
#ifndef GEO_UNSAFE
  if (geometry == NULL || geometry->segments == NULL) {
    return -1;
  }

  if (geometry->segments_count < 3) {
    return 0;
  }
#endif

  for (int i = 0; i < geometry->segments_count; ++i) {
    int mod = (i + 1) % geometry->segments_count;
    int equal = geo_points_equal(geometry->segments[i]->end,
                                 geometry->segments[mod]->start);
    if (equal != 1) {
      return equal;
    }
  }
  return 1;
}

int geo_geometry_is_simple(struct geo_geometry const* const geometry) {
#ifndef GEO_UNSAFE
  if (geometry == NULL || geometry->segments == NULL) {
    return -1;
  }

  if (geometry->segments_count < 3) {
    return 0;
  }
#endif

  int intersect = 0;
  for (int i = 0; i < (geometry->segments_count - 1); ++i) {
    for (int j = (i + 1); j < geometry->segments_count; ++j) {
      intersect =
          geo_segments_intersect(geometry->segments[i], geometry->segments[j]);
#ifndef GEO_UNSAFE
      if (intersect == -1) {
        return -1;
      }
#endif
      if (intersect == 1) {
        return 0;
      }
    }
  }
  return 1;
}

int geo_point_in_geometry(struct geo_point const* point,
                          struct geo_geometry const* geometry, int strict) {
#ifndef GEO_UNSAFE
  if (geometry == NULL || geometry->segments == NULL || point == NULL) {
    return -1;
  }

  if (geometry->segments_count < 3) {
    return 0;
  }
  int intersections = 0;
#endif
  for (int i = 0; i < geometry->segments_count; ++i) {
#ifndef GEO_UNSAFE
    if (geometry->segments[i] == NULL || geometry->segments[i]->start == NULL ||
        geometry->segments[i]->end == NULL) {
      return -1;
    }
#endif

    enum geo_orientation orientation_p = orientation(
        geometry->segments[i]->start, geometry->segments[i]->end, point);
    if (orientation_p == COLINEAR && in_disk(geometry->segments[i], point)) {
      return !strict;
    }
    /*
     * checks that a ray from `point` bisects the segment and that the
     * orientation puts the `point` on the appropriate side of the `segment`.
     */
    intersections += (((geometry->segments[i]->end->y >= point->y) -
                       (geometry->segments[i]->start->y >= point->y)) *
                      orientation_p) > 0;
  }
  return intersections & 1;
}

int geo_geometry_in_geometry(struct geo_geometry* parent,
                             struct geo_geometry* child, int strict) {
#ifndef GEO_UNSAFE
  if (parent == NULL || parent->segments == NULL || child == NULL ||
      child->segments == NULL) {
    return -1;
  }

  if (parent->segments_count < 3 || child->segments_count < 3) {
    return 0;
  }
#endif
  int inside = 0;
  for (int i = 0; i < child->segments_count; ++i) {
#ifndef GEO_UNSAFE
    if (child->segments[i] == NULL) {
      return -1;
    }
#endif
    // could be -1, 0, or 1 depending on GEO_UNSAFE flag and actual result.
    inside = geo_point_in_geometry(child->segments[i]->start, parent, strict);
    if (inside != 1) {
      return inside;
    }
    inside = geo_point_in_geometry(child->segments[i]->end, parent, strict);
    if (inside != 1) {
      return inside;
    }
  }
  return 1;
}

int geo_convex_hull(struct geo_point** points, struct geo_point** hull,
                    int size) {
#ifndef GEO_UNSAFE
  if (points == NULL || hull == NULL || size < 3 || points[0] == NULL) {
    return -1;
  }
#endif

  int min_idx = 0;
  float min_y = points[0]->y;

  for (int i = 1; i < size; ++i) {
#ifndef GEO_UNSAFE
    if (points[i] == NULL) {
      return -1;
    }
#endif

    if ((points[i]->y < min_y) ||
        (fabs((double)(points[i]->y - min_y)) < GEO_EPSILON &&
         points[i]->x < points[min_idx]->x)) {
      min_idx = i;
      min_y = points[i]->y;
    }
  }

  // swap (if needed) so p0 is the actual starting point based on y and x coords
  if (min_idx != 0) {
    struct geo_point* temp = points[0];
    points[0] = points[min_idx];
    points[min_idx] = temp;
  }
  // setting `start` which is a static global var to "pass a 3rd arg" to qsort.
  // :(
  global_start_point = points[0];
  /*
   * Sort points by polar angle from starting_point
   *
   *  NOTE: uses orientation instead of actual polar angle because if p[0] and
   * p[x] for a vector, v, then finding orientation of p[x+1] with respect to v
   *        tells you which side of v p[x+1] falls on. This tells you the
   * relative angle and not the exact polar angle.
   */
  qsort((void*)&points[1], size - 1, sizeof(struct geo_point*), compare);
  /*
   * 1. add p0, p1, and p2 onto a stack from the sorted list. The first 2 are
   * guaranteed to be on the hull
   * 2. iterate over points in sorted list in order starting at p2
   *    2a. calcuate orientation of pX compared to the vector formed by p(x-2)
   * and p(x-1). 2b if CCW, push onto stack. if CW, pop last p(x-1) off the
   * stack and move back to 2a using p(x-2) and p(x-1) without popped point.
   *
   */
  hull[0] = points[0];
  hull[1] = points[1];
  hull[2] = points[2];
  int hull_idx = 3;
  for (int i = 3; i < size; ++i) {
    while (orientation(hull[hull_idx - 2], points[hull_idx - 1], points[i]) !=
           LEFT) {
      hull_idx--;
    }
    hull[hull_idx] = points[i];
    hull_idx++;
  }

  return hull_idx;
}
