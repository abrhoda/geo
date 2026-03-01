#include "geo.h"
#include <math.h>
#include <stdio.h>

enum geo_orientation {
  RIGHT = -1,
  COLINEAR = 0,
  LEFT = 1
};

/* point may not be the best type name but its easiest */
static float dot_product(struct geo_point const * vec_ab, struct geo_point const * vec_ac);
static float cross_product(struct geo_point const * vec_ab, struct geo_point const * vec_ac);

static enum geo_orientation orientation(struct geo_segment const * segment, struct geo_point const * point);
static int in_disk(struct geo_segment const * segment, struct geo_point const * point);

static float dot_product(struct geo_point const * const vec_ab, struct geo_point const * const vec_ac) {
  return ((vec_ab->x*vec_ac->x) + (vec_ab->y*vec_ac->y));
}

static float cross_product(struct geo_point const * const vec_ab, struct geo_point const * const vec_ac) {
  return (vec_ab->x*vec_ac->y) - (vec_ab->y*vec_ac->x);
}

/*
 * Creates vector AB and AC and finds the cross product. Returns the orientation
 * found from the cross product.
 */
static enum geo_orientation orientation(struct geo_segment const * const segment, struct geo_point const * const point) {
  struct geo_point vec_ab;
  struct geo_point vec_ac;
  float cross = 0.0F;

  vec_ab.x = segment->end->x-segment->start->x;
  vec_ab.y = segment->end->y-segment->start->y;
  vec_ac.x = point->x-segment->start->x;
  vec_ac.y = point->y-segment->start->y;
  cross = cross_product(&vec_ab, &vec_ac);
  if (fabs((double) cross) < GEO_EPSILON) {
    return COLINEAR;
  }
  if (cross < 0) {
    return RIGHT;
  }
  return LEFT;
}

static int in_disk(struct geo_segment const * const segment, struct geo_point const * const point) {
  struct geo_point vec_ap;
  struct geo_point vec_bp;
  vec_ap.x = (segment->start->x - point->x);
  vec_ap.y = (segment->start->y - point->y);

  vec_bp.x = (segment->end->x - point->x);
  vec_bp.y = (segment->end->y - point->y);
  return dot_product(&vec_ap, &vec_bp) <= 0.0F;
}

int geo_points_equal(struct geo_point const * const lhs, struct geo_point const * const rhs) {
  if (lhs == NULL || rhs == NULL) {
    return -1;
  }
  return (fabs((double) lhs->x - rhs->x) < GEO_EPSILON && fabs((double) lhs->y - rhs->y) < GEO_EPSILON);
}

