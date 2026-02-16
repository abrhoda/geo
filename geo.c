#include "geo.h"
#include <math.h>

/* point may not be the best type name but its easiest */
static float dot_product(struct point const * vec_ab, struct point const * vec_ac);
static float cross_product(struct point const * vec_ab, struct point const * vec_ac);

static enum orientation orient(struct segment const * segment, struct point const * point);
static int is_in_disk(struct segment const * segment, struct point const * point);
static int is_on_segment(struct segment const * segment, struct point const * point);

static float dot_product(struct point const * const vec_ab, struct point const * const vec_ac) {
  return ((vec_ab->x*vec_ac->x) + (vec_ab->y*vec_ac->y));
}

static float cross_product(struct point const * const vec_ab, struct point const * const vec_ac) {
  return (vec_ab->x*vec_ac->y) - (vec_ab->y*vec_ac->x);
}

/*
 * Creates vector AB and AC and finds the cross product. Returns the orientation
 * found from the cross product.
 */
static enum orientation orient(struct segment const * const segment, struct point const * const point) {
  struct point vec_ab;
  struct point vec_ac;
  float cross = 0.0F;

  vec_ab.x = segment->end->x-segment->start->x;
  vec_ab.y = segment->end->y-segment->start->y;
  vec_ac.x = point->x-segment->start->x;
  vec_ac.y = point->y-segment->start->y;
  cross = cross_product(&vec_ab, &vec_ac);
  if (fabs((double) cross) < EPSILON) {
    return COLINEAR;
  }
  if (cross < 0) {
    return RIGHT;
  }
  return LEFT;
}

/*
 * Checks if `point` lies on a disk whose diameter is `segment`.
 *
 * - dot > 0 -> false because cos(theta) between the 2 vectors is less than pi/2 (90 degrees)
 * - dot == 0 -> true because cos (theta) = pi/2 (90 degrees) and point is _on disk edge_
 * - dot < 0 -> true becuse cos(theta) is greater than pi/2 (90 degrees)
 */
static int is_in_disk(struct segment const * const segment, struct point const * const point) {
  float dot = 0.0F;
  struct point vec_ap;
  struct point vec_bp;
  vec_ap.x = (segment->start->x - point->x);
  vec_ap.y = (segment->start->y - point->y);

  vec_bp.x = (segment->end->x - point->x);
  vec_bp.y = (segment->end->y - point->y);
  dot = dot_product(&vec_ap, &vec_bp);
  return (dot < 0 || fabs((double) dot) < EPSILON);
}

/*
 * Checks if `point` is on `segment`. This is useful to determine proper intersections
 * vs intersections where one of the endpoint of a segment is exactly on the other.
 *
 */
static int is_on_segment(struct segment const * segment, struct point const * point) {
  return orient(segment, point) == COLINEAR && is_in_disk(segment, point);
}

/*
 * Checks that if 2 points x and y values are within EPSILON tolerance, returning
 * 1 if both are and 0 otherwise.
 *
 */
int points_equal(struct point const * const lhs, struct point const * const rhs) {
  return (fabs((double) lhs->x - rhs->x) < EPSILON && fabs((double) lhs->y - rhs->y) < EPSILON);
}

/*
 * Checks the if segment1's start and end points are on opposite sides of segment2 and
 * if segment2's start and end points are on opposite sides of segment1.
 *
 * the note on "properly intersect" means that the lines:
 * 1. do intersect.
 * 2. are not colinear.
 * 3. don't have endpoints of either one of the segments lay on the other (meaning they don't
 *    intersect at either one's endpoints
 *
 * FIXME: this does not properly handle when the intersecting point of segment1 on segment2 is
 * either start or end points.
 */
int segments_intersect(struct segment const * const segment1, struct segment const * const segment2) {
  int count = 0;
  enum orientation orientation_a = orient(segment2, segment1->start);
  enum orientation orientation_b = orient(segment2, segment1->end);
  enum orientation orientation_c = orient(segment1, segment2->start);
  enum orientation orientation_d = orient(segment1, segment2->end);

  /* properly intersect */
  if ((orientation_a*orientation_b < 0) && (orientation_c*orientation_d < 0)) {
    return 1;
  }

  /* check if endpoints are where the intersection happens */
  if (orientation_a == COLINEAR && is_in_disk(segment2, segment1->start)) {
    count++;
  }

  if 

  return 0;
}

/*
 * Checks if geometry is a closed geometry or not by checking if the nth segment's end point
 * is the same as the (n+1)th segment's starting point. When n == segments_count, the segment's
 * end point is checked against the n == 0 segment's starting point. This forms a closed
 * geometry.
 *
 */
int geometry_is_closed(struct geometry const * const geometry) {
  size_t iter = 0;
  if (geometry->segments_count < 3) {
    return 0;
  }

  for (iter = 0; iter < geometry->segments_count - 2; ++iter) {
    if (!points_equal(geometry->segments[iter]->end, geometry->segments[iter+1]->start)) {
      return 0;
    }
  }
  return points_equal(geometry->segments[geometry->segments_count-1]->end, geometry->segments[0]->start);
}

/*
 * Checks if any line segments of the geometry intersect with another line segment of the geometry.
 * Start and end points of the line segments should not be considered as intersecting.
 */
int geometry_is_simple(struct geometry const * const geometry) {
  size_t outer_iter = 0;
  size_t inner_iter = 0;
  for (outer_iter = 0; outer_iter < (geometry->segments_count-1); ++outer_iter) {
    for (inner_iter = (outer_iter+1); inner_iter < geometry->segments_count; ++inner_iter) {
      if (segments_intersect(geometry->segments[outer_iter], geometry->segments[inner_iter]) != 0) {
        return 0;
      }
    }
  }

  return 1;
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
int point_in_geometry(struct point const * const point, struct geometry const * const geometry) {
  size_t iter = 0;
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
    if (fabs((double)geometry->segments[iter]->start->x - geometry->segments[iter]->end->x) < EPSILON) {
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
  return count % 2;
}
