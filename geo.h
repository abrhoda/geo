#ifndef GEO_H
#define GEO_H

#include <stddef.h>
#define EPSILON 0.00001

struct point {
  float x;
  float y;
};

int points_equal(struct point * lhs, struct point * rhs);

struct segment {
  struct point * start;
  struct point * end;
};

int segments_intersect(struct segment * segment1, struct segment * segment2);

struct geometry {
  struct segment ** segments;
  size_t segments_count;
};

/*
 * implement as graham's scan because graham's scan minimizes segment count.
 * int geometry_from_points(struct point **points, int count, struct geometry * geometry);
 */

/*
 * `int is_negative_space;` to tell if its a "hole" cut out of a parent geometry.
 */

int geometry_is_closed(struct geometry const * geometry);
int geometry_is_simple(struct geometry const * geometry);

/*
 * could this be optimized to keep the (min_x, min_y) and (max_x, max_y) and only
 * check point_in_geometry of point (p_x, p_y) if min_x < p_x < max_x and
 * min_y < p_y < max_y
 */
int point_in_geometry(struct point * point, struct geometry * geometry);

/*
 * int geometry_in_geometry(struct geometry * parent, struct geometry * child);
 */



#endif
