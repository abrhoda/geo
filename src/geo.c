#include "geo.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

enum geo_orientation { RIGHT = -1, COLINEAR = 0, LEFT = 1 };

/* point may not be the best type name but its easiest */
static float dot_product(struct geo_point const* vec_ab,
                         struct geo_point const* vec_ac);
static float cross_product(struct geo_point const* vec_ab,
                           struct geo_point const* vec_ac);

static enum geo_orientation orientation(struct geo_point const* start,
                                        struct geo_point const* end,
                                        struct geo_point const* point);
static int in_disk(struct geo_segment const* segment,
                   struct geo_point const* point);

static float squared_distance(struct geo_point const* point1,
                              struct geo_point const* point2);

static int compare(const void *first, const void *second);

static float dot_product(struct geo_point const* const vec_ab,
                         struct geo_point const* const vec_ac) {
  return ((vec_ab->x * vec_ac->x) + (vec_ab->y * vec_ac->y));
}

static float cross_product(struct geo_point const* const vec_ab,
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
  float cross = 0.0F;

  vec_ab.x = end->x - start->x;
  vec_ab.y = end->y - start->y;
  vec_ac.x = point->x - start->x;
  vec_ac.y = point->y - start->y;
  cross = cross_product(&vec_ab, &vec_ac);
  if (fabs((double)cross) < GEO_EPSILON) {
    return COLINEAR;
  }
return cross < 0 ? RIGHT : LEFT;
}

static int in_disk(struct geo_segment const* const segment,
                   struct geo_point const* const point) {
  struct geo_point vec_ap;
  struct geo_point vec_bp;
  vec_ap.x = (segment->start->x - point->x);
  vec_ap.y = (segment->start->y - point->y);

  vec_bp.x = (segment->end->x - point->x);
  vec_bp.y = (segment->end->y - point->y);
  return dot_product(&vec_ap, &vec_bp) <= 0.0F;
}

static float squared_distance(struct geo_point const* point1,
                              struct geo_point const* point2) {

  float diff_x = point2->x - point1->x;
  float diff_y = point2->y - point1->y;
  return (diff_x*diff_x) + (diff_y*diff_y);
}

/* 
 * This returns -1 when the point (second) is a CCW turn. 1 if 
 * point (second) is a CW turn. 0 if point (second) is equal to vec->end (first)
 *
 * TODO; this uses start as a global variable because orientation requires 3 points
 *      and compare takes 2 args. I'd like to not use stdlib.h/qsort and then i could
 *      get rid of the static `start` variable.
 */
static struct geo_point * start;
static int compare(const void *first, const void *second) {
  struct geo_point * vec_end = (struct geo_point *)first;
  struct geo_point * point = (struct geo_point *)second;
  enum geo_orientation orientation_p = orientation(start, vec_end, point);

  printf("start (%f, %f) and end (%f, %f)\n", start->x, start->y, vec_end->x, vec_end->y);
  printf("point (%f, %f) to find orientation\n", point->x, point->y);
  if (orientation_p == COLINEAR) {
    int distance = (squared_distance(start, point) >= squared_distance(start, vec_end));
    return distance == 1 ? -1 : 1;
  }
  printf("orientation = %d\n", orientation_p);

  /* turn RIGHT into a positive and LEFT into negative to sort properly */
  return -1*orientation_p;
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
  int intersect_count = 0;
  enum geo_orientation orientation_a;
  enum geo_orientation orientation_b;
  enum geo_orientation orientation_c;
  enum geo_orientation orientation_d;
#ifndef GEO_UNSAFE
  if (segment1 == NULL || segment2 == NULL || segment1->start == NULL ||
      segment1->end == NULL || segment2->start == NULL ||
      segment2->end == NULL) {
    return -1;
  }
#endif

  orientation_a = orientation(segment2->start, segment2->end, segment1->start);
  orientation_b = orientation(segment2->start, segment2->end, segment1->end);
  orientation_c = orientation(segment1->start, segment1->end, segment2->start);
  orientation_d = orientation(segment1->start, segment1->end, segment2->end);

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
  int iter = 0;
  int mod = 0;
  int equal = 0;

#ifndef GEO_UNSAFE
  if (geometry == NULL || geometry->segments == NULL) {
    return -1;
  }

  if (geometry->segments_count < 3) {
    return 0;
  }
#endif

  for (iter = 0; iter < geometry->segments_count; ++iter) {
    mod = (iter + 1) % geometry->segments_count;
    equal = geo_points_equal(geometry->segments[iter]->end,
                             geometry->segments[mod]->start);
    if (equal != 1) {
      return equal;
    }
  }
  return 1;
}

