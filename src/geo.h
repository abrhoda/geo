/**
 * \file geo.h
 *
 * \brief Header file for the libgeo geometric enums, functions, and structs.
 *
 * \author Alexander Rhoda
 * \date 2026
 */
#ifndef GEO_H
#define GEO_H

/**
 * \def GEO_EPSILON
 *
 * \brief epsilon value to use as tolerance when comparing floats and doubles.
 */
#ifndef GEO_EPSILON
#define GEO_EPSILON 0.00001
#endif

/**
 * \struct geo_point
 *
 * \brief a 2d point that holds x and y coordinates.
 */
struct geo_point {
  float x;
  float y;
};

/**
 * \brief Determines if 2 `geo_point`s are equal.
 *
 * \details 2 `geo_point`s are equal if and only if their x and y coordinates
 * are within GEO_EPSILON of each other.
 *
 * \param[in] lhs The first geo_point to test for equality
 * \param[in] rhs The second geo_point to test for equality
 *
 * \return int result code indicating the outcome:
 *   - -1 if either point is NULL (removed when compiled with GEO_UNSAFE set)
 *   - 0 if the points are not equal
 *   - 1 if the points are equal
 *
 */
int geo_points_equal(struct geo_point const* lhs, struct geo_point const* rhs);

/**
 * \struct geo_segment
 *
 * \brief a line segment with a start point and an end point.
 */
struct geo_segment {
  struct geo_point* start;
  struct geo_point* end;
};

/**
 * \brief Determines if 2 segments intersect.
 *
 * \details checks determines if segment1 and segment2 intersect. It does so by
 *         first checking if they "properly intersect" through finding the
 * orientations of the start and end points of one segment with the other line
 * segment. If the two line segments don't "properly intersect", the start and
 * end points of each segment are checked to see if they are on the other
 * segment. This determines if a segment intersects the other segment at the
 * start point, end point, or both points while being colinear. This informs if
 * the segment intersects the other or if the segment is the same segment as the
 * other.
 *
 * \param[in] segment1 The first segment to test for intersection
 * \param[in] segment2 The second segment to test for intersection
 *
 * \return int result code indicating the outcome:
 *   - -1 if either segment is NULL or if either segments start point or end point
 *        are NULL (removed when compiled with GEO_UNSAFE set)
 *   - 0 if the segments don't intersect
 *   - 1 if the segments properly intersect
 *   - 2 if the segments share an end + start point pair or if one segment is a
 *        section of the other.
 *   - 3 if one segment is a section of another and they share an end + start point pair.
 *   - 4 if the segments have identical start and end points.
 */
int geo_segments_intersect(struct geo_segment const* segment1,
                           struct geo_segment const* segment2);

/**
 * \struct geo_geometry
 *
 * \brief a geometry is a polygon made of line segments. Closed geometries form
 *        a ring with their line segments. Simple geometries have no line
 * segments that intersect (except for overlapping start point and end points)
 */
struct geo_geometry {
  int segments_count;
  struct geo_segment** segments;
  /* TODO int is_negative_space; // tell if a geometry is a cut of of a parent.
   */
};

/**
 * \brief determines if a geo_geometry is considered a closed shape.
 *
 * \details a closed geometry must have at least 3 segments and each nth segment
 *          ends at the (n+1)th segment's start. This means the segment's form a
 *          continuous, unbroken boundary.
 *
 * \param[in] geometry The geometry to test.
 *
 * \return int result code indicating the outcome:
 *   - -1 if geometry or geometry's segments are NULL (removed when compiled with GEO_UNSAFE set)
 *   - 0 if the geometry is not closed
 *   - 1 if the geometry is closed
 */
int geo_geometry_is_closed(struct geo_geometry const* geometry);

/**
 * \brief determines if a geo_geometry is considered a simple geometry.
 *
 * \details a simple geometry is one where the segments that form the geometry
 *          do not intersect with each other.
 *
 * \param[in] geometry The geometry to test.
 *
 * \return int result code indicating the outcome:
 *   - -1 if geometry or geometry's segments are NULL (removed when compiled with GEO_UNSAFE set)
 *   - 0 if the geometry is not simple
 *   - 1 if the geometry is simple
 */
int geo_geometry_is_simple(struct geo_geometry const* geometry);

/**
 * \brief determines if a given geo_point is inside of the geo_geometry.
 *
 * \warning this function might produce unexpected results if
 *          `geo_geometry_is_closed(geo_geometry) != 1 ||
 *          geo_geometry_is_simple(geo_geometry) != 1`. Ensure that your
 *          geo_geometry meets this condition BEFORE using this function.
 *
 * \details uses a raycasting algorithm to check if `point` is in `geometry`
 *
 * \param[in] geo_point The point to test
 * \param[in] geo_geometry The geometry to test if the point is inside.
 * \param[in] strict Controls whether a point on a segment is considered in or
 * out of the geometry.
 *
 * \return int result code indicating the outcome:
 *   - -1 if point, geometry, geometry's segments, any start point, or any end point is NULL (removed when compiled with GEO_UNSAFE set)
 *   - 0 if not in the geometry
 *   - 1 if in the geometry
 */
int geo_point_in_geometry(struct geo_point const* point,
                          struct geo_geometry const* geometry, int strict);

/**
 * \brief determines if one geometry (called `child`) is entirely contained in
 *        the other geometry (called `parent`)
 *
 * \warning this function might produce unexpected results if
 *          `geo_geometry_is_closed(child) != 1 ||
 *          geo_geometry_is_simple(child) != 1 ||
 *          geo_geometry_is_closed(parent) != 1 ||
 *          geo_geometry_is_simple(parent) != 1`. Ensure that your
 *          `geo_geometry` structs meets this condition BEFORE using this function.
 *
 * \details checks that each segment in `child` is entirely contained in `parent`
 *          by checking that each segment in the child geo_geometry has a start point
 *          and an end point inside the parent geo_geometry using the `geo_point_in_geometry`
 *          function.
 *
 * \param[in] parent The containing geometry
 * \param[in] child The geometry to test if it is contained in parent geometry
 * \param[in] strict Controls whether a point on a segment is considered in or
 *
 * \return int result code indicating the outcome:
 *   - -1 if either geometry, either geometry's segments, any start point, or any end point is NULL (removed when compiled with GEO_UNSAFE set)
 *   - 0 if child geometry is not contained in the parent geometry
 *   - 1 if child geometry is contained in the parent geometry
 */
int geo_geometry_in_geometry(struct geo_geometry * parent, struct geo_geometry * child, int strict);

/*
 * TODO Implement these functions:
 *
 * implement as graham's scan because graham's scan minimizes segment count.
 * int geometry_from_points(struct geo_point **points, int count, struct
 * geo_geometry * geometry);
 */

#endif
