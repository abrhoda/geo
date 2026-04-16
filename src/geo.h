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

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>

/**
 * \def GEO_EPSILON
 *
 * \brief epsilon value to use as tolerance when comparing floats and doubles.
 */
#ifndef GEO_EPSILON
#define GEO_EPSILON 1e-5F
#endif

/**
 * \enum geo_result
 *
 * \brief Tells whether a function successfully completed and if not, what error
 * happened.
 *
 */
enum geo_result {
  GEO_SUCCESS = 0,
  GEO_ERR_NULL_POINTER = 1,
  GEO_ERR_TOO_SMALL = 2,
  GEO_ERR_OVERFLOW = 3  // unused for now
};

/**
 * \struct geo_point
 *
 * \brief a 2d point that holds x and y coordinates.
 */
struct geo_point {
  float x; /**< The x coordinate of the point */
  float y; /**< The y coordinate of the point */
};

/**
 * \brief Determines if 2 `geo_point`s are equal.
 *
 * \details 2 `geo_point`s are equal if and only if their x and y coordinates
 * are within GEO_EPSILON of each other.
 *
 * \param[in] lhs The first geo_point to test for equality
 * \param[in] rhs The second geo_point to test for equality
 * \param[out] is_equal The result of the equality test
 *
 * \return enum geo_result indicating whether or not the operation was
 * successful. the `is_equal` out value should only be used when geo_result ==
 * GEO_SUCCESS. Possible geo_result values are:
 *         - GEO_SUCCESS (0)
 *         - GEO_ERR_NULL_POINTER (1)
 *
 */
enum geo_result geo_points_equal(struct geo_point const* lhs,
                                 struct geo_point const* rhs, bool* is_equal);

/**
 * TODO implement
 */
enum geo_result geo_point_nearby_point(struct geo_point const* root,
                                     struct geo_point const* to_check,
                                     float distance, bool* is_nearby);

/**
 * \struct geo_segment
 *
 * \brief a line segment with a start point and an end point.
 */
struct geo_segment {
  struct geo_point* start; /**< the start point of the line segment */
  struct geo_point* end; /**< the end point of the line segment */
};

/**
 * \brief Determines if 2 segments intersect.
 *
 * \details checks determines if segment1 and segment2 intersect. It does so by
 * first checking if they "properly intersect" through finding the orientations
 * of the start and end points of one segment with the other line segment. If
 * the two line segments don't "properly intersect", the start and end points
 * of each segment are checked to see if they are on the other segment. This
 * determines if a segment intersects the other segment at the start point, end
 * point, or both points while being colinear. This informs if the segment
 * intersects the other or if the segment is the same segment as the other.
 *
 * `intersect_count` has a different meaning depending on the value. Values are
 * on the range 0 <= intersect_count <= 4:
 *   - 0 if the segments do not intersect
 *   - 1 if the segments properly intersect
 *   - 2 if the segments share an end + start point pair or if one segment is a
 *        section of the other.
 *   - 3 if one segment is a section of another and they share an end + start
 * point pair.
 *   - 4 if the segments have identical start and end points.
 *
 *
 * \param[in] segment1 The first segment to test for intersection
 * \param[in] segment2 The second segment to test for intersection
 * \param[out] intersect_count The number of intersection points
 *
 * \return enum geo_result indicating whether or not the operation was
 * successful. the `intersect_count` out value should only be used when
 * geo_result == GEO_SUCCESS possible geo_result values are:
 *         - GEO_SUCCESS (0)
 *         - GEO_ERR_NULL_POINTER (1)
 *
 */
enum geo_result geo_segments_intersect(struct geo_segment const* segment1,
                                       struct geo_segment const* segment2,
                                       size_t* intersect_count);

/**
 * \struct geo_geometry
 *
 * \brief A geometry is a polygon made of line segments. Closed geometries form
 *        a ring with their line segments. Simple geometries have no line
 * segments that intersect (except for overlapping start point and end points)
 */