int geo_geometry_is_simple(struct geo_geometry const* const geometry) {
  int outer_iter = 0;
  int inner_iter = 0;
  int intersect = 0;

#ifndef GEO_UNSAFE
  if (geometry == NULL || geometry->segments == NULL) {
    return -1;
  }

  if (geometry->segments_count < 3) {
    return 0;
  }
#endif

  for (outer_iter = 0; outer_iter < (geometry->segments_count - 1);
       ++outer_iter) {
    for (inner_iter = (outer_iter + 1); inner_iter < geometry->segments_count;
         ++inner_iter) {
      intersect = geo_segments_intersect(geometry->segments[outer_iter],
                                         geometry->segments[inner_iter]);
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
  int intersections = 0;
  int iter = 0;
  enum geo_orientation orientation_p;
#ifndef GEO_UNSAFE
  if (geometry == NULL || geometry->segments == NULL || point == NULL) {
    return -1;
  }

  if (geometry->segments_count < 3) {
    return 0;
  }
#endif
  for (iter = 0; iter < geometry->segments_count; ++iter) {
#ifndef GEO_UNSAFE
    if (geometry->segments[iter] == NULL ||
        geometry->segments[iter]->start == NULL ||
        geometry->segments[iter]->end == NULL) {
      return -1;
    }
#endif

    orientation_p = orientation(geometry->segments[iter]->start, geometry->segments[iter]->end, point);
    if (orientation_p == COLINEAR && in_disk(geometry->segments[iter], point)) {
      return !strict;
    }
    /*
     * checks that a ray from `point` bisects the segment and that the
     * orientation puts the `point` on the appropriate side of the `segment`.
     */
    intersections += (((geometry->segments[iter]->end->y >= point->y) -
                       (geometry->segments[iter]->start->y >= point->y)) *
                      orientation_p) > 0;
  }
  return intersections & 1;
}

int geo_geometry_in_geometry(struct geo_geometry* parent,
                             struct geo_geometry* child, int strict) {
  int iter = 0;
  int inside = 0;
#ifndef GEO_UNSAFE
  if (parent == NULL || parent->segments == NULL || child == NULL ||
      child->segments == NULL) {
    return -1;
  }

  if (parent->segments_count < 3 || child->segments_count < 3) {
    return 0;
  }
#endif
  for (iter = 0; iter < child->segments_count; ++iter) {
#ifndef GEO_UNSAFE
    if (child->segments[iter] == NULL) {
      return -1;
    }
#endif
    /* could be -1, 0, or 1 depending on GEO_UNSAFE flag and actual result. */
    inside =
        geo_point_in_geometry(child->segments[iter]->start, parent, strict);
    if (inside != 1) {
      return inside;
    }
    inside = geo_point_in_geometry(child->segments[iter]->end, parent, strict);
    if (inside != 1) {
      return inside;
    }
  }
  return 1;
}

int geo_convex_hull(struct geo_point ** points, struct geo_point ** hull, int size) {
  int hull_idx = -1;
  int iter = 1;

  /* used to find starting point */
  struct geo_point * temp;
  int min_idx = 0;
  float current_y = 0.0F;
  float min_y = 0.0F;

#ifndef GEO_UNSAFE
  if(points == NULL || hull == NULL || size < 3) {
    return hull_idx;
  }
#endif
  for (iter = 0; iter < size; ++iter) {
#ifndef GEO_UNSAFE
    if (points[iter] == NULL) {
      return hull_idx;
    }
#endif
    if (iter == 0) {
      min_idx = 0;
      min_y = points[0]->y;
      continue;
    }

    current_y = points[iter]->y;
    if ((current_y < min_y) || (fabs((double) (current_y - min_y)) < GEO_EPSILON && points[iter]->x < points[min_idx]->x)) {
      min_idx = iter;
      min_y = points[iter]->y;
    }
  }

  /* swap (if needed) so p0 is the actual starting point based on y and x coords */
  if (min_idx != 0) {
    temp = points[0];
    points[0] = points[min_idx];
    points[min_idx] = temp;
  }
  /* setting `start` which is a static global var to "pass a 3rd arg" to qsort. :( */
  start = points[0];
  /*
   * Sort points by polar angle from starting_point
   *
   *  NOTE: uses orientation instead of actual polar angle because if p[0] and p[x]
   *        for a vector, v, then finding orientation of p[x+1] with respect to v
   *        tells you which side of v p[x+1] falls on. This tells you the relative
   *        angle and not the exact polar angle.
   */
  qsort(points[1], size-1, sizeof(struct geo_point *), compare);
  for (iter = 0; iter < size; ++iter) {
    printf("%d. (pointer = %p). (%f, %f)\n", iter,  (void *)points[iter], points[iter]->x, points[iter]->y);
  }
  /*
   * 1. add p0, p1, and p2 onto a stack from the sorted list. The first 2 are guaranteed to be on the hull
   * 2. iterate over points in sorted list in order starting at p2
   *    2a. calcuate orientation of pX compared to the vector formed by p(x-2) and p(x-1).
   *    2b if CCW, push onto stack. if CW, pop last p(x-1) off the stack and move back to 2a using p(x-2) and p(x-1) without popped point.
   *
   */
  hull[0] = points[0];
  hull[1] = points[1];
  hull[2] = points[2];
  hull_idx = 3;
  for (iter = 3; iter < size; ++iter) {
    while(orientation(points[iter-2], points[iter-1], points[iter]) != LEFT) {
      hull_idx--;
    }
    hull[hull_idx] = points[iter];
  }

  for (iter = 0; iter < hull_idx; ++iter) {
    printf("%d. (pointer = %p). (%f, %f)\n", iter,  (void *)hull[iter], hull[iter]->x, hull[iter]->y);
  }

  return hull_idx;
}