int geo_segments_intersect(struct geo_segment const * const segment1, struct geo_segment const * const segment2) {
  int intersect_count = 0;
  enum geo_orientation orientation_a;
  enum geo_orientation orientation_b;
  enum geo_orientation orientation_c;
  enum geo_orientation orientation_d;

  if (segment1 == NULL || segment2 == NULL || segment1->start == NULL || segment1->end == NULL || segment2->start == NULL || segment2->end == NULL ) {
    return -1;
  }

  orientation_a = orientation(segment2, segment1->start);
  orientation_b = orientation(segment2, segment1->end);
  orientation_c = orientation(segment1, segment2->start);
  orientation_d = orientation(segment1, segment2->end);

  if ((orientation_a*orientation_b < 0) && (orientation_c*orientation_d < 0)) {
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

int geo_geometry_is_closed(struct geo_geometry const * const geometry) {
  int iter = 0;
  int mod = 0;
  int equal = 0;

  if (geometry == NULL || geometry->segments == NULL) {
    return -1;
  }

  if (geometry->segments_count < 3) {
    return 0;
  }

  for (iter = 0; iter < geometry->segments_count; ++iter) {
    mod = (iter + 1) % geometry->segments_count;
    equal = geo_points_equal(geometry->segments[iter]->end, geometry->segments[mod]->start);
    if (equal != 1) {
      return equal;
    }
  }
  return 1;
}

int geo_geometry_is_simple(struct geo_geometry const * const geometry) {
  int outer_iter = 0;
  int inner_iter = 0;
  int intersect = 0;
  if (geometry == NULL || geometry->segments == NULL) {
    return -1;
  }

  if (geometry->segments_count < 3) {
    return 0;
  }

  for (outer_iter = 0; outer_iter < (geometry->segments_count-1); ++outer_iter) {
    for (inner_iter = (outer_iter+1); inner_iter < geometry->segments_count; ++inner_iter) {
      intersect = geo_segments_intersect(geometry->segments[outer_iter], geometry->segments[inner_iter]);
      if (intersect == -1) {
        return -1;
      }
      if (intersect == 1) {
        return 0;
      }
    }
  }

  return 1;
}

int geo_point_in_geometry(struct geo_point const * point, struct geo_geometry const * geometry, int strict) {
  int intersections = 0;
  int iter = 0;
  enum geo_orientation orientation_p;
  for (iter = 0; iter < geometry->segments_count; ++iter) {
    orientation_p = orientation(geometry->segments[iter], point);
    if (orientation_p == COLINEAR && in_disk(geometry->segments[iter], point)) {
      return !strict;
    }
    /*
     * checks that a ray from `point` bisects the segment and that the orientation puts the `point` on the appropriate side of the `segment`.
     */
    intersections += (((geometry->segments[iter]->end->y >= point->y) - (geometry->segments[iter]->start->y >= point->y)) * orientation_p) > 0;
  }
  return intersections & 1;
}

/*
 * implement as simple raycasting algorithm. Methodology is:
 * - check if the points y coord is between the line segment's start and end points
 *   y coords
 * - check if the points x coord is to the left (less than) at least one point
 *   on the line segment
 * - if either of the first 2 checks fail, a ray from the point will never intersect
 *   the line segment so immediately move to next iteration.
 * - if the line segment is vertical, a ray from the point will always intersect
 *   the line segment so add 1 to count and move to next interation.
 * - get the x coord of the ray that inersects the line segment.
 * - check If the point's x coord is less than or equal to the x point of the intersection
 *   and if so, add 1 to count
 * - move to next iteration.
 *
 * NOTE: this version counts the cases where the point is on a segment (edge)
 * as "inside"
 *
 * NOTE: this only handles simple geometries, meaning it does not account for
 * "cut out" shapes. each nested geometry would have to individually be checked.
 *
 * returns 1 if inside, 0 otherwise.
 */
int old_geo_point_in_geometry(struct geo_point const * const point, struct geo_geometry const * const geometry) {
  int iter = 0;
  int count = 0;
  for(iter = 0; iter < geometry->segments_count; ++iter) {
    float min_y = 0.0F;
    float max_x = 0.0F;
    float max_y = 0.0F;
    float x_intersect_coord = 0.0F;

    if (geometry->segments[iter]->start->x < geometry->segments[iter]->end->x) {
      max_x = geometry->segments[iter]->end->x;
    } else {
      max_x = geometry->segments[iter]->start->x;
    }

    if (geometry->segments[iter]->start->y < geometry->segments[iter]->end->y) {
      min_y = geometry->segments[iter]->start->y;
      max_y = geometry->segments[iter]->end->y;
    } else {
      min_y = geometry->segments[iter]->end->y;
      max_y = geometry->segments[iter]->start->y;
    }

    /*
     * Check if point's y coord is between line segment's y coords AND that the
     * points x coord is to the right of all points on the line segment.
     */
    if (point->y < min_y || point->y > max_y || point->x > max_x) {
      continue;
    }

    /*
     * Check if the line segment is vertical because the 'ray' would always intersect
     */
    if (fabs((double)geometry->segments[iter]->start->x - geometry->segments[iter]->end->x) < GEO_EPSILON) {
      ++count;
      continue;
    }

    /*
     * find the x coord where the ray intersects the line segment to check that
     * the points x coord is less than (or equal to) the intersect points x coord.
     */
    x_intersect_coord = (((point->y - geometry->segments[iter]->start->y)*(geometry->segments[iter]->end->x - geometry->segments[iter]->start->x))/(geometry->segments[iter]->end->y - geometry->segments[iter]->start->y)) + geometry->segments[iter]->start->x;

    if (point->x <= x_intersect_coord) {
      ++count;
    }
  }
  return count & 1;
}