struct geo_geometry {
  struct geo_segment** segments; /**< The list of segments that make up the geometry */
  int segments_count; /**< The size of the segments array */
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
 * \param[out] is_closed The result of "is closed" test.
 *
 * \return enum geo_result indicating whether or not the operation was
 * successful. the `is_closed` out value should only be used when geo_result ==
 * GEO_SUCCESS. Possible geo_result values are:
 *         - GEO_SUCCESS (0)
 *         - GEO_ERR_NULL_POINTER (1)
 *         - GEO_ERR_TOO_SMALL (2)
 */
enum geo_result geo_geometry_is_closed(struct geo_geometry const* geometry,
                                       bool* is_closed);

/**
 * \brief determines if a geo_geometry is considered a simple geometry.
 *
 * \details a simple geometry is one where the segments that form the geometry
 *          do not intersect with each other.
 *
 * \param[in] geometry The geometry to test.
 * \param[out] is_simple The result of "is simple" test.
 *
 * \return enum geo_result indicating whether or not the operation was
 * successful. the `is_simple` out value should only be used when geo_result ==
 * GEO_SUCCESS. Possible geo_result values are:
 *         - GEO_SUCCESS (0)
 *         - GEO_ERR_NULL_POINTER (1)
 *         - GEO_ERR_TOO_SMALL (2)
 */
enum geo_result geo_geometry_is_simple(struct geo_geometry const* geometry,
                                       bool* is_simple);

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
 * \param[in] point The point to test
 * \param[in] geometry The geometry to test if the point is inside.
 * \param[in] strict Controls whether a point on a segment is considered in or
 * out of the geometry.
 * \param[out] is_inside The result of "is inside" test, indicating whether the
 * point is in the geometry.
 *
 * \return enum geo_result indicating whether or not the operation was
 * successful. the `is_inside` out value should only be used when geo_result ==
 * GEO_SUCCESS. Possible geo_result values are:
 *         - GEO_SUCCESS (0)
 *         - GEO_ERR_NULL_POINTER (1)
 *         - GEO_ERR_TOO_SMALL (2)
 */
enum geo_result geo_point_in_geometry(struct geo_point const* point,
                                      struct geo_geometry const* geometry,
                                      bool strict, bool* is_inside);

/**
 * \brief determines if one geometry (called `child`) is entirely contained in
 *        the other geometry (called `parent`)
 *
 * \warning this function might produce unexpected results if
 *          `geo_geometry_is_closed(child) != 1 ||
 *          geo_geometry_is_simple(child) != 1 ||
 *          geo_geometry_is_closed(parent) != 1 ||
 *          geo_geometry_is_simple(parent) != 1`. Ensure that your
 *          `geo_geometry` structs meets this condition BEFORE using this
 * function.
 *
 * \details checks that each segment in `child` is entirely contained in
 * `parent` by checking that each segment in the child geo_geometry has a start
 * point and an end point inside the parent geo_geometry using the
 * `geo_point_in_geometry` function.
 *
 * \param[in] parent The containing geometry
 * \param[in] child The geometry to test if it is contained in parent geometry
 * \param[in] strict Controls whether a point on a segment is considered in or
 * \param[out] is_inside The result of "is inside" test, indicating whether the
 * child geometry is entirely in the parent geometry.
 *
 * \return enum geo_result indicating whether or not the operation was
 * successful. the `is_inside` out value should only be used when geo_result ==
 * GEO_SUCCESS. Possible geo_result values are:
 *         - GEO_SUCCESS (0)
 *         - GEO_ERR_NULL_POINTER (1)
 *         - GEO_ERR_TOO_SMALL (2)
 */
enum geo_result geo_geometry_in_geometry(struct geo_geometry* parent,
                             struct geo_geometry* child, bool strict, bool * is_inside);

/**
 * \brief creates a convex hull from the given points.
 *
 * \details uses Graham's Scan algorithm to create a convex hull from the
 * points. This algorithm is used because it minimizes the segments needed to
 * create the geometry with the tradeoff being an increased area of the
 * geometry.
 *
 * \param[in] points The set of points used to create the convex hull.
 * \param[out] convex_hull The set of points, in order, that create the convex
 * hull.
 * \param[in] size The number of points in both the points and convex hull
 * arrays.
 * \param[out] convex_hull_size The number of points, N, in the convex_hull array that
 * form the convex hull of the point cloud. Note that N will be on the range 3 <= N <= size.
 *
 * \return enum geo_result indicating whether or not the operation was
 * successful. The `convex_hull` array and `convex_hull_size` values should only
 * be used when geo_result == GEO_SUCCESS
 * Possible geo_result values are:
 *         - GEO_SUCCESS (0)
 *         - GEO_ERR_NULL_POINTER (1)
 *         - GEO_ERR_TOO_SMALL (2)
 */
enum geo_result geo_convex_hull(struct geo_point** points, struct geo_point** convex_hull,
                    size_t size, size_t * convex_hull_size);

#ifdef __cplusplus
}
#endif
#endif
