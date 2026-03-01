#ifndef GEO_H
#define GEO_H

#ifndef GEO_EPSILON
#define GEO_EPSILON 0.00001
#endif

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
 * @return int result code indicating the outcome:
 *   - -1 if either point is NULL
 *   - 0 if the points are not equal
 *   - 1 if the points are equal
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
 * NOTE: 2 is also returned when one segment's end is the same as another segment's start. There
 * should be a way to determine whether the intersect == 2 is due to sharing an end+start pair or
 * if its because the first segment is contained by another. Maybe this can be done with a
 * `proper_only` flag that only checks if an intersection is a proper intersect for cases
 * where end+start pairs are expected to "intersect" but shouldn't count as an intersection.
 */
int geo_segments_intersect(struct geo_segment const * segment1, struct geo_segment const * segment2);

struct geo_geometry {
  struct geo_segment ** segments;
  int segments_count;
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
 * @warning this function might produce unexpected results if
 *          `geo_geometry_is_closed(geo_geometry) &&
 *          geo_geometry_is_simple(geo_geometry) != 1`. Ensure that your geo_geometry
 *          meets this condition BEFORE using this function.
 *
 * @details uses a raycasting algorithm to check if `point` is in `geometry`
 *
 * @param[in] geo_point The point to test
 * @param[in] geo_geometry The geometry to test if the point is inside.
 * @param[in] strict Controls whether a point on a segment is considered in or out
 *                   of the geometry.
 *
 * @return 1 if the geo_point is inside the geo_geometry, 0 otherwise
 */
int geo_point_in_geometry(struct geo_point const * point, struct geo_geometry const * geometry, int strict);

/**
 * @brief determins if a given geo_point is inside of the geo_geometry
 * @deprecated and might not work as intended.
 */
int old_geo_point_in_geometry(struct geo_point const * point, struct geo_geometry const * geometry);



/*
 * TODO Implement these functions:
 *
 * implement as graham's scan because graham's scan minimizes segment count.
 * int geometry_from_points(struct geo_point **points, int count, struct geo_geometry * geometry);
 *
 * int geometry_in_geometry(struct geo_geometry * parent, struct geo_geometry * child);
 */



#endif
