#ifndef GEO_H
#define GEO_H

#include <stddef.h>
#define GEO_EPSILON 0.00001

enum geo_orientation {
  RIGHT = -1,
  COLINEAR = 0,
  LEFT = 1
};

enum geo_disk_position {
  INSIDE = -1,
  ON_EDGE = 0,
  OUTSIDE = 1
};

struct geo_point {
  float x;
  float y;
};

/**
 * @brief Determines if 2 `geo_point`s are equal.
 *
 * @details 2 `geo_point`s are equal if and only if their x and y coordinates are
 *          within GEO_EPSILON of each other.
 *
 * @param[in] lhs The first geo_point to test for equality
 * @param[in] rhs The second geo_point to test for equality
 *
 * @return 1 if the points are equal, 0 otherwise.
 *
 */
int geo_points_equal(struct geo_point const * lhs, struct geo_point const * rhs);

struct geo_segment {
  struct geo_point * start;
  struct geo_point * end;
};

/**
 * @brief Determines if 2 segments intersect.
 *
 * @details checks determines if segment1 and segment2 intersect. It does so by
 *         first checking if they "properly intersect" through finding the orientations
 *         of the start and end points of one segment with the other line segment.
 *         If the two line segments don't "properly intersect", the start and end
 *         points of each segment are checked to see if they are on the other segment.
 *         This determines if a segment intersects the other segment at the start point,
 *         end point, or both points while being colinear. This informs if the segment
 *         intersects the other or if the segment is the same segment as the other.
 *
 * @param[in] segment1 The first segment to test for intersection
 * @param[in] segment2 The second segment to test for intersection
 *
 * @returns the count of intersectings points on both lines. 0 of there is none,
 * 1 if the segments properly intersect or intersect at one segment's start or end
 * point, 2 if one segment lies entirely on the other, 4 if the 2 segments are the
 * same segment.
 *
 * TODO add a proper_only control param to handle cases where colinearity should be considered on
 * intersections and when it shouldn't.
 */
int geo_segments_intersect(struct geo_segment const * segment1, struct geo_segment const * segment2);

struct geo_geometry {
  struct geo_segment ** segments;
  size_t segments_count;
  /* TODO int is_negative_space; // tell if a geometry is a cut of of a parent. */
};


/**
 * @brief determines if a geo_geometry is considered a closed shape.
 *
 * @details a closed geometry must have at least 3 segments and each nth segment
 *          ends at the (n+1)th segment's start. This means the segment's form a
 *          continuous, unbroken boundary.
 *
 * @param[in] geometry The geometry to test.
 * 
 * @return 1 if the geometry is a closed shape, 0 otherwise.
 */
int geo_geometry_is_closed(struct geo_geometry const * geometry);

/**
 * @brief determines if a geo_geometry is considered a simple geometry.
 *
 * @details a simple geometry is one where the segments that form the geometry
 *          do not intersect with each other.
 *
 * @param[in] geometry The geometry to test.
 *
 * @return 1 if the geometry is simple, 0 otherwise.
 */
int geo_geometry_is_simple(struct geo_geometry const * geometry);


/**
 * @brief determines if a given geo_point is inside of the geo_geometry.
 *
 * param[in] geo_point The point to test
 * param[in] geo_geometry The geometry to test if the point is inside.
 *
 * @return 1 if the geo_point is inside the geo_geometry, 0 otherwise
 */
int geo_point_in_geometry(struct geo_point const * point, struct geo_geometry const * geometry);



/*
 * TODO Implement these functions:
 *
 * implement as graham's scan because graham's scan minimizes segment count.
 * int geometry_from_points(struct geo_point **points, int count, struct geo_geometry * geometry);
 *
 * int geometry_in_geometry(struct geo_geometry * parent, struct geo_geometry * child);
 */



#endif
