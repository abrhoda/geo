#include "../src/geo.h"
#include <assert.h>
#include <stdio.h>

/*----------------------------------
 * geo_points_equal tests
 *----------------------------------
 */
void geo_points_equal_returns_geo_err_null_pointer_result_code_when_lhs_is_null(void) {
  struct geo_point point = {0.0F, 0.0F};
  bool is_eq = false;
  enum geo_result result = geo_points_equal(NULL, &point, &is_eq);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_points_equal_returns_geo_err_null_pointer_result_code_when_rhs_is_null(void) {
  struct geo_point point = {0.0F, 0.0F};
  bool is_eq = false;
  enum geo_result result = geo_points_equal(&point, NULL, &is_eq);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_points_equal_returns_geo_success_and_is_equal_set_to_1_when_lhs_and_rhs_are_exactly_equal(void) {
  struct geo_point point1 = {1.5F, 2.0F};
  struct geo_point point2 = {1.5F, 2.0F};
  bool is_eq = false;
  enum geo_result result = geo_points_equal(&point1, &point2, &is_eq);
  assert(result == GEO_SUCCESS);
  assert(is_eq == true);
}

void geo_points_equal_returns_geo_success_and_is_equal_set_to_1_when_lhs_x_and_y_and_rhs_x_and_y_are_within_epsilon(void) {
  struct geo_point point1 = {1.49999999F, 2.000000001F};
  struct geo_point point2 = {1.5F, 2.0F};
  bool is_eq = false;
  enum geo_result result = geo_points_equal(&point1, &point2, &is_eq);
  assert(result == GEO_SUCCESS);
  assert(is_eq == true);
}

void geo_points_equal_returns_geo_success_and_is_equal_set_to_0_when_lhs_only_x_and_rhs_only_x_are_within_epsilon(void) {
  struct geo_point point1 = {2.0F, 2.000000001F};
  struct geo_point point2 = {1.5F, 2.0F};
  bool is_eq = false;
  enum geo_result result = geo_points_equal(&point1, &point2, &is_eq);
  assert(result == GEO_SUCCESS);
  assert(is_eq == false);
}

void geo_points_equal_returns_geo_success_and_is_equal_set_to_0_when_lhs_neither_x_or_y_and_rhs_x_or_y_are_within_epsilon(void) {
  struct geo_point point1 = {2.0F, 3.0F};
  struct geo_point point2 = {1.5F, 2.0F};
  bool is_eq = false;
  enum geo_result result = geo_points_equal(&point1, &point2, &is_eq);
  assert(result == GEO_SUCCESS);
  assert(is_eq == false);
}

/*----------------------------------
 * geo_segments_intersect tests
 * TODO all these functions have old names from before the result enum return type.
 *----------------------------------
 */
void geo_segments_intersect_returns_geo_err_null_pointer_result_code_when_segment_1_is_null(void) {
  struct geo_point point1 = {2.0F, 3.0F};
  struct geo_point point2 = {1.5F, 2.0F};
  struct geo_segment segment;
  enum geo_result result = 0;
  size_t intersect_count = 0;
  segment.start = &point1;
  segment.end = &point2;
  result = geo_segments_intersect(NULL, &segment, &intersect_count);
  assert(result == GEO_ERR_NULL_POINTER);
}
void geo_segments_intersect_returns_geo_err_null_pointer_result_code_when_segment_2_is_null(void) {
  struct geo_point point1 = {2.0F, 3.0F};
  struct geo_point point2 = {1.5F, 2.0F};
  struct geo_segment segment;
  enum geo_result result = 0;
  size_t intersect_count = 0;
  segment.start = &point1;
  segment.end = &point2;
  result = geo_segments_intersect(&segment, NULL, &intersect_count);
  assert(result == GEO_ERR_NULL_POINTER);
}
void geo_segments_intersect_returns_geo_err_null_pointer_result_code_when_segment_1_start_is_null(void) {
  /*struct geo_point point1 = {2.0F, 3.0F};*/
  struct geo_point point2 = {1.5F, 2.0F};
  struct geo_point point3 = {7.0F, 3.0F};
  struct geo_point point4 = {6.5F, 2.0F};
  struct geo_segment segment1;
  struct geo_segment segment2;
  enum geo_result result = 0;
  size_t intersect_count = 0;
  segment1.start = NULL;
  segment1.end = &point2;
  segment2.start = &point3;
  segment2.end = &point4;
  result = geo_segments_intersect(&segment1, &segment2, &intersect_count);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_segments_intersect_returns_geo_err_null_pointer_result_code_when_segment_1_end_is_null(void) {
  struct geo_point point1 = {2.0F, 3.0F};
  /*struct geo_point point2 = {1.5F, 2.0F};*/
  struct geo_point point3 = {7.0F, 3.0F};
  struct geo_point point4 = {6.5F, 2.0F};
  struct geo_segment segment1;
  struct geo_segment segment2;
  enum geo_result result = 0;
  size_t intersect_count = 0;
  segment1.start = &point1;
  segment1.end = NULL;
  segment2.start = &point3;
  segment2.end = &point4;
  result = geo_segments_intersect(&segment1, &segment2, &intersect_count);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_segments_intersect_returns_geo_err_null_pointer_result_code_when_segment_2_start_is_null(void) {
  struct geo_point point1 = {2.0F, 3.0F};
  struct geo_point point2 = {1.5F, 2.0F};
  /*struct geo_point point3 = {7.0F, 3.0F};*/
  struct geo_point point4 = {6.5F, 2.0F};
  struct geo_segment segment1;
  struct geo_segment segment2;
  enum geo_result result = 0;
  size_t intersect_count = 0;
  segment1.start = &point1;
  segment1.end = &point2;
  segment2.start = NULL;
  segment2.end = &point4;
  result = geo_segments_intersect(&segment1, &segment2, &intersect_count);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_segments_intersect_returns_geo_err_null_pointer_result_code_when_segment_2_end_is_null(void) {
  struct geo_point point1 = {2.0F, 3.0F};
  struct geo_point point2 = {1.5F, 2.0F};
  struct geo_point point3 = {7.0F, 3.0F};
  /*struct geo_point point4 = {6.5F, 2.0F};*/
  struct geo_segment segment1;
  struct geo_segment segment2;
  enum geo_result result = 0;
  size_t intersect_count = 0;
  segment1.start = &point1;
  segment1.end = &point2;
  segment2.start = &point3;
  segment2.end = NULL;
  result = geo_segments_intersect(&segment1, &segment2, &intersect_count);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_segments_intersect_returns_geo_success_and_intersect_count_is_0_when_segments_are_parallel(void) {
  struct geo_point point1 = {0.0F, 3.0F};
  struct geo_point point2 = {3.0F, 3.0F};
  struct geo_point point3 = {0.0F, 4.0F};
  struct geo_point point4 = {3.0F, 4.0F};
  struct geo_segment segment1;
  struct geo_segment segment2;
  enum geo_result result = 0;
  size_t intersect_count = 0;
  segment1.start = &point1;
  segment1.end = &point2;
  segment2.start = &point3;
  segment2.end = &point4;
  result = geo_segments_intersect(&segment1, &segment2, &intersect_count);
  assert(result == GEO_SUCCESS);
  assert(intersect_count == 0);
}

void geo_segments_intersect_returns_geo_success_and_intersect_count_is_0_when_segments_are_colinear_but_dont_intersect(void) {
  struct geo_point point1 = {0.0F, 0.0F};
  struct geo_point point2 = {1.0F, 0.0F};
  struct geo_point point3 = {2.0F, 0.0F};
  struct geo_point point4 = {3.0F, 0.0F};
  struct geo_segment segment1;
  struct geo_segment segment2;
  enum geo_result result = 0;
  size_t intersect_count = 0;
  segment1.start = &point1;
  segment1.end = &point2;
  segment2.start = &point3;
  segment2.end = &point4;
  result = geo_segments_intersect(&segment1, &segment2, &intersect_count);
  assert(result == GEO_SUCCESS);
  assert(intersect_count == 0);
}

void geo_segments_intersect_returns_geo_success_and_intersect_count_is_0_when_segments_dont_intersect(void) {
  struct geo_point point1 = {0.0F, 0.0F};
  struct geo_point point2 = {1.0F, 1.0F};
  struct geo_point point3 = {2.0F, 3.0F};
  struct geo_point point4 = {3.0F, 5.0F};
  struct geo_segment segment1;
  struct geo_segment segment2;
  enum geo_result result = 0;
  size_t intersect_count = 0;
  segment1.start = &point1;
  segment1.end = &point2;
  segment2.start = &point3;
  segment2.end = &point4;
  result = geo_segments_intersect(&segment1, &segment2, &intersect_count);
  assert(result == GEO_SUCCESS);
  assert(intersect_count == 0);
}

void geo_segments_intersect_returns_geo_success_and_intersect_count_is_1_when_segments_properly_intersect(void) {
  /*
   * p3    p2
   * |     |
   * o     o
   *  \   /
   *   \ /
   *    o
   *   / \
   *  /   \
   * o     o
   * |     |
   * p1    p4
   */

  struct geo_point point1 = {0.0F, 0.0F};
  struct geo_point point2 = {1.0F, 1.0F};
  struct geo_point point3 = {0.0F, 1.0F};
  struct geo_point point4 = {1.0F, 0.0F};
  struct geo_segment segment1;
  struct geo_segment segment2;
  enum geo_result result = 0;
  size_t intersect_count = 0;
  segment1.start = &point1;
  segment1.end = &point2;
  segment2.start = &point3;
  segment2.end = &point4;
  result = geo_segments_intersect(&segment1, &segment2, &intersect_count);
  assert(result == GEO_SUCCESS);
  assert(intersect_count == 1);
}

void geo_segments_intersect_returns_geo_success_and_intersect_count_is_2_when_segment_1_end_is_equal_to_segment_2_start(void) {
  /*
   * o-----o
   * |    /|
   * p3  / p2 + p4
   *    /
   *   /
   *  /
   * o
   * |
   * p1
   *
   */
  struct geo_point point1 = {0.0F, 0.0F};
  struct geo_point point2 = {1.0F, 1.0F};
  struct geo_point point3 = {0.0F, 1.0F};
  struct geo_point point4 = {1.0F, 1.0F};
  struct geo_segment segment1;
  struct geo_segment segment2;
  enum geo_result result = 0;
  size_t intersect_count = 0;
  segment1.start = &point1;
  segment1.end = &point2;
  segment2.start = &point3;
  segment2.end = &point4;
  result = geo_segments_intersect(&segment1, &segment2, &intersect_count);
  assert(result == GEO_SUCCESS);
  assert(intersect_count == 2);
}

void geo_segments_intersect_returns_geo_success_and_intersect_count_is_2_when_one_segment_is_section_of_other_segment(void) {
  /*
   * o----o----o----o
   * |    |    |    |
   * p1   p3   p4   p2
   *
   */
  struct geo_point point1 = {0.0F, 0.0F};
  struct geo_point point2 = {2.0F, 0.0F};
  struct geo_point point3 = {1.0F, 0.0F};
  struct geo_point point4 = {1.5F, 0.0F};
  struct geo_segment segment1;
  struct geo_segment segment2;
  enum geo_result result = 0;
  size_t intersect_count = 0;
  segment1.start = &point1;
  segment1.end = &point2;
  segment2.start = &point3;
  segment2.end = &point4;
  result = geo_segments_intersect(&segment1, &segment2, &intersect_count);
  assert(result == GEO_SUCCESS);
  assert(intersect_count == 2);
}

void geo_segments_intersect_returns_geo_success_and_intersect_count_is_3_when_segment_1_is_section_of_segment_2_and_share_1_end(void) {
  /*
   * o----o--------o
   * |    |        |
   * p1   p3    p2 + p4
   * */
  struct geo_point point1 = {0.0F, 0.0F};
  struct geo_point point2 = {2.0F, 0.0F};
  struct geo_point point3 = {1.0F, 0.0F};
  struct geo_point point4 = {2.0F, 0.0F};
  struct geo_segment segment1;
  struct geo_segment segment2;
  enum geo_result result = 0;
  size_t intersect_count = 0;
  segment1.start = &point1;
  segment1.end = &point2;
  segment2.start = &point3;
  segment2.end = &point4;
  result = geo_segments_intersect(&segment1, &segment2, &intersect_count);
  assert(result == GEO_SUCCESS);
  assert(intersect_count == 3);
}

void geo_segments_intersect_returns_geo_success_and_intersect_count_is_4_when_segment_1_is_the_same_segment_as_segment_2(void) {
  /*
   * o--------------o
   * |              |
   * p1+p3          p2+p4
   */
  struct geo_point point1 = {0.0F, 0.0F};
  struct geo_point point2 = {2.0F, 0.0F};
  struct geo_point point3 = {0.0F, 0.0F};
  struct geo_point point4 = {2.0F, 0.0F};
  struct geo_segment segment1;
  struct geo_segment segment2;
  enum geo_result result = 0;
  size_t intersect_count = 0;
  segment1.start = &point1;
  segment1.end = &point2;
  segment2.start = &point3;
  segment2.end = &point4;
  result = geo_segments_intersect(&segment1, &segment2, &intersect_count);
  assert(result == GEO_SUCCESS);
  assert(intersect_count == 4);
}


/*----------------------------------
 * geo_geometry_is_closed tests
 *----------------------------------
 */
void geo_geometry_is_closed_returns_geo_err_null_pointer_when_geometry_is_null(void) {
  struct geo_geometry * geometry = NULL;
  bool is_closed = false;
  enum geo_result result = geo_geometry_is_closed(geometry, &is_closed);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_geometry_is_closed_returns_geo_err_null_pointer_when_geometry_segments_is_null(void) {
  struct geo_geometry geometry;
  geometry.segments_count = 0;
  geometry.segments = NULL;
  bool is_closed = false;
  enum geo_result result = geo_geometry_is_closed(&geometry, &is_closed);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_geometry_is_closed_returns_geo_err_null_pointer_when_geometry_segment_start_is_null(void) {
  struct geo_point start1 = {0.0F, 0.0F};
  struct geo_point end1 = {3.0F, 0.0F};
  struct geo_point start2 = {3.0F, 0.0F};
  struct geo_point start3 = {1.5F, 3.0F};
  struct geo_point end3 = {0.0F, 0.0F};
  struct geo_segment segment1;
  struct geo_segment segment2;
  struct geo_segment segment3;
  struct geo_segment * segments[3];
  struct geo_geometry geometry;
  segment1.start = &start1;
  segment1.end = &end1;
  segments[0] = &segment1;
  segment2.start = &start2;
  segment2.end = NULL;
  segments[1] = &segment2;
  segment3.start = &start3;
  segment3.end = &end3;
  segments[2] = &segment3;
  geometry.segments_count = 3;
  geometry.segments = segments;

  bool is_closed = false;
  enum geo_result result = geo_geometry_is_closed(&geometry, &is_closed);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_geometry_is_closed_returns_geo_err_null_pointer_when_geometry_segment_end_is_null(void) {
  struct geo_point start1 = {0.0F, 0.0F};
  struct geo_point end1 = {3.0F, 0.0F};
  /*struct geo_point start2 = {3.0F, 0.0F};*/
  struct geo_point end2 = {1.5F, 3.0F};
  struct geo_point start3 = {1.5F, 3.0F};
  struct geo_point end3 = {0.0F, 0.0F};
  struct geo_segment segment1;
  struct geo_segment segment2;
  struct geo_segment segment3;
  struct geo_segment * segments[3];
  struct geo_geometry geometry;
  segment1.start = &start1;
  segment1.end = &end1;
  segments[0] = &segment1;
  segment2.start = NULL;
  segment2.end = &end2;
  segments[1] = &segment2;
  segment3.start = &start3;
  segment3.end = &end3;
  segments[2] = &segment3;
  geometry.segments_count = 3;
  geometry.segments = segments;

  bool is_closed = false;
  enum geo_result result = geo_geometry_is_closed(&geometry, &is_closed);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_geometry_is_closed_returns_geo_err_too_small_when_geometry_segment_count_less_than_3(void) {
  struct geo_point start1 = {2.0F, 0.0F};
  struct geo_point end1 = {3.0F, 0.0F};
  struct geo_point start2 = {3.0F, 0.0F};
  struct geo_point end2 = {6.0F, 1.0F};
  struct geo_segment segment1;
  struct geo_segment segment2;
  struct geo_segment * segments[2];
  struct geo_geometry geometry;
  segment1.start = &start1;
  segment1.end = &end1;
  segments[0] = &segment1;
  segment2.start = &start2;
  segment2.end = &end2;
  segments[1] = &segment2;
  geometry.segments_count = 2;
  geometry.segments = segments;

  bool is_closed = false;
  enum geo_result result = geo_geometry_is_closed(&geometry, &is_closed);
  assert(result == GEO_ERR_TOO_SMALL);
}

void geo_geometry_is_closed_returns_geo_success_and_is_closed_is_false_when_nth_segments_end_doesnt_equal_n_plus_1_segment_start(void) {
  struct geo_point start1 = {0.0F, 0.0F};
  struct geo_point end1 = {3.0F, 0.0F};
  struct geo_point start2 = {3.0F, 0.0F};
  struct geo_point end2 = {1.5F, 3.0F};
  struct geo_point start3 = {1.5F, 3.0F};

  /* GAP HERE */
  struct geo_point end3 = {0.1F, 0.1F};
  struct geo_segment segment1;
  struct geo_segment segment2;
  struct geo_segment segment3;
  struct geo_segment * segments[3];
  struct geo_geometry geometry;
  segment1.start = &start1;
  segment1.end = &end1;
  segments[0] = &segment1;
  segment2.start = &start2;
  segment2.end = &end2;
  segments[1] = &segment2;
  segment3.start = &start3;
  segment3.end = &end3;
  segments[2] = &segment3;
  geometry.segments_count = 3;
  geometry.segments = segments;

  bool is_closed = false;
  enum geo_result result = geo_geometry_is_closed(&geometry, &is_closed);
  assert(result == GEO_SUCCESS);
  assert(is_closed == false);
}

void geo_geometry_is_closed_returns_geo_success_and_is_closed_is_true_when_nth_segments_end_equals_n_plus_1_segments_start(void) {
  struct geo_point start1 = {0.0F, 0.0F};
  struct geo_point end1 = {3.0F, 0.0F};
  struct geo_point start2 = {3.0F, 0.0F};
  struct geo_point end2 = {1.5F, 3.0F};
  struct geo_point start3 = {1.5F, 3.0F};
  struct geo_point end3 = {0.0F, 0.0F};
  struct geo_segment segment1;
  struct geo_segment segment2;
  struct geo_segment segment3;
  struct geo_segment * segments[3];
  struct geo_geometry geometry;
  segment1.start = &start1;
  segment1.end = &end1;
  segments[0] = &segment1;
  segment2.start = &start2;
  segment2.end = &end2;
  segments[1] = &segment2;
  segment3.start = &start3;
  segment3.end = &end3;
  segments[2] = &segment3;
  geometry.segments_count = 3;
  geometry.segments = segments;

  bool is_closed = false;
  enum geo_result result = geo_geometry_is_closed(&geometry, &is_closed);
  assert(result == GEO_SUCCESS);
  assert(is_closed == true);
}

/*----------------------------------
 * geo_geometry_is_simple tests
 *----------------------------------
 */
void geo_geometry_is_simple_returns_geo_err_null_pointer_when_geometry_is_null(void) {
  struct geo_geometry * geometry = NULL;
  bool is_simple = false;
  enum geo_result result = geo_geometry_is_simple(geometry, &is_simple);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_geometry_is_simple_returns_geo_err_null_pointer_when_geometry_segments_is_null(void) {
  struct geo_geometry geometry;
  geometry.segments_count = 0;
  geometry.segments = NULL;

  bool is_simple = false;
  enum geo_result result = geo_geometry_is_simple(&geometry, &is_simple);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_geometry_is_simple_returns_geo_err_null_pointer_when_geometry_segments_ith_start_is_null(void) {
  struct geo_point start1 = {0.0F, 0.0F};
  struct geo_point end1 = {3.0F, 0.0F};
  struct geo_point start2 = {3.0F, 0.0F};
  struct geo_point end2 = {3.0F, 3.0F};
  struct geo_point start3 = {3.0F, 3.0F};
  struct geo_point end3 = {0.0F, 3.0F};
  struct geo_point start4 = {0.0F, 3.0F};
  struct geo_point end4 = {0.0F, 0.0F};
  struct geo_segment segment1;
  struct geo_segment segment2;
  struct geo_segment segment3;
  struct geo_segment segment4;
  struct geo_segment * segments[4];
  struct geo_geometry geometry;
  segment1.start = &start1;
  segment1.end = &end1;
  segments[0] = &segment1;
  segment2.start = NULL;
  segment2.end = &end2;
  segments[1] = &segment2;
  segment3.start = &start3;
  segment3.end = &end3;
  segments[2] = &segment3;
  segment4.start = &start4;
  segment4.end = &end4;
  segments[3] = &segment4;
  geometry.segments_count = 4;
  geometry.segments = segments;

  bool is_simple = false;
  enum geo_result result = geo_geometry_is_simple(&geometry, &is_simple);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_geometry_is_simple_returns_geo_err_null_pointer_when_geometry_segments_ith_end_is_null(void) {
  struct geo_point start1 = {0.0F, 0.0F};
  struct geo_point end1 = {3.0F, 0.0F};
  struct geo_point start2 = {3.0F, 0.0F};
  struct geo_point end2 = {3.0F, 3.0F};
  struct geo_point start3 = {3.0F, 3.0F};
  struct geo_point end3 = {0.0F, 3.0F};
  struct geo_point start4 = {0.0F, 3.0F};
  struct geo_point end4 = {0.0F, 0.0F};
  struct geo_segment segment1;
  struct geo_segment segment2;
  struct geo_segment segment3;
  struct geo_segment segment4;
  struct geo_segment * segments[4];
  struct geo_geometry geometry;
  segment1.start = &start1;
  segment1.end = &end1;
  segments[0] = &segment1;
  segment2.start = &start2;
  segment2.end = NULL;
  segments[1] = &segment2;
  segment3.start = &start3;
  segment3.end = &end3;
  segments[2] = &segment3;
  segment4.start = &start4;
  segment4.end = &end4;
  segments[3] = &segment4;
  geometry.segments_count = 4;
  geometry.segments = segments;

  bool is_simple = false;
  enum geo_result result = geo_geometry_is_simple(&geometry, &is_simple);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_geometry_is_simple_returns_geo_err_too_small_when_geometry_segments_count_less_than_3(void) {
  struct geo_point start1 = {0.0F, 0.0F};
  struct geo_point end1 = {3.0F, 0.0F};
  struct geo_point start2 = {3.0F, 0.0F};
  struct geo_point end2 = {3.0F, 3.0F};
  struct geo_segment segment1;
  struct geo_segment segment2;
  struct geo_segment * segments[2];
  struct geo_geometry geometry;
  segment1.start = &start1;
  segment1.end = &end1;
  segments[0] = &segment1;
  segment2.start = &start2;
  segment2.end = &end2;
  segments[1] = &segment2;
  geometry.segments_count = 2;
  geometry.segments = segments;

  bool is_simple = false;
  enum geo_result result = geo_geometry_is_simple(&geometry, &is_simple);
  assert(result == GEO_ERR_TOO_SMALL);
}

void geo_geometry_is_simple_returns_geo_success_and_is_simple_is_false_when_any_segments_intersect(void) {
  struct geo_point start1 = {0.0F, 0.0F};
  struct geo_point end1 = {3.0F, 3.0F};
  struct geo_point start2 = {3.0F, 3.0F};
  struct geo_point end2 = {3.0F, 0.0F};
  struct geo_point start3 = {3.0F, 0.0F};
  struct geo_point end3 = {0.0F, 3.0F};
  struct geo_point start4 = {0.0F, 3.0F};
  struct geo_point end4 = {0.0F, 0.0F};
  struct geo_segment segment1;
  struct geo_segment segment2;
  struct geo_segment segment3;
  struct geo_segment segment4;
  struct geo_segment * segments[4];
  struct geo_geometry geometry;
  segment1.start = &start1;
  segment1.end = &end1;
  segments[0] = &segment1;
  segment2.start = &start2;
  segment2.end = &end2;
  segments[1] = &segment2;
  segment3.start = &start3;
  segment3.end = &end3;
  segments[2] = &segment3;
  segment4.start = &start4;
  segment4.end = &end4;
  segments[3] = &segment4;
  geometry.segments_count = 4;
  geometry.segments = segments;

  bool is_simple = false;
  enum geo_result result = geo_geometry_is_simple(&geometry, &is_simple);
  assert(result == GEO_SUCCESS);
  assert(is_simple == false);
}

void geo_geometry_is_simple_returns_geo_success_and_is_simple_is_true_when_no_segments_intersect(void) {
  struct geo_point start1 = {0.0F, 0.0F};
  struct geo_point end1 = {3.0F, 0.0F};
  struct geo_point start2 = {3.0F, 0.0F};
  struct geo_point end2 = {3.0F, 3.0F};
  struct geo_point start3 = {3.0F, 3.0F};
  struct geo_point end3 = {0.0F, 3.0F};
  struct geo_point start4 = {0.0F, 3.0F};
  struct geo_point end4 = {0.0F, 0.0F};
  struct geo_segment segment1;
  struct geo_segment segment2;
  struct geo_segment segment3;
  struct geo_segment segment4;
  struct geo_segment * segments[4];
  struct geo_geometry geometry;
  segment1.start = &start1;
  segment1.end = &end1;
  segments[0] = &segment1;
  segment2.start = &start2;
  segment2.end = &end2;
  segments[1] = &segment2;
  segment3.start = &start3;
  segment3.end = &end3;
  segments[2] = &segment3;
  segment4.start = &start4;
  segment4.end = &end4;
  segments[3] = &segment4;
  geometry.segments_count = 4;
  geometry.segments = segments;

  bool is_simple = false;
  enum geo_result result = geo_geometry_is_simple(&geometry, &is_simple);
  assert(result == GEO_SUCCESS);
  assert(is_simple == true);
}

/*----------------------------------
 * geo_point_in_geometry tests
 *----------------------------------
 */
void geo_point_in_geometry_returns_negative_1_when_point_is_null(void) {
  struct geo_geometry geometry;
  struct geo_segment * segments[3];
  bool strict = true;
  bool inside = false;
  geometry.segments = segments;
  geometry.segments_count = 3;
  enum geo_result result = geo_point_in_geometry(NULL, &geometry, strict, &inside);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_point_in_geometry_returns_negative_1_when_geometry_is_null(void) {
  struct geo_point point = { 0.0F, 0.0F };
  bool strict = true;
  bool inside = false;
  enum geo_result result = geo_point_in_geometry(&point, NULL, strict, &inside);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_point_in_geometry_returns_negative_1_when_geometry_segments_is_null(void) {
  struct geo_geometry geometry;
  struct geo_point point = { 0.0F, 0.0F };
  bool strict = true;
  bool inside = false;
  geometry.segments = NULL;
  geometry.segments_count = 3;

  enum geo_result result = geo_point_in_geometry(&point, &geometry, strict, &inside);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_point_in_geometry_returns_negative_1_when_geometry_segments_ith_start_is_null(void) {
  bool strict = true;
  bool inside = false;
  struct geo_point point = {1.5F, 1.5F};
  struct geo_point start1 = {0.0F, 0.0F};
  struct geo_point end1 = {3.0F, 0.0F};
  struct geo_point start2 = {3.0F, 0.0F};
  struct geo_point end2 = {3.0F, 3.0F};
  struct geo_point start3 = {3.0F, 3.0F};
  struct geo_point end3 = {0.0F, 3.0F};
  struct geo_point start4 = {0.0F, 3.0F};
  struct geo_point end4 = {0.0F, 0.0F};
  struct geo_segment segment1;
  struct geo_segment segment2;
  struct geo_segment segment3;
  struct geo_segment segment4;
  struct geo_segment * segments[4];
  struct geo_geometry geometry;
  segment1.start = &start1;
  segment1.end = &end1;
  segments[0] = &segment1;
  segment2.start = &start2;
  segment2.end = &end2;
  segments[1] = &segment2;
  segment3.start = NULL;
  segment3.end = &end3;
  segments[2] = &segment3;
  segment4.start = &start4;
  segment4.end = &end4;
  segments[3] = &segment4;
  geometry.segments_count = 4;
  geometry.segments = segments;

  enum geo_result result = geo_point_in_geometry(&point, &geometry, strict, &inside);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_point_in_geometry_returns_negative_1_when_geometry_segments_ith_end_is_null(void) {
  bool strict = true;
  bool inside = false;
  struct geo_point point = {1.5F, 1.5F};
  struct geo_point start1 = {0.0F, 0.0F};
  struct geo_point end1 = {3.0F, 0.0F};
  struct geo_point start2 = {3.0F, 0.0F};
  struct geo_point end2 = {3.0F, 3.0F};
  struct geo_point start3 = {3.0F, 3.0F};
  struct geo_point end3 = {0.0F, 3.0F};
  struct geo_point start4 = {0.0F, 3.0F};
  struct geo_point end4 = {0.0F, 0.0F};
  struct geo_segment segment1;
  struct geo_segment segment2;
  struct geo_segment segment3;
  struct geo_segment segment4;
  struct geo_segment * segments[4];
  struct geo_geometry geometry;
  segment1.start = &start1;
  segment1.end = &end1;
  segments[0] = &segment1;
  segment2.start = &start2;
  segment2.end = &end2;
  segments[1] = &segment2;
  segment3.start = &start3;
  segment3.end = NULL;
  segments[2] = &segment3;
  segment4.start = &start4;
  segment4.end = &end4;
  segments[3] = &segment4;
  geometry.segments_count = 4;
  geometry.segments = segments;

  enum geo_result result = geo_point_in_geometry(&point, &geometry, strict, &inside);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_point_in_geometry_returns_0_when_geometry_segments_count_is_less_than_3(void) {
  bool strict = true;
  bool inside = false;
  struct geo_point point = {1.5F, 1.5F};
  struct geo_point start1 = {0.0F, 0.0F};
  struct geo_point end1 = {3.0F, 0.0F};
  struct geo_point start2 = {3.0F, 0.0F};
  struct geo_point end2 = {3.0F, 3.0F};
  struct geo_segment segment1;
  struct geo_segment segment2;
  struct geo_segment * segments[2];
  struct geo_geometry geometry;
  segment1.start = &start1;
  segment1.end = &end1;
  segments[0] = &segment1;
  segment2.start = &start2;
  segment2.end = &end2;
  segments[1] = &segment2;
  geometry.segments_count = 2;
  geometry.segments = segments;

  enum geo_result result = geo_point_in_geometry(&point, &geometry, strict, &inside);
  assert(result == GEO_ERR_TOO_SMALL);

}

void geo_point_in_geometry_returns_0_when_point_on_geometry_segment_and_strict_is_1(void) {
  bool strict = true;
  bool inside = false;
  struct geo_point point = {3.0F, 1.5F};
  struct geo_point start1 = {0.0F, 0.0F};
  struct geo_point end1 = {3.0F, 0.0F};
  struct geo_point start2 = {3.0F, 0.0F};
  struct geo_point end2 = {3.0F, 3.0F};
  struct geo_point start3 = {3.0F, 3.0F};
  struct geo_point end3 = {0.0F, 3.0F};
  struct geo_point start4 = {0.0F, 3.0F};
  struct geo_point end4 = {0.0F, 0.0F};
  struct geo_segment segment1;
  struct geo_segment segment2;
  struct geo_segment segment3;
  struct geo_segment segment4;
  struct geo_segment * segments[4];
  struct geo_geometry geometry;
  segment1.start = &start1;
  segment1.end = &end1;
  segments[0] = &segment1;
  segment2.start = &start2;
  segment2.end = &end2;
  segments[1] = &segment2;
  segment3.start = &start3;
  segment3.end = &end3;
  segments[2] = &segment3;
  segment4.start = &start4;
  segment4.end = &end4;
  segments[3] = &segment4;
  geometry.segments_count = 4;
  geometry.segments = segments;

  enum geo_result result = geo_point_in_geometry(&point, &geometry, strict, &inside);
  assert(result == GEO_SUCCESS);
  assert(inside == false);
}

void geo_point_in_geometry_returns_1_when_point_on_geometry_segment_and_strict_is_0(void) {
  bool strict = false;
  bool inside = false;
  struct geo_point point = {3.0F, 1.5F};
  struct geo_point start1 = {0.0F, 0.0F};
  struct geo_point end1 = {3.0F, 0.0F};
  struct geo_point start2 = {3.0F, 0.0F};
  struct geo_point end2 = {3.0F, 3.0F};
  struct geo_point start3 = {3.0F, 3.0F};
  struct geo_point end3 = {0.0F, 3.0F};
  struct geo_point start4 = {0.0F, 3.0F};
  struct geo_point end4 = {0.0F, 0.0F};
  struct geo_segment segment1;
  struct geo_segment segment2;
  struct geo_segment segment3;
  struct geo_segment segment4;
  struct geo_segment * segments[4];
  struct geo_geometry geometry;
  segment1.start = &start1;
  segment1.end = &end1;
  segments[0] = &segment1;
  segment2.start = &start2;
  segment2.end = &end2;
  segments[1] = &segment2;
  segment3.start = &start3;
  segment3.end = &end3;
  segments[2] = &segment3;
  segment4.start = &start4;
  segment4.end = &end4;
  segments[3] = &segment4;
  geometry.segments_count = 4;
  geometry.segments = segments;

  enum geo_result result = geo_point_in_geometry(&point, &geometry, strict, &inside);
  assert(result == GEO_SUCCESS);
  assert(inside == true);
}

void geo_point_in_geometry_returns_0_when_point_is_to_the_left_of_the_geometry_and_colinear_with_horizontal_segment(void) {
  bool strict = true;
  bool inside = false;
  struct geo_point point = {3.0F, -1.0F};
  struct geo_point start1 = {0.0F, 0.0F};
  struct geo_point end1 = {3.0F, 0.0F};
  struct geo_point start2 = {3.0F, 0.0F};
  struct geo_point end2 = {3.0F, 3.0F};
  struct geo_point start3 = {3.0F, 3.0F};
  struct geo_point end3 = {0.0F, 3.0F};
  struct geo_point start4 = {0.0F, 3.0F};
  struct geo_point end4 = {0.0F, 0.0F};
  struct geo_segment segment1;
  struct geo_segment segment2;
  struct geo_segment segment3;
  struct geo_segment segment4;
  struct geo_segment * segments[4];
  struct geo_geometry geometry;
  segment1.start = &start1;
  segment1.end = &end1;
  segments[0] = &segment1;
  segment2.start = &start2;
  segment2.end = &end2;
  segments[1] = &segment2;
  segment3.start = &start3;
  segment3.end = &end3;
  segments[2] = &segment3;
  segment4.start = &start4;
  segment4.end = &end4;
  segments[3] = &segment4;
  geometry.segments_count = 4;
  geometry.segments = segments;

  enum geo_result result = geo_point_in_geometry(&point, &geometry, strict, &inside);
  assert(result == GEO_SUCCESS);
  assert(inside == false);
}

void geo_point_in_geometry_returns_0_when_point_is_to_the_right_of_the_geometry_and_colinear_with_horizontal_segment(void) {
  bool strict = true;
  bool inside = false;
  struct geo_point point = {4.0F, 0.0F};
  struct geo_point start1 = {0.0F, 0.0F};
  struct geo_point end1 = {3.0F, 0.0F};
  struct geo_point start2 = {3.0F, 0.0F};
  struct geo_point end2 = {3.0F, 3.0F};
  struct geo_point start3 = {3.0F, 3.0F};
  struct geo_point end3 = {0.0F, 3.0F};
  struct geo_point start4 = {0.0F, 3.0F};
  struct geo_point end4 = {0.0F, 0.0F};
  struct geo_segment segment1;
  struct geo_segment segment2;
  struct geo_segment segment3;
  struct geo_segment segment4;
  struct geo_segment * segments[4];
  struct geo_geometry geometry;
  segment1.start = &start1;
  segment1.end = &end1;
  segments[0] = &segment1;
  segment2.start = &start2;
  segment2.end = &end2;
  segments[1] = &segment2;
  segment3.start = &start3;
  segment3.end = &end3;
  segments[2] = &segment3;
  segment4.start = &start4;
  segment4.end = &end4;
  segments[3] = &segment4;
  geometry.segments_count = 4;
  geometry.segments = segments;

  enum geo_result result = geo_point_in_geometry(&point, &geometry, strict, &inside);
  assert(result == GEO_SUCCESS);
  assert(inside == false);
}

void geo_point_in_geometry_returns_0_when_point_is_above_of_the_geometry_and_colinear_with_vertical_segment(void) {
  bool strict = true;
  bool inside = false;
  struct geo_point point = {0.0F, 4.0F};
  struct geo_point start1 = {0.0F, 0.0F};
  struct geo_point end1 = {3.0F, 0.0F};
  struct geo_point start2 = {3.0F, 0.0F};
  struct geo_point end2 = {3.0F, 3.0F};
  struct geo_point start3 = {3.0F, 3.0F};
  struct geo_point end3 = {0.0F, 3.0F};
  struct geo_point start4 = {0.0F, 3.0F};
  struct geo_point end4 = {0.0F, 0.0F};
  struct geo_segment segment1;
  struct geo_segment segment2;
  struct geo_segment segment3;
  struct geo_segment segment4;
  struct geo_segment * segments[4];
  struct geo_geometry geometry;
  segment1.start = &start1;
  segment1.end = &end1;
  segments[0] = &segment1;
  segment2.start = &start2;
  segment2.end = &end2;
  segments[1] = &segment2;
  segment3.start = &start3;
  segment3.end = &end3;
  segments[2] = &segment3;
  segment4.start = &start4;
  segment4.end = &end4;
  segments[3] = &segment4;
  geometry.segments_count = 4;
  geometry.segments = segments;

  enum geo_result result = geo_point_in_geometry(&point, &geometry, strict, &inside);
  assert(result == GEO_SUCCESS);
  assert(inside == false);
}

void geo_point_in_geometry_returns_0_when_point_is_below_of_the_geometry_and_colinear_with_vertical_segment(void) {
  bool strict = true;
  bool inside = false;
  struct geo_point point = {0.0F, -1.0F};
  struct geo_point start1 = {0.0F, 0.0F};
  struct geo_point end1 = {3.0F, 0.0F};
  struct geo_point start2 = {3.0F, 0.0F};
  struct geo_point end2 = {3.0F, 3.0F};
  struct geo_point start3 = {3.0F, 3.0F};
  struct geo_point end3 = {0.0F, 3.0F};
  struct geo_point start4 = {0.0F, 3.0F};
  struct geo_point end4 = {0.0F, 0.0F};
  struct geo_segment segment1;
  struct geo_segment segment2;
  struct geo_segment segment3;
  struct geo_segment segment4;
  struct geo_segment * segments[4];
  struct geo_geometry geometry;
  segment1.start = &start1;
  segment1.end = &end1;
  segments[0] = &segment1;
  segment2.start = &start2;
  segment2.end = &end2;
  segments[1] = &segment2;
  segment3.start = &start3;
  segment3.end = &end3;
  segments[2] = &segment3;
  segment4.start = &start4;
  segment4.end = &end4;
  segments[3] = &segment4;
  geometry.segments_count = 4;
  geometry.segments = segments;

  enum geo_result result = geo_point_in_geometry(&point, &geometry, strict, &inside);
  assert(result == GEO_SUCCESS);
  assert(inside == false);
}

/*----------------------------------
 * geo_geometry_in_geometry tests
 *----------------------------------
 */
void geo_geometry_in_geometry_returns_negative_1_when_parent_geometry_is_null(void) {
  int result = 0;
  int strict = 1;
  struct geo_point parent_vertex1 = { 0.0F, 0.0F };
  struct geo_point parent_vertex2 = { 5.0F, 0.0F };
  struct geo_point parent_vertex3 = { 5.0F, 5.0F };
  struct geo_point parent_vertex4 = { 0.0F, 5.0F };
  struct geo_point child_vertex1 = { 1.0F, 1.0F };
  struct geo_point child_vertex2 = { 3.0F, 1.0F };
  struct geo_point child_vertex3 = { 3.0F, 3.0F };
  struct geo_point child_vertex4 = { 1.0F, 3.0F };
  struct geo_segment parent_segment1;
  struct geo_segment parent_segment2;
  struct geo_segment parent_segment3;
  struct geo_segment parent_segment4;
  struct geo_segment child_segment1;
  struct geo_segment child_segment2;
  struct geo_segment child_segment3;
  struct geo_segment child_segment4;
  struct geo_segment *parent_segments[4];
  struct geo_segment *child_segments[4];
  struct geo_geometry parent;
  struct geo_geometry child;
  int parent_segments_count = 4;
  int child_segments_count = 4;
  parent_segment1.start = &parent_vertex1;
  parent_segment1.end = &parent_vertex2;
  parent_segments[0] = &parent_segment1;
  parent_segment2.start = &parent_vertex2;
  parent_segment2.end = &parent_vertex3;
  parent_segments[1] = &parent_segment2;
  parent_segment3.start = &parent_vertex3;
  parent_segment3.end = &parent_vertex4;
  parent_segments[2] = &parent_segment3;
  parent_segment4.start = &parent_vertex4;
  parent_segment4.end = &parent_vertex1;
  parent_segments[3] = &parent_segment4;
  parent.segments = parent_segments;
  parent.segments_count = parent_segments_count;

  child_segment1.start = &child_vertex1;
  child_segment1.end = &child_vertex2;
  child_segments[0] = &child_segment1;
  child_segment2.start = &child_vertex2;
  child_segment2.end = &child_vertex3;
  child_segments[1] = &child_segment2;
  child_segment3.start = &child_vertex3;
  child_segment3.end = &child_vertex4;
  child_segments[2] = &child_segment3;
  child_segment4.start = &child_vertex4;
  child_segment4.end = &child_vertex1;
  child_segments[3] = &child_segment4;
  child.segments = child_segments;
  child.segments_count = child_segments_count;
  result = geo_geometry_in_geometry(NULL, &child, strict);
  assert(result == -1);
}

void geo_geometry_in_geometry_returns_negative_1_when_parent_geometry_segments_is_null(void) {
  int result = 0;
  int strict = 1;
  struct geo_point parent_vertex1 = { 0.0F, 0.0F };
  struct geo_point parent_vertex2 = { 5.0F, 0.0F };
  struct geo_point parent_vertex3 = { 5.0F, 5.0F };
  struct geo_point parent_vertex4 = { 0.0F, 5.0F };
  struct geo_point child_vertex1 = { 1.0F, 1.0F };
  struct geo_point child_vertex2 = { 3.0F, 1.0F };
  struct geo_point child_vertex3 = { 3.0F, 3.0F };
  struct geo_point child_vertex4 = { 1.0F, 3.0F };
  struct geo_segment parent_segment1;
  struct geo_segment parent_segment2;
  struct geo_segment parent_segment3;
  struct geo_segment parent_segment4;
  struct geo_segment child_segment1;
  struct geo_segment child_segment2;
  struct geo_segment child_segment3;
  struct geo_segment child_segment4;
  struct geo_segment *parent_segments[4];
  struct geo_segment *child_segments[4];
  struct geo_geometry parent;
  struct geo_geometry child;
  int parent_segments_count = 4;
  int child_segments_count = 4;
  parent_segment1.start = &parent_vertex1;
  parent_segment1.end = &parent_vertex2;
  parent_segments[0] = &parent_segment1;
  parent_segment2.start = &parent_vertex2;
  parent_segment2.end = &parent_vertex3;
  parent_segments[1] = &parent_segment2;
  parent_segment3.start = &parent_vertex3;
  parent_segment3.end = &parent_vertex4;
  parent_segments[2] = &parent_segment3;
  parent_segment4.start = &parent_vertex4;
  parent_segment4.end = &parent_vertex1;
  parent_segments[3] = &parent_segment4;
  parent.segments = NULL;
  parent.segments_count = parent_segments_count;

  child_segment1.start = &child_vertex1;
  child_segment1.end = &child_vertex2;
  child_segments[0] = &child_segment1;
  child_segment2.start = &child_vertex2;
  child_segment2.end = &child_vertex3;
  child_segments[1] = &child_segment2;
  child_segment3.start = &child_vertex3;
  child_segment3.end = &child_vertex4;
  child_segments[2] = &child_segment3;
  child_segment4.start = &child_vertex4;
  child_segment4.end = &child_vertex1;
  child_segments[3] = &child_segment4;
  child.segments = child_segments;
  child.segments_count = child_segments_count;
  result = geo_geometry_in_geometry(&parent, &child, strict);
  assert(result == -1);
}

void geo_geometry_in_geometry_returns_negative_1_when_parent_geometry_ith_segment_is_null(void) {
  int result = 0;
  int strict = 1;
  struct geo_point parent_vertex1 = { 0.0F, 0.0F };
  struct geo_point parent_vertex2 = { 5.0F, 0.0F };
  struct geo_point parent_vertex3 = { 5.0F, 5.0F };
  struct geo_point parent_vertex4 = { 0.0F, 5.0F };
  struct geo_point child_vertex1 = { 1.0F, 1.0F };
  struct geo_point child_vertex2 = { 3.0F, 1.0F };
  struct geo_point child_vertex3 = { 3.0F, 3.0F };
  struct geo_point child_vertex4 = { 1.0F, 3.0F };
  struct geo_segment parent_segment1;
  struct geo_segment parent_segment2;
  struct geo_segment parent_segment3;
  struct geo_segment parent_segment4;
  struct geo_segment child_segment1;
  struct geo_segment child_segment2;
  struct geo_segment child_segment3;
  struct geo_segment child_segment4;
  struct geo_segment *parent_segments[4];
  struct geo_segment *child_segments[4];
  struct geo_geometry parent;
  struct geo_geometry child;
  int parent_segments_count = 4;
  int child_segments_count = 4;
  parent_segment1.start = &parent_vertex1;
  parent_segment1.end = &parent_vertex2;
  parent_segments[0] = &parent_segment1;
  parent_segment2.start = &parent_vertex2;
  parent_segment2.end = &parent_vertex3;
  parent_segments[1] = NULL;
  parent_segment3.start = &parent_vertex3;
  parent_segment3.end = &parent_vertex4;
  parent_segments[2] = &parent_segment3;
  parent_segment4.start = &parent_vertex4;
  parent_segment4.end = &parent_vertex1;
  parent_segments[3] = &parent_segment4;
  parent.segments = parent_segments;
  parent.segments_count = parent_segments_count;

  child_segment1.start = &child_vertex1;
  child_segment1.end = &child_vertex2;
  child_segments[0] = &child_segment1;
  child_segment2.start = &child_vertex2;
  child_segment2.end = &child_vertex3;
  child_segments[1] = &child_segment2;
  child_segment3.start = &child_vertex3;
  child_segment3.end = &child_vertex4;
  child_segments[2] = &child_segment3;
  child_segment4.start = &child_vertex4;
  child_segment4.end = &child_vertex1;
  child_segments[3] = &child_segment4;
  child.segments = child_segments;
  child.segments_count = child_segments_count;
  result = geo_geometry_in_geometry(&parent, &child, strict);
  assert(result == -1);
}

void geo_geometry_in_geometry_returns_negative_1_when_parent_geometry_ith_segment_start_point_is_null(void) {
  int result = 0;
  int strict = 1;
  struct geo_point parent_vertex1 = { 0.0F, 0.0F };
  struct geo_point parent_vertex2 = { 5.0F, 0.0F };
  struct geo_point parent_vertex3 = { 5.0F, 5.0F };
  struct geo_point parent_vertex4 = { 0.0F, 5.0F };
  struct geo_point child_vertex1 = { 1.0F, 1.0F };
  struct geo_point child_vertex2 = { 3.0F, 1.0F };
  struct geo_point child_vertex3 = { 3.0F, 3.0F };
  struct geo_point child_vertex4 = { 1.0F, 3.0F };
  struct geo_segment parent_segment1;
  struct geo_segment parent_segment2;
  struct geo_segment parent_segment3;
  struct geo_segment parent_segment4;
  struct geo_segment child_segment1;
  struct geo_segment child_segment2;
  struct geo_segment child_segment3;
  struct geo_segment child_segment4;
  struct geo_segment *parent_segments[4];
  struct geo_segment *child_segments[4];
  struct geo_geometry parent;
  struct geo_geometry child;
  int parent_segments_count = 4;
  int child_segments_count = 4;
  parent_segment1.start = &parent_vertex1;
  parent_segment1.end = &parent_vertex2;
  parent_segments[0] = &parent_segment1;
  parent_segment2.start = &parent_vertex2;
  parent_segment2.end = &parent_vertex3;
  parent_segments[1] = &parent_segment2;
  parent_segment3.start = &parent_vertex3;
  parent_segment3.end = &parent_vertex4;
  parent_segments[2] = &parent_segment3;
  parent_segment4.start = NULL;
  parent_segment4.end = &parent_vertex1;
  parent_segments[3] = &parent_segment4;
  parent.segments = parent_segments;
  parent.segments_count = parent_segments_count;

  child_segment1.start = &child_vertex1;
  child_segment1.end = &child_vertex2;
  child_segments[0] = &child_segment1;
  child_segment2.start = &child_vertex2;
  child_segment2.end = &child_vertex3;
  child_segments[1] = &child_segment2;
  child_segment3.start = &child_vertex3;
  child_segment3.end = &child_vertex4;
  child_segments[2] = &child_segment3;
  child_segment4.start = &child_vertex4;
  child_segment4.end = &child_vertex1;
  child_segments[3] = &child_segment4;
  child.segments = child_segments;
  child.segments_count = child_segments_count;
  result = geo_geometry_in_geometry(&parent, &child, strict);
  assert(result == -1);
}

void geo_geometry_in_geometry_returns_negative_1_when_parent_geometry_ith_segment_end_point_is_null(void) {
  int result = 0;
  int strict = 1;
  struct geo_point parent_vertex1 = { 0.0F, 0.0F };
  struct geo_point parent_vertex2 = { 5.0F, 0.0F };
  struct geo_point parent_vertex3 = { 5.0F, 5.0F };
  struct geo_point parent_vertex4 = { 0.0F, 5.0F };
  struct geo_point child_vertex1 = { 1.0F, 1.0F };
  struct geo_point child_vertex2 = { 3.0F, 1.0F };
  struct geo_point child_vertex3 = { 3.0F, 3.0F };
  struct geo_point child_vertex4 = { 1.0F, 3.0F };
  struct geo_segment parent_segment1;
  struct geo_segment parent_segment2;
  struct geo_segment parent_segment3;
  struct geo_segment parent_segment4;
  struct geo_segment child_segment1;
  struct geo_segment child_segment2;
  struct geo_segment child_segment3;
  struct geo_segment child_segment4;
  struct geo_segment *parent_segments[4];
  struct geo_segment *child_segments[4];
  struct geo_geometry parent;
  struct geo_geometry child;
  int parent_segments_count = 4;
  int child_segments_count = 4;
  parent_segment1.start = &parent_vertex1;
  parent_segment1.end = &parent_vertex2;
  parent_segments[0] = &parent_segment1;
  parent_segment2.start = &parent_vertex2;
  parent_segment2.end = &parent_vertex3;
  parent_segments[1] = &parent_segment2;
  parent_segment3.start = &parent_vertex3;
  parent_segment3.end = &parent_vertex4;
  parent_segments[2] = &parent_segment3;
  parent_segment4.start = &parent_vertex4;
  parent_segment4.end = NULL;
  parent_segments[3] = &parent_segment4;
  parent.segments = parent_segments;
  parent.segments_count = parent_segments_count;

  child_segment1.start = &child_vertex1;
  child_segment1.end = &child_vertex2;
  child_segments[0] = &child_segment1;
  child_segment2.start = &child_vertex2;
  child_segment2.end = &child_vertex3;
  child_segments[1] = &child_segment2;
  child_segment3.start = &child_vertex1;
  child_segment3.end = &child_vertex3;
  child_segments[2] = &child_segment3;
  child_segment4.start = &child_vertex4;
  child_segment4.end = &child_vertex1;
  child_segments[3] = &child_segment4;
  child.segments = child_segments;
  child.segments_count = child_segments_count;
  result = geo_geometry_in_geometry(&parent, &child, strict);
  assert(result == -1);
}

void geo_geometry_in_geometry_returns_negative_1_when_child_geometry_is_null(void) {
  int result = 0;
  int strict = 1;
  struct geo_point parent_vertex1 = { 0.0F, 0.0F };
  struct geo_point parent_vertex2 = { 5.0F, 0.0F };
  struct geo_point parent_vertex3 = { 5.0F, 5.0F };
  struct geo_point parent_vertex4 = { 0.0F, 5.0F };
  struct geo_point child_vertex1 = { 1.0F, 1.0F };
  struct geo_point child_vertex2 = { 3.0F, 1.0F };
  struct geo_point child_vertex3 = { 3.0F, 3.0F };
  struct geo_point child_vertex4 = { 1.0F, 3.0F };
  struct geo_segment parent_segment1;
  struct geo_segment parent_segment2;
  struct geo_segment parent_segment3;
  struct geo_segment parent_segment4;
  struct geo_segment child_segment1;
  struct geo_segment child_segment2;
  struct geo_segment child_segment3;
  struct geo_segment child_segment4;
  struct geo_segment *parent_segments[4];
  struct geo_segment *child_segments[4];
  struct geo_geometry parent;
  struct geo_geometry child;
  int parent_segments_count = 4;
  int child_segments_count = 4;
  parent_segment1.start = &parent_vertex1;
  parent_segment1.end = &parent_vertex2;
  parent_segments[0] = &parent_segment1;
  parent_segment2.start = &parent_vertex2;
  parent_segment2.end = &parent_vertex3;
  parent_segments[1] = &parent_segment2;
  parent_segment3.start = &parent_vertex3;
  parent_segment3.end = &parent_vertex4;
  parent_segments[2] = &parent_segment3;
  parent_segment4.start = &parent_vertex4;
  parent_segment4.end = &parent_vertex1;
  parent_segments[3] = &parent_segment4;
  parent.segments = parent_segments;
  parent.segments_count = parent_segments_count;

  child_segment1.start = &child_vertex1;
  child_segment1.end = &child_vertex2;
  child_segments[0] = &child_segment1;
  child_segment2.start = &child_vertex2;
  child_segment2.end = &child_vertex3;
  child_segments[1] = &child_segment2;
  child_segment3.start = &child_vertex3;
  child_segment3.end = &child_vertex4;
  child_segments[2] = &child_segment3;
  child_segment4.start = &child_vertex4;
  child_segment4.end = &child_vertex1;
  child_segments[3] = &child_segment4;
  child.segments = child_segments;
  child.segments_count = child_segments_count;
  result = geo_geometry_in_geometry(&parent, NULL, strict);
  assert(result == -1);
}

void geo_geometry_in_geometry_returns_negative_1_when_child_geometry_segments_is_null(void) {
  int result = 0;
  int strict = 1;
  struct geo_point parent_vertex1 = { 0.0F, 0.0F };
  struct geo_point parent_vertex2 = { 5.0F, 0.0F };
  struct geo_point parent_vertex3 = { 5.0F, 5.0F };
  struct geo_point parent_vertex4 = { 0.0F, 5.0F };
  struct geo_point child_vertex1 = { 1.0F, 1.0F };
  struct geo_point child_vertex2 = { 3.0F, 1.0F };
  struct geo_point child_vertex3 = { 3.0F, 3.0F };
  struct geo_point child_vertex4 = { 1.0F, 3.0F };
  struct geo_segment parent_segment1;
  struct geo_segment parent_segment2;
  struct geo_segment parent_segment3;
  struct geo_segment parent_segment4;
  struct geo_segment child_segment1;
  struct geo_segment child_segment2;
  struct geo_segment child_segment3;
  struct geo_segment child_segment4;
  struct geo_segment *parent_segments[4];
  struct geo_segment *child_segments[4];
  struct geo_geometry parent;
  struct geo_geometry child;
  int parent_segments_count = 4;
  int child_segments_count = 4;
  parent_segment1.start = &parent_vertex1;
  parent_segment1.end = &parent_vertex2;
  parent_segments[0] = &parent_segment1;
  parent_segment2.start = &parent_vertex2;
  parent_segment2.end = &parent_vertex3;
  parent_segments[1] = &parent_segment2;
  parent_segment3.start = &parent_vertex3;
  parent_segment3.end = &parent_vertex4;
  parent_segments[2] = &parent_segment3;
  parent_segment4.start = &parent_vertex4;
  parent_segment4.end = &parent_vertex1;
  parent_segments[3] = &parent_segment4;
  parent.segments = parent_segments;
  parent.segments_count = parent_segments_count;

  child_segment1.start = &child_vertex1;
  child_segment1.end = &child_vertex2;
  child_segments[0] = &child_segment1;
  child_segment2.start = &child_vertex2;
  child_segment2.end = &child_vertex3;
  child_segments[1] = &child_segment2;
  child_segment3.start = &child_vertex3;
  child_segment3.end = &child_vertex4;
  child_segments[2] = &child_segment3;
  child_segment4.start = &child_vertex4;
  child_segment4.end = &child_vertex1;
  child_segments[3] = &child_segment4;
  child.segments = NULL;
  child.segments_count = child_segments_count;
  result = geo_geometry_in_geometry(&parent, &child, strict);
  assert(result == -1);
}

void geo_geometry_in_geometry_returns_negative_1_when_child_geometry_ith_segment_is_null(void) {
  int result = 0;
  int strict = 1;
  struct geo_point parent_vertex1 = { 0.0F, 0.0F };
  struct geo_point parent_vertex2 = { 5.0F, 0.0F };
  struct geo_point parent_vertex3 = { 5.0F, 5.0F };
  struct geo_point parent_vertex4 = { 0.0F, 5.0F };
  struct geo_point child_vertex1 = { 1.0F, 1.0F };
  struct geo_point child_vertex2 = { 3.0F, 1.0F };
  struct geo_point child_vertex3 = { 3.0F, 3.0F };
  struct geo_point child_vertex4 = { 1.0F, 3.0F };
  struct geo_segment parent_segment1;
  struct geo_segment parent_segment2;
  struct geo_segment parent_segment3;
  struct geo_segment parent_segment4;
  struct geo_segment child_segment1;
  struct geo_segment child_segment2;
  struct geo_segment child_segment3;
  struct geo_segment child_segment4;
  struct geo_segment *parent_segments[4];
  struct geo_segment *child_segments[4];
  struct geo_geometry parent;
  struct geo_geometry child;
  int parent_segments_count = 4;
  int child_segments_count = 4;
  parent_segment1.start = &parent_vertex1;
  parent_segment1.end = &parent_vertex2;
  parent_segments[0] = &parent_segment1;
  parent_segment2.start = &parent_vertex2;
  parent_segment2.end = &parent_vertex3;
  parent_segments[1] = &parent_segment2;
  parent_segment3.start = &parent_vertex3;
  parent_segment3.end = &parent_vertex4;
  parent_segments[2] = &parent_segment3;
  parent_segment4.start = &parent_vertex4;
  parent_segment4.end = &parent_vertex1;
  parent_segments[3] = &parent_segment4;
  parent.segments = parent_segments;
  parent.segments_count = parent_segments_count;

  child_segment1.start = &child_vertex1;
  child_segment1.end = &child_vertex2;
  child_segments[0] = &child_segment1;
  child_segment2.start = &child_vertex2;
  child_segment2.end = &child_vertex3;
  child_segments[1] = &child_segment2;
  child_segment3.start = &child_vertex3;
  child_segment3.end = &child_vertex4;
  child_segments[2] = NULL;
  child_segment4.start = &child_vertex4;
  child_segment4.end = &child_vertex1;
  child_segments[3] = &child_segment4;
  child.segments = child_segments;
  child.segments_count = child_segments_count;
  result = geo_geometry_in_geometry(&parent, &child, strict);
  assert(result == -1);
}

void geo_geometry_in_geometry_returns_negative_1_when_child_geometry_ith_segment_start_point_is_null(void) {
  int result = 0;
  int strict = 1;
  struct geo_point parent_vertex1 = { 0.0F, 0.0F };
  struct geo_point parent_vertex2 = { 5.0F, 0.0F };
  struct geo_point parent_vertex3 = { 5.0F, 5.0F };
  struct geo_point parent_vertex4 = { 0.0F, 5.0F };
  struct geo_point child_vertex1 = { 1.0F, 1.0F };
  struct geo_point child_vertex2 = { 3.0F, 1.0F };
  struct geo_point child_vertex3 = { 3.0F, 3.0F };
  struct geo_point child_vertex4 = { 1.0F, 3.0F };
  struct geo_segment parent_segment1;
  struct geo_segment parent_segment2;
  struct geo_segment parent_segment3;
  struct geo_segment parent_segment4;
  struct geo_segment child_segment1;
  struct geo_segment child_segment2;
  struct geo_segment child_segment3;
  struct geo_segment child_segment4;
  struct geo_segment *parent_segments[4];
  struct geo_segment *child_segments[4];
  struct geo_geometry parent;
  struct geo_geometry child;
  int parent_segments_count = 4;
  int child_segments_count = 4;
  parent_segment1.start = &parent_vertex1;
  parent_segment1.end = &parent_vertex2;
  parent_segments[0] = &parent_segment1;
  parent_segment2.start = &parent_vertex2;
  parent_segment2.end = &parent_vertex3;
  parent_segments[1] = &parent_segment2;
  parent_segment3.start = &parent_vertex3;
  parent_segment3.end = &parent_vertex4;
  parent_segments[2] = &parent_segment3;
  parent_segment4.start = &parent_vertex4;
  parent_segment4.end = &parent_vertex1;
  parent_segments[3] = &parent_segment4;
  parent.segments = parent_segments;
  parent.segments_count = parent_segments_count;

  child_segment1.start = &child_vertex1;
  child_segment1.end = &child_vertex2;
  child_segments[0] = &child_segment1;
  child_segment2.start = NULL;
  child_segment2.end = &child_vertex3;
  child_segments[1] = &child_segment2;
  child_segment3.start = &child_vertex3;
  child_segment3.end = &child_vertex4;
  child_segments[2] = &child_segment3;
  child_segment4.start = &child_vertex4;
  child_segment4.end = &child_vertex1;
  child_segments[3] = &child_segment4;
  child.segments = child_segments;
  child.segments_count = child_segments_count;
  result = geo_geometry_in_geometry(&parent, &child, strict);
  assert(result == -1);
}

void geo_geometry_in_geometry_returns_negative_1_when_child_geometry_ith_segment_end_point_is_null(void) {
  int result = 0;
  int strict = 1;
  struct geo_point parent_vertex1 = { 0.0F, 0.0F };
  struct geo_point parent_vertex2 = { 5.0F, 0.0F };
  struct geo_point parent_vertex3 = { 5.0F, 5.0F };
  struct geo_point parent_vertex4 = { 0.0F, 5.0F };
  struct geo_point child_vertex1 = { 1.0F, 1.0F };
  struct geo_point child_vertex2 = { 3.0F, 1.0F };
  struct geo_point child_vertex3 = { 3.0F, 3.0F };
  struct geo_point child_vertex4 = { 1.0F, 3.0F };
  struct geo_segment parent_segment1;
  struct geo_segment parent_segment2;
  struct geo_segment parent_segment3;
  struct geo_segment parent_segment4;
  struct geo_segment child_segment1;
  struct geo_segment child_segment2;
  struct geo_segment child_segment3;
  struct geo_segment child_segment4;
  struct geo_segment *parent_segments[4];
  struct geo_segment *child_segments[4];
  struct geo_geometry parent;
  struct geo_geometry child;
  int parent_segments_count = 4;
  int child_segments_count = 4;
  parent_segment1.start = &parent_vertex1;
  parent_segment1.end = &parent_vertex2;
  parent_segments[0] = &parent_segment1;
  parent_segment2.start = &parent_vertex2;
  parent_segment2.end = &parent_vertex3;
  parent_segments[1] = &parent_segment2;
  parent_segment3.start = &parent_vertex3;
  parent_segment3.end = &parent_vertex4;
  parent_segments[2] = &parent_segment3;
  parent_segment4.start = &parent_vertex4;
  parent_segment4.end = NULL;
  parent_segments[3] = &parent_segment4;
  parent.segments = parent_segments;
  parent.segments_count = parent_segments_count;

  child_segment1.start = &child_vertex1;
  child_segment1.end = &child_vertex2;
  child_segments[0] = &child_segment1;
  child_segment2.start = &child_vertex2;
  child_segment2.end = &child_vertex3;
  child_segments[1] = &child_segment2;
  child_segment3.start = &child_vertex3;
  child_segment3.end = &child_vertex4;
  child_segments[2] = &child_segment3;
  child_segment4.start = &child_vertex4;
  child_segment4.end = &child_vertex1;
  child_segments[3] = &child_segment4;
  child.segments = child_segments;
  child.segments_count = child_segments_count;
  result = geo_geometry_in_geometry(&parent, &child, strict);
  assert(result == -1);
}

void geo_geometry_in_geometry_returns_0_when_parent_geometry_segments_count_less_than_3(void) {
  int result = 0;
  int strict = 1;
  struct geo_point parent_vertex1 = { 0.0F, 0.0F };
  struct geo_point parent_vertex2 = { 5.0F, 0.0F };
  struct geo_point parent_vertex3 = { 5.0F, 5.0F };
  struct geo_point parent_vertex4 = { 0.0F, 5.0F };
  struct geo_point child_vertex1 = { 1.0F, 1.0F };
  struct geo_point child_vertex2 = { 3.0F, 1.0F };
  struct geo_point child_vertex3 = { 3.0F, 3.0F };
  struct geo_point child_vertex4 = { 1.0F, 3.0F };
  struct geo_segment parent_segment1;
  struct geo_segment parent_segment2;
  struct geo_segment parent_segment3;
  struct geo_segment parent_segment4;
  struct geo_segment child_segment1;
  struct geo_segment child_segment2;
  struct geo_segment child_segment3;
  struct geo_segment child_segment4;
  struct geo_segment *parent_segments[4];
  struct geo_segment *child_segments[4];
  struct geo_geometry parent;
  struct geo_geometry child;
  int parent_segments_count = 2;
  int child_segments_count = 4;
  parent_segment1.start = &parent_vertex1;
  parent_segment1.end = &parent_vertex2;
  parent_segments[0] = &parent_segment1;
  parent_segment2.start = &parent_vertex2;
  parent_segment2.end = &parent_vertex3;
  parent_segments[1] = &parent_segment2;
  parent.segments = parent_segments;
  parent.segments_count = parent_segments_count;

  child_segment1.start = &child_vertex1;
  child_segment1.end = &child_vertex2;
  child_segments[0] = &child_segment1;
  child_segment2.start = &child_vertex2;
  child_segment2.end = &child_vertex3;
  child_segments[1] = &child_segment2;
  child_segment3.start = &child_vertex3;
  child_segment3.end = &child_vertex4;
  child_segments[2] = &child_segment3;
  child_segment4.start = &child_vertex4;
  child_segment4.end = &child_vertex1;
  child_segments[3] = &child_segment4;
  child.segments = child_segments;
  child.segments_count = child_segments_count;
  result = geo_geometry_in_geometry(&parent, &child, strict);
  assert(result == 0);
}

void geo_geometry_in_geometry_returns_0_when_child_geometry_segments_count_less_than_3(void) {
  int result = 0;
  int strict = 1;
  struct geo_point parent_vertex1 = { 0.0F, 0.0F };
  struct geo_point parent_vertex2 = { 5.0F, 0.0F };
  struct geo_point parent_vertex3 = { 5.0F, 5.0F };
  struct geo_point parent_vertex4 = { 0.0F, 5.0F };
  struct geo_point child_vertex1 = { 1.0F, 1.0F };
  struct geo_point child_vertex2 = { 3.0F, 1.0F };
  struct geo_point child_vertex3 = { 3.0F, 3.0F };
  struct geo_point child_vertex4 = { 1.0F, 3.0F };
  struct geo_segment parent_segment1;
  struct geo_segment parent_segment2;
  struct geo_segment parent_segment3;
  struct geo_segment parent_segment4;
  struct geo_segment child_segment1;
  struct geo_segment child_segment2;
  struct geo_segment child_segment3;
  struct geo_segment child_segment4;
  struct geo_segment *parent_segments[4];
  struct geo_segment *child_segments[4];
  struct geo_geometry parent;
  struct geo_geometry child;
  int parent_segments_count = 4;
  int child_segments_count = 2;
  parent_segment1.start = &parent_vertex1;
  parent_segment1.end = &parent_vertex2;
  parent_segments[0] = &parent_segment1;
  parent_segment2.start = &parent_vertex2;
  parent_segment2.end = &parent_vertex3;
  parent_segments[1] = &parent_segment2;
  parent_segment3.start = &parent_vertex3;
  parent_segment3.end = &parent_vertex4;
  parent_segments[2] = &parent_segment3;
  parent_segment4.start = &parent_vertex4;
  parent_segment4.end = &parent_vertex1;
  parent_segments[3] = &parent_segment4;
  parent.segments = parent_segments;
  parent.segments_count = parent_segments_count;

  child_segment1.start = &child_vertex1;
  child_segment1.end = &child_vertex2;
  child_segments[0] = &child_segment1;
  child_segment2.start = &child_vertex2;
  child_segment2.end = &child_vertex3;
  child_segments[1] = &child_segment2;
  child.segments = child_segments;
  child.segments_count = child_segments_count;
  result = geo_geometry_in_geometry(&parent, &child, strict);
  assert(result == 0);
}

void geo_geometry_in_geometry_returns_1_when_all_points_in_child_geometry_are_inside_parent_geometry(void) {
  int result = 0;
  int strict = 1;
  struct geo_point parent_vertex1 = { 0.0F, 0.0F };
  struct geo_point parent_vertex2 = { 5.0F, 0.0F };
  struct geo_point parent_vertex3 = { 5.0F, 5.0F };
  struct geo_point parent_vertex4 = { 0.0F, 5.0F };
  struct geo_point child_vertex1 = { 1.0F, 1.0F };
  struct geo_point child_vertex2 = { 3.0F, 1.0F };
  struct geo_point child_vertex3 = { 3.0F, 3.0F };
  struct geo_point child_vertex4 = { 1.0F, 3.0F };
  struct geo_segment parent_segment1;
  struct geo_segment parent_segment2;
  struct geo_segment parent_segment3;
  struct geo_segment parent_segment4;
  struct geo_segment child_segment1;
  struct geo_segment child_segment2;
  struct geo_segment child_segment3;
  struct geo_segment child_segment4;
  struct geo_segment *parent_segments[4];
  struct geo_segment *child_segments[4];
  struct geo_geometry parent;
  struct geo_geometry child;
  int parent_segments_count = 4;
  int child_segments_count = 4;
  parent_segment1.start = &parent_vertex1;
  parent_segment1.end = &parent_vertex2;
  parent_segments[0] = &parent_segment1;
  parent_segment2.start = &parent_vertex2;
  parent_segment2.end = &parent_vertex3;
  parent_segments[1] = &parent_segment2;
  parent_segment3.start = &parent_vertex3;
  parent_segment3.end = &parent_vertex4;
  parent_segments[2] = &parent_segment3;
  parent_segment4.start = &parent_vertex4;
  parent_segment4.end = &parent_vertex1;
  parent_segments[3] = &parent_segment4;
  parent.segments = parent_segments;
  parent.segments_count = parent_segments_count;

  child_segment1.start = &child_vertex1;
  child_segment1.end = &child_vertex2;
  child_segments[0] = &child_segment1;
  child_segment2.start = &child_vertex2;
  child_segment2.end = &child_vertex3;
  child_segments[1] = &child_segment2;
  child_segment3.start = &child_vertex3;
  child_segment3.end = &child_vertex4;
  child_segments[2] = &child_segment3;
  child_segment4.start = &child_vertex4;
  child_segment4.end = &child_vertex1;
  child_segments[3] = &child_segment4;
  child.segments = child_segments;
  child.segments_count = child_segments_count;
  result = geo_geometry_in_geometry(&parent, &child, strict);
  assert(result == 1);
}

void geo_geometry_in_geometry_returns_0_when_any_points_in_child_geometry_are_outside_parent_geometry(void) {
  int result = 0;
  int strict = 1;
  struct geo_point parent_vertex1 = { 0.0F, 0.0F };
  struct geo_point parent_vertex2 = { 5.0F, 0.0F };
  struct geo_point parent_vertex3 = { 5.0F, 5.0F };
  struct geo_point parent_vertex4 = { 0.0F, 5.0F };
  struct geo_point child_vertex1 = { 1.0F, 1.0F };
  struct geo_point child_vertex2 = { 3.0F, 1.0F };
  struct geo_point child_vertex3 = { 6.0F, 3.0F }; /* outside parent */
  struct geo_point child_vertex4 = { 1.0F, 3.0F };
  struct geo_segment parent_segment1;
  struct geo_segment parent_segment2;
  struct geo_segment parent_segment3;
  struct geo_segment parent_segment4;
  struct geo_segment child_segment1;
  struct geo_segment child_segment2;
  struct geo_segment child_segment3;
  struct geo_segment child_segment4;
  struct geo_segment *parent_segments[4];
  struct geo_segment *child_segments[4];
  struct geo_geometry parent;
  struct geo_geometry child;
  int parent_segments_count = 4;
  int child_segments_count = 4;
  parent_segment1.start = &parent_vertex1;
  parent_segment1.end = &parent_vertex2;
  parent_segments[0] = &parent_segment1;
  parent_segment2.start = &parent_vertex2;
  parent_segment2.end = &parent_vertex3;
  parent_segments[1] = &parent_segment2;
  parent_segment3.start = &parent_vertex3;
  parent_segment3.end = &parent_vertex4;
  parent_segments[2] = &parent_segment3;
  parent_segment4.start = &parent_vertex4;
  parent_segment4.end = &parent_vertex1;
  parent_segments[3] = &parent_segment4;
  parent.segments = parent_segments;
  parent.segments_count = parent_segments_count;

  child_segment1.start = &child_vertex1;
  child_segment1.end = &child_vertex2;
  child_segments[0] = &child_segment1;
  child_segment2.start = &child_vertex2;
  child_segment2.end = &child_vertex3;
  child_segments[1] = &child_segment2;
  child_segment3.start = &child_vertex3;
  child_segment3.end = &child_vertex4;
  child_segments[2] = &child_segment3;
  child_segment4.start = &child_vertex4;
  child_segment4.end = &child_vertex1;
  child_segments[3] = &child_segment4;
  child.segments = child_segments;
  child.segments_count = child_segments_count;
  result = geo_geometry_in_geometry(&parent, &child, strict);
  assert(result == 0);
}

void geo_geometry_in_geometry_returns_0_when_any_points_in_child_geometry_are_on_segment_of_parent_geometry_and_strict_is_1(void) {
  int result = 0;
  int strict = 1;
  struct geo_point parent_vertex1 = { 0.0F, 0.0F };
  struct geo_point parent_vertex2 = { 5.0F, 0.0F };
  struct geo_point parent_vertex3 = { 5.0F, 5.0F };
  struct geo_point parent_vertex4 = { 0.0F, 5.0F };
  struct geo_point child_vertex1 = { 1.0F, 1.0F };
  struct geo_point child_vertex2 = { 3.0F, 1.0F };
  struct geo_point child_vertex3 = { 5.0F, 3.0F }; /* on parent geometry segment */
  struct geo_point child_vertex4 = { 1.0F, 3.0F };
  struct geo_segment parent_segment1;
  struct geo_segment parent_segment2;
  struct geo_segment parent_segment3;
  struct geo_segment parent_segment4;
  struct geo_segment child_segment1;
  struct geo_segment child_segment2;
  struct geo_segment child_segment3;
  struct geo_segment child_segment4;
  struct geo_segment *parent_segments[4];
  struct geo_segment *child_segments[4];
  struct geo_geometry parent;
  struct geo_geometry child;
  int parent_segments_count = 4;
  int child_segments_count = 4;
  parent_segment1.start = &parent_vertex1;
  parent_segment1.end = &parent_vertex2;
  parent_segments[0] = &parent_segment1;
  parent_segment2.start = &parent_vertex2;
  parent_segment2.end = &parent_vertex3;
  parent_segments[1] = &parent_segment2;
  parent_segment3.start = &parent_vertex3;
  parent_segment3.end = &parent_vertex4;
  parent_segments[2] = &parent_segment3;
  parent_segment4.start = &parent_vertex4;
  parent_segment4.end = &parent_vertex1;
  parent_segments[3] = &parent_segment4;
  parent.segments = parent_segments;
  parent.segments_count = parent_segments_count;

  child_segment1.start = &child_vertex1;
  child_segment1.end = &child_vertex2;
  child_segments[0] = &child_segment1;
  child_segment2.start = &child_vertex2;
  child_segment2.end = &child_vertex3;
  child_segments[1] = &child_segment2;
  child_segment3.start = &child_vertex3;
  child_segment3.end = &child_vertex4;
  child_segments[2] = &child_segment3;
  child_segment4.start = &child_vertex4;
  child_segment4.end = &child_vertex1;
  child_segments[3] = &child_segment4;
  child.segments = child_segments;
  child.segments_count = child_segments_count;
  result = geo_geometry_in_geometry(&parent, &child, strict);
  assert(result == 0);
}

void geo_geometry_in_geometry_returns_1_when_any_points_in_child_geometry_are_on_segment_of_parent_geometry_and_strict_is_0(void) {
  int result = 0;
  int strict = 0;
  struct geo_point parent_vertex1 = { 0.0F, 0.0F };
  struct geo_point parent_vertex2 = { 5.0F, 0.0F };
  struct geo_point parent_vertex3 = { 5.0F, 5.0F };
  struct geo_point parent_vertex4 = { 0.0F, 5.0F };
  struct geo_point child_vertex1 = { 1.0F, 1.0F };
  struct geo_point child_vertex2 = { 3.0F, 1.0F };
  struct geo_point child_vertex3 = { 5.0F, 3.0F }; /* on parent geometry segment */
  struct geo_point child_vertex4 = { 1.0F, 3.0F };
  struct geo_segment parent_segment1;
  struct geo_segment parent_segment2;
  struct geo_segment parent_segment3;
  struct geo_segment parent_segment4;
  struct geo_segment child_segment1;
  struct geo_segment child_segment2;
  struct geo_segment child_segment3;
  struct geo_segment child_segment4;
  struct geo_segment *parent_segments[4];
  struct geo_segment *child_segments[4];
  struct geo_geometry parent;
  struct geo_geometry child;
  int parent_segments_count = 4;
  int child_segments_count = 4;
  parent_segment1.start = &parent_vertex1;
  parent_segment1.end = &parent_vertex2;
  parent_segments[0] = &parent_segment1;
  parent_segment2.start = &parent_vertex2;
  parent_segment2.end = &parent_vertex3;
  parent_segments[1] = &parent_segment2;
  parent_segment3.start = &parent_vertex3;
  parent_segment3.end = &parent_vertex4;
  parent_segments[2] = &parent_segment3;
  parent_segment4.start = &parent_vertex4;
  parent_segment4.end = &parent_vertex1;
  parent_segments[3] = &parent_segment4;
  parent.segments = parent_segments;
  parent.segments_count = parent_segments_count;

  child_segment1.start = &child_vertex1;
  child_segment1.end = &child_vertex2;
  child_segments[0] = &child_segment1;
  child_segment2.start = &child_vertex2;
  child_segment2.end = &child_vertex3;
  child_segments[1] = &child_segment2;
  child_segment3.start = &child_vertex3;
  child_segment3.end = &child_vertex4;
  child_segments[2] = &child_segment3;
  child_segment4.start = &child_vertex4;
  child_segment4.end = &child_vertex1;
  child_segments[3] = &child_segment4;
  child.segments = child_segments;
  child.segments_count = child_segments_count;
  result = geo_geometry_in_geometry(&parent, &child, strict);
  assert(result == 1);
}

/*----------------------------------
 * geo_convex_hull tests
*----------------------------------
 */
void geo_convex_hull_returns_negative_1_when_points_array_is_null(void) {
  int count = 5;
  struct geo_point *hull[5];
  int result = geo_convex_hull(NULL, hull, count);
  assert(result == -1);
}

void geo_convex_hull_returns_negative_1_when_hull_array_is_null(void) {
  int count = 3;
  struct geo_point *points[3];
  struct geo_point point1 = { 0.0F, 0.0F };
  struct geo_point point2 = { 1.0F, 0.0F };
  struct geo_point point3 = { 0.5F, 0.5F };
  int result = 0;
  points[0] = &point1;
  points[1] = &point2;
  points[2] = &point3;

  result = geo_convex_hull(points, NULL, count);
  assert(result == -1);
}

void geo_convex_hull_returns_negative_1_when_size_is_less_than_3(void) {
  int count = 2;
  struct geo_point *hull[2];
  struct geo_point *points[2];
  struct geo_point point1 = { 0.0F, 0.0F };
  struct geo_point point2 = { 1.0F, 0.0F };
  int result = 0;
  points[0] = &point1;
  points[1] = &point2;

  result = geo_convex_hull(points, hull, count);
  assert(result == -1);
}

void geo_convex_hull_returns_negative_1_when_any_point_in_points_is_null(void) {
  int count = 3;
  struct geo_point *hull[3];
  struct geo_point *points[3];
  struct geo_point point1 = { 0.0F, 0.0F };
  struct geo_point point3 = { 0.5F, 0.5F };
  int result = 0;
  points[0] = &point1;
  points[1] = NULL;
  points[2] = &point3;

  result = geo_convex_hull(points, hull, count);
  assert(result == -1);
}

void geo_convex_hull_returns_3_and_hull_has_points_in_order_when_given_points_for_triangle(void) {
  int count = 3;
  struct geo_point *hull[3];
  struct geo_point *points[3];
  struct geo_point point1 = { 0.0F, 0.0F };
  struct geo_point point2 = { 1.0F, 0.0F };
  struct geo_point point3 = { 0.5F, 0.5F };
  int result = 0;
  points[0] = &point1;
  points[1] = &point3;
  points[2] = &point2;

  result = geo_convex_hull(points, hull, count);
  assert(result == 3);
  assert(hull[0] == &point1);
  assert(hull[1] == &point2);
  assert(hull[2] == &point3);
}

void geo_convex_hull_returns_5_and_hull_has_points_in_ccw_order_when_given_point_cloud(void) {
  int count = 7;
  struct geo_point *hull[7];
  struct geo_point *points[7];
  struct geo_point point1 = { 1.0F, 1.0F };
  struct geo_point point2 = { 7.0F, 0.0F };
  struct geo_point point3 = { 4.0F, 2.0F };
  struct geo_point point4 = { 6.0F, 4.0F };
  struct geo_point point5 = { 3.0F, 5.0F };
  struct geo_point point6 = { 5.0F, 6.0F };
  struct geo_point point7 = { 2.0F, 7.0F };
  int result = 0;

  points[0] = &point1;
  points[1] = &point2;
  points[2] = &point3;
  points[3] = &point4;
  points[4] = &point5;
  points[5] = &point6;
  points[6] = &point7;
  result = geo_convex_hull(points, hull, count);
  assert(result == 5);
  assert(hull[0] == &point2);
  assert(hull[1] == &point4);
  assert(hull[2] == &point6);
  assert(hull[3] == &point7);
  assert(hull[4] == &point1);
}

void geo_convex_hull_returns_4_and_hull_has_points_in_ccw_order_using_furthest_colinear_point_when_given_point_cloud_with_colinear_points(void) {
  int count = 6;
  struct geo_point *hull[6];
  struct geo_point *points[6];
  struct geo_point point1 = { 0.0F, 0.0F };
  struct geo_point point2 = { 3.0F, 0.0F };
  struct geo_point point3 = { 3.0F, 1.0F };
  struct geo_point point4 = { 3.0F, 2.0F };
  struct geo_point point5 = { 3.0F, 3.0F };
  struct geo_point point6 = { 0.0F, 3.0F };
  int result = 0;
  points[0] = &point1;
  points[1] = &point6;
  points[2] = &point3;
  points[3] = &point2;
  points[4] = &point5;
  points[5] = &point4;
  result = geo_convex_hull(points, hull, count);
  assert(result == 4);
  assert(hull[0] == &point1);
  assert(hull[1] == &point2);
  assert(hull[2] == &point5);
  assert(hull[3] == &point6);
}

void convex_hull_with_30_points_returns_12_in_ccw_order(void) {
  int count = 30;
  struct geo_point *hull[30];
  struct geo_point *points[30];
  struct geo_point point1 = { -100.0f, 100.0f };
  struct geo_point point2 = { -125.0f, 125.0f };
  struct geo_point point3 = { -150.0f, 125.0f };
  struct geo_point point4 = { -175.0f, 100.0f };
  struct geo_point point5 = { -200.0f, 50.0f };
  struct geo_point point6 = { -200.0f, -50.0f };
  struct geo_point point7 = { -175.0f, -100.0f };
  struct geo_point point8 = { -150.0f, -125.0f };
  struct geo_point point9 = { -125.0f, -125.0f };
  struct geo_point point10 = { -100.0f, -100.0f };
  struct geo_point point11 = { 75.0f, 150.0f };
  struct geo_point point12 = { 25.0f, 200.0f };
  struct geo_point point13 = { -25.0f, 200.0f };
  struct geo_point point14 = { -75.0f, 125.0f };
  struct geo_point point15 = { -25.0f, 50.0f };
  struct geo_point point16 = { 25.0f, -50.0f };
  struct geo_point point17 = { 75.0f, -125.0f };
  struct geo_point point18 = { 25.0f, -200.0f };
  struct geo_point point19 = { -25.0f, -200.0f };
  struct geo_point point20 = { -75.0f, -150.0f };
  struct geo_point point21 = { 200.0f, 125.0f };
  struct geo_point point22 = { 150.0f, 125.0f };
  struct geo_point point23 = { 100.0f, 125.0f };
  struct geo_point point24 = { 100.0f, 50.0f };
  struct geo_point point25 = { 100.0f, 0.0f };
  struct geo_point point26 = { 150.0f, 0.0f };
  struct geo_point point27 = { 100.0f, -50.0f };
  struct geo_point point28 = { 100.0f, -125.0f };
  struct geo_point point29 = { 150.0f, -125.0f };
  struct geo_point point30 = { 200.0f, -125.0f };
  int result = 0;
  points[0] = &point1;
  points[1] = &point2;
  points[2] = &point3;
  points[3] = &point4;
  points[4] = &point5;
  points[5] = &point6;
  points[6] = &point7;
  points[7] = &point8;
  points[8] = &point9;
  points[9] = &point10;
  points[10] = &point11;
  points[11] = &point12;
  points[12] = &point13;
  points[13] = &point14;
  points[14] = &point15;
  points[15] = &point16;
  points[16] = &point17;
  points[17] = &point18;
  points[18] = &point19;
  points[19] = &point20;
  points[20] = &point21;
  points[21] = &point22;
  points[22] = &point23;
  points[23] = &point24;
  points[24] = &point25;
  points[25] = &point26;
  points[26] = &point27;
  points[27] = &point28;
  points[28] = &point29;
  points[29] = &point30;
  result = geo_convex_hull(points, hull, count);
  assert(result == 12);
}

int main(void) {
  /* geo_points_equal tests */
  geo_points_equal_returns_geo_err_null_pointer_result_code_when_lhs_is_null();
  geo_points_equal_returns_geo_err_null_pointer_result_code_when_rhs_is_null();
  geo_points_equal_returns_geo_success_and_is_equal_set_to_1_when_lhs_and_rhs_are_exactly_equal();
  geo_points_equal_returns_geo_success_and_is_equal_set_to_1_when_lhs_x_and_y_and_rhs_x_and_y_are_within_epsilon();
  geo_points_equal_returns_geo_success_and_is_equal_set_to_0_when_lhs_only_x_and_rhs_only_x_are_within_epsilon();
  geo_points_equal_returns_geo_success_and_is_equal_set_to_0_when_lhs_neither_x_or_y_and_rhs_x_or_y_are_within_epsilon();

  /* geo_segments_intersect tests */
  geo_segments_intersect_returns_geo_err_null_pointer_result_code_when_segment_1_is_null();
  geo_segments_intersect_returns_geo_err_null_pointer_result_code_when_segment_2_is_null();
  geo_segments_intersect_returns_geo_err_null_pointer_result_code_when_segment_1_start_is_null();
  geo_segments_intersect_returns_geo_err_null_pointer_result_code_when_segment_1_end_is_null();
  geo_segments_intersect_returns_geo_err_null_pointer_result_code_when_segment_2_start_is_null();
  geo_segments_intersect_returns_geo_err_null_pointer_result_code_when_segment_2_end_is_null();
  geo_segments_intersect_returns_geo_success_and_intersect_count_is_0_when_segments_are_parallel();
  geo_segments_intersect_returns_geo_success_and_intersect_count_is_0_when_segments_are_colinear_but_dont_intersect();
  geo_segments_intersect_returns_geo_success_and_intersect_count_is_0_when_segments_dont_intersect();
  geo_segments_intersect_returns_geo_success_and_intersect_count_is_1_when_segments_properly_intersect();
  geo_segments_intersect_returns_geo_success_and_intersect_count_is_2_when_segment_1_end_is_equal_to_segment_2_start();
  geo_segments_intersect_returns_geo_success_and_intersect_count_is_2_when_one_segment_is_section_of_other_segment();
  geo_segments_intersect_returns_geo_success_and_intersect_count_is_4_when_segment_1_is_the_same_segment_as_segment_2();

  /* geo_geometry_is_closed tests */
  geo_geometry_is_closed_returns_geo_err_null_pointer_when_geometry_is_null();
  geo_geometry_is_closed_returns_geo_err_null_pointer_when_geometry_segments_is_null();
  geo_geometry_is_closed_returns_geo_err_null_pointer_when_geometry_segment_start_is_null();
  geo_geometry_is_closed_returns_geo_err_null_pointer_when_geometry_segment_end_is_null();
  geo_geometry_is_closed_returns_geo_err_too_small_when_geometry_segment_count_less_than_3();
  geo_geometry_is_closed_returns_geo_success_and_is_closed_is_false_when_nth_segments_end_doesnt_equal_n_plus_1_segment_start();
  geo_geometry_is_closed_returns_geo_success_and_is_closed_is_true_when_nth_segments_end_equals_n_plus_1_segments_start();

  /* geo_geometry_is_simple tests */
  geo_geometry_is_simple_returns_geo_err_null_pointer_when_geometry_is_null();
  geo_geometry_is_simple_returns_geo_err_null_pointer_when_geometry_segments_is_null();
  geo_geometry_is_simple_returns_geo_err_null_pointer_when_geometry_segments_ith_start_is_null();
  geo_geometry_is_simple_returns_geo_err_null_pointer_when_geometry_segments_ith_end_is_null();
  geo_geometry_is_simple_returns_geo_err_too_small_when_geometry_segments_count_less_than_3();
  geo_geometry_is_simple_returns_geo_success_and_is_simple_is_false_when_any_segments_intersect();
  geo_geometry_is_simple_returns_geo_success_and_is_simple_is_true_when_no_segments_intersect();

  /* geo_point_in_geometry tests */
  geo_point_in_geometry_returns_negative_1_when_point_is_null();
  geo_point_in_geometry_returns_negative_1_when_geometry_is_null();
  geo_point_in_geometry_returns_negative_1_when_geometry_segments_is_null();
  geo_point_in_geometry_returns_negative_1_when_geometry_segments_ith_start_is_null();
  geo_point_in_geometry_returns_negative_1_when_geometry_segments_ith_end_is_null();
  geo_point_in_geometry_returns_0_when_geometry_segments_count_is_less_than_3();
  geo_point_in_geometry_returns_0_when_point_on_geometry_segment_and_strict_is_1();
  geo_point_in_geometry_returns_1_when_point_on_geometry_segment_and_strict_is_0();
  geo_point_in_geometry_returns_0_when_point_is_to_the_left_of_the_geometry_and_colinear_with_horizontal_segment();
  geo_point_in_geometry_returns_0_when_point_is_to_the_right_of_the_geometry_and_colinear_with_horizontal_segment();
  geo_point_in_geometry_returns_0_when_point_is_above_of_the_geometry_and_colinear_with_vertical_segment();
  geo_point_in_geometry_returns_0_when_point_is_below_of_the_geometry_and_colinear_with_vertical_segment();


  /* geo_geometry_in_geometry tests */
  geo_geometry_in_geometry_returns_negative_1_when_parent_geometry_is_null();
  geo_geometry_in_geometry_returns_negative_1_when_parent_geometry_segments_is_null();
  geo_geometry_in_geometry_returns_negative_1_when_parent_geometry_ith_segment_is_null();
  geo_geometry_in_geometry_returns_negative_1_when_parent_geometry_ith_segment_start_point_is_null();
  geo_geometry_in_geometry_returns_negative_1_when_parent_geometry_ith_segment_end_point_is_null();
  geo_geometry_in_geometry_returns_negative_1_when_child_geometry_is_null();
  geo_geometry_in_geometry_returns_negative_1_when_child_geometry_segments_is_null();
  geo_geometry_in_geometry_returns_negative_1_when_child_geometry_ith_segment_is_null();
  geo_geometry_in_geometry_returns_negative_1_when_child_geometry_ith_segment_start_point_is_null();
  geo_geometry_in_geometry_returns_negative_1_when_child_geometry_ith_segment_end_point_is_null();
  geo_geometry_in_geometry_returns_0_when_parent_geometry_segments_count_less_than_3();
  geo_geometry_in_geometry_returns_0_when_child_geometry_segments_count_less_than_3();
  geo_geometry_in_geometry_returns_1_when_all_points_in_child_geometry_are_inside_parent_geometry();
  geo_geometry_in_geometry_returns_0_when_any_points_in_child_geometry_are_outside_parent_geometry();
  geo_geometry_in_geometry_returns_0_when_any_points_in_child_geometry_are_on_segment_of_parent_geometry_and_strict_is_1();
  geo_geometry_in_geometry_returns_1_when_any_points_in_child_geometry_are_on_segment_of_parent_geometry_and_strict_is_0();

  /* geo_convex_hull tests */
  geo_convex_hull_returns_negative_1_when_points_array_is_null();
  geo_convex_hull_returns_negative_1_when_hull_array_is_null();
  geo_convex_hull_returns_negative_1_when_size_is_less_than_3();
  geo_convex_hull_returns_negative_1_when_any_point_in_points_is_null();
  geo_convex_hull_returns_3_and_hull_has_points_in_order_when_given_points_for_triangle();
  geo_convex_hull_returns_5_and_hull_has_points_in_ccw_order_when_given_point_cloud();
  geo_convex_hull_returns_4_and_hull_has_points_in_ccw_order_using_furthest_colinear_point_when_given_point_cloud_with_colinear_points();
  printf("All tests pass.\n");
  return 0;
}
