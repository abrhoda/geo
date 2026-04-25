#include "geo_int.h"
#include <assert.h>
#include <stdio.h>

/*----------------------------------
 * geo_points_equal_int tests
 *----------------------------------
 */
void geo_points_equal_int_returns_geo_err_null_pointer_result_code_when_lhs_is_null(void) {
  struct geo_point_int point = {0, 0};
  bool is_eq = false;
  enum geo_result result = geo_points_equal_int(NULL, &point, &is_eq);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_points_equal_int_returns_geo_err_null_pointer_result_code_when_rhs_is_null(void) {
  struct geo_point_int point = {0.0, 0};
  bool is_eq = false;
  enum geo_result result = geo_points_equal_int(&point, NULL, &is_eq);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_points_equal_int_returns_geo_success_and_is_equal_set_to_1_when_lhs_and_rhs_are_exactly_equal(void) {
  struct geo_point_int point1 = {1, 2};
  struct geo_point_int point2 = {1, 2};
  bool is_eq = false;
  enum geo_result result = geo_points_equal_int(&point1, &point2, &is_eq);
  assert(result == GEO_SUCCESS);
  assert(is_eq == true);
}

void geo_points_equal_int_returns_geo_success_and_is_equal_set_to_0_when_lhs_neither_x_or_y_and_rhs_x_or_y_are_within_epsilon(void) {
  struct geo_point_int point1 = {2, 3};
  struct geo_point_int point2 = {10, 10};
  bool is_eq = false;
  enum geo_result result = geo_points_equal_int(&point1, &point2, &is_eq);
  assert(result == GEO_SUCCESS);
  assert(is_eq == false);
}

/*----------------------------------
 * geo_segments_intersect_int tests
 *----------------------------------
 */
void geo_segments_intersect_int_returns_geo_err_null_pointer_result_code_when_segment_1_is_null(void) {
  struct geo_point_int point1 = {2, 3};
  struct geo_point_int point2 = {1, 2};
  struct geo_segment_int segment;
  enum geo_result result = 0;
  size_t intersect_count = 0;
  segment.start = &point1;
  segment.end = &point2;
  result = geo_segments_intersect_int(NULL, &segment, &intersect_count);
  assert(result == GEO_ERR_NULL_POINTER);
}
void geo_segments_intersect_int_returns_geo_err_null_pointer_result_code_when_segment_2_is_null(void) {
  struct geo_point_int point1 = {2, 3};
  struct geo_point_int point2 = {1, 2};
  struct geo_segment_int segment;
  enum geo_result result = 0;
  size_t intersect_count = 0;
  segment.start = &point1;
  segment.end = &point2;
  result = geo_segments_intersect_int(&segment, NULL, &intersect_count);
  assert(result == GEO_ERR_NULL_POINTER);
}
void geo_segments_intersect_int_returns_geo_err_null_pointer_result_code_when_segment_1_start_is_null(void) {
  /*struct geo_point_int point1 = {2, 3};*/
  struct geo_point_int point2 = {1, 2};
  struct geo_point_int point3 = {7, 3};
  struct geo_point_int point4 = {6, 2};
  struct geo_segment_int segment1;
  struct geo_segment_int segment2;
  enum geo_result result = 0;
  size_t intersect_count = 0;
  segment1.start = NULL;
  segment1.end = &point2;
  segment2.start = &point3;
  segment2.end = &point4;
  result = geo_segments_intersect_int(&segment1, &segment2, &intersect_count);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_segments_intersect_int_returns_geo_err_null_pointer_result_code_when_segment_1_end_is_null(void) {
  struct geo_point_int point1 = {2, 3};
  /*struct geo_point_int point2 = {1.5F, 2};*/
  struct geo_point_int point3 = {7, 3};
  struct geo_point_int point4 = {6, 2};
  struct geo_segment_int segment1;
  struct geo_segment_int segment2;
  enum geo_result result = 0;
  size_t intersect_count = 0;
  segment1.start = &point1;
  segment1.end = NULL;
  segment2.start = &point3;
  segment2.end = &point4;
  result = geo_segments_intersect_int(&segment1, &segment2, &intersect_count);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_segments_intersect_int_returns_geo_err_null_pointer_result_code_when_segment_2_start_is_null(void) {
  struct geo_point_int point1 = {2, 3};
  struct geo_point_int point2 = {1, 2};
  /*struct geo_point_int point3 = {7, 3};*/
  struct geo_point_int point4 = {6, 2};
  struct geo_segment_int segment1;
  struct geo_segment_int segment2;
  enum geo_result result = 0;
  size_t intersect_count = 0;
  segment1.start = &point1;
  segment1.end = &point2;
  segment2.start = NULL;
  segment2.end = &point4;
  result = geo_segments_intersect_int(&segment1, &segment2, &intersect_count);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_segments_intersect_int_returns_geo_err_null_pointer_result_code_when_segment_2_end_is_null(void) {
  struct geo_point_int point1 = {2, 3};
  struct geo_point_int point2 = {1, 2};
  struct geo_point_int point3 = {7, 3};
  /*struct geo_point_int point4 = {6.5F, 2};*/
  struct geo_segment_int segment1;
  struct geo_segment_int segment2;
  enum geo_result result = 0;
  size_t intersect_count = 0;
  segment1.start = &point1;
  segment1.end = &point2;
  segment2.start = &point3;
  segment2.end = NULL;
  result = geo_segments_intersect_int(&segment1, &segment2, &intersect_count);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_segments_intersect_int_returns_geo_success_and_intersect_count_is_0_when_segments_are_parallel(void) {
  struct geo_point_int point1 = {0, 3};
  struct geo_point_int point2 = {3, 3};
  struct geo_point_int point3 = {0, 4};
  struct geo_point_int point4 = {3, 4};
  struct geo_segment_int segment1;
  struct geo_segment_int segment2;
  enum geo_result result = 0;
  size_t intersect_count = 0;
  segment1.start = &point1;
  segment1.end = &point2;
  segment2.start = &point3;
  segment2.end = &point4;
  result = geo_segments_intersect_int(&segment1, &segment2, &intersect_count);
  assert(result == GEO_SUCCESS);
  assert(intersect_count == 0);
}

void geo_segments_intersect_int_returns_geo_success_and_intersect_count_is_0_when_segments_are_colinear_but_dont_intersect(void) {
  struct geo_point_int point1 = {0, 0};
  struct geo_point_int point2 = {1, 0};
  struct geo_point_int point3 = {2, 0};
  struct geo_point_int point4 = {3, 0};
  struct geo_segment_int segment1;
  struct geo_segment_int segment2;
  enum geo_result result = 0;
  size_t intersect_count = 0;
  segment1.start = &point1;
  segment1.end = &point2;
  segment2.start = &point3;
  segment2.end = &point4;
  result = geo_segments_intersect_int(&segment1, &segment2, &intersect_count);
  assert(result == GEO_SUCCESS);
  assert(intersect_count == 0);
}

void geo_segments_intersect_int_returns_geo_success_and_intersect_count_is_0_when_segments_dont_intersect(void) {
  struct geo_point_int point1 = {0, 0};
  struct geo_point_int point2 = {1, 1};
  struct geo_point_int point3 = {2, 3};
  struct geo_point_int point4 = {3, 5};
  struct geo_segment_int segment1;
  struct geo_segment_int segment2;
  enum geo_result result = 0;
  size_t intersect_count = 0;
  segment1.start = &point1;
  segment1.end = &point2;
  segment2.start = &point3;
  segment2.end = &point4;
  result = geo_segments_intersect_int(&segment1, &segment2, &intersect_count);
  assert(result == GEO_SUCCESS);
  assert(intersect_count == 0);
}

void geo_segments_intersect_int_returns_geo_success_and_intersect_count_is_1_when_segments_properly_intersect(void) {
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

  struct geo_point_int point1 = {0, 0};
  struct geo_point_int point2 = {2, 2};
  struct geo_point_int point3 = {0, 2};
  struct geo_point_int point4 = {2, 0};
  struct geo_segment_int segment1;
  struct geo_segment_int segment2;
  enum geo_result result = 0;
  size_t intersect_count = 0;
  segment1.start = &point1;
  segment1.end = &point2;
  segment2.start = &point3;
  segment2.end = &point4;
  result = geo_segments_intersect_int(&segment1, &segment2, &intersect_count);
  assert(result == GEO_SUCCESS);
  assert(intersect_count == 1);
}

void geo_segments_intersect_int_returns_geo_success_and_intersect_count_is_2_when_segment_1_end_is_equal_to_segment_2_start(void) {
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
  struct geo_point_int point1 = {0, 0};
  struct geo_point_int point2 = {1, 1};
  struct geo_point_int point3 = {0, 1};
  struct geo_point_int point4 = {1, 1};
  struct geo_segment_int segment1;
  struct geo_segment_int segment2;
  enum geo_result result = 0;
  size_t intersect_count = 0;
  segment1.start = &point1;
  segment1.end = &point2;
  segment2.start = &point3;
  segment2.end = &point4;
  result = geo_segments_intersect_int(&segment1, &segment2, &intersect_count);
  assert(result == GEO_SUCCESS);
  assert(intersect_count == 2);
}

void geo_segments_intersect_int_returns_geo_success_and_intersect_count_is_2_when_one_segment_is_section_of_other_segment(void) {
  /*
   * o----o----o----o
   * |    |    |    |
   * p1   p3   p4   p2
   *
   */
  struct geo_point_int point1 = {0, 0};
  struct geo_point_int point2 = {3, 0};
  struct geo_point_int point3 = {1, 0};
  struct geo_point_int point4 = {2, 0};
  struct geo_segment_int segment1;
  struct geo_segment_int segment2;
  enum geo_result result = 0;
  size_t intersect_count = 0;
  segment1.start = &point1;
  segment1.end = &point2;
  segment2.start = &point3;
  segment2.end = &point4;
  result = geo_segments_intersect_int(&segment1, &segment2, &intersect_count);
  assert(result == GEO_SUCCESS);
  assert(intersect_count == 2);
}

void geo_segments_intersect_int_returns_geo_success_and_intersect_count_is_3_when_segment_1_is_section_of_segment_2_and_share_1_end(void) {
  /*
   * o----o--------o
   * |    |        |
   * p1   p3    p2 + p4
   * */
  struct geo_point_int point1 = {0, 0};
  struct geo_point_int point2 = {2, 0};
  struct geo_point_int point3 = {1, 0};
  struct geo_point_int point4 = {2, 0};
  struct geo_segment_int segment1;
  struct geo_segment_int segment2;
  enum geo_result result = 0;
  size_t intersect_count = 0;
  segment1.start = &point1;
  segment1.end = &point2;
  segment2.start = &point3;
  segment2.end = &point4;
  result = geo_segments_intersect_int(&segment1, &segment2, &intersect_count);
  assert(result == GEO_SUCCESS);
  assert(intersect_count == 3);
}

void geo_segments_intersect_int_returns_geo_success_and_intersect_count_is_4_when_segment_1_is_the_same_segment_as_segment_2(void) {
  /*
   * o--------------o
   * |              |
   * p1+p3          p2+p4
   */
  struct geo_point_int point1 = {0, 0};
  struct geo_point_int point2 = {2, 0};
  struct geo_point_int point3 = {0, 0};
  struct geo_point_int point4 = {2, 0};
  struct geo_segment_int segment1;
  struct geo_segment_int segment2;
  enum geo_result result = 0;
  size_t intersect_count = 0;
  segment1.start = &point1;
  segment1.end = &point2;
  segment2.start = &point3;
  segment2.end = &point4;
  result = geo_segments_intersect_int(&segment1, &segment2, &intersect_count);
  assert(result == GEO_SUCCESS);
  assert(intersect_count == 4);
}


/*----------------------------------
 * geo_geometry_is_closed_int tests
 *----------------------------------
 */
void geo_geometry_is_closed_int_returns_geo_err_null_pointer_when_geometry_is_null(void) {
  struct geo_geometry_int * geometry = NULL;
  bool is_closed = false;
  enum geo_result result = geo_geometry_is_closed_int(geometry, &is_closed);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_geometry_is_closed_int_returns_geo_err_null_pointer_when_geometry_segments_is_null(void) {
  struct geo_geometry_int geometry;
  geometry.segments_count = 0;
  geometry.segments = NULL;
  bool is_closed = false;
  enum geo_result result = geo_geometry_is_closed_int(&geometry, &is_closed);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_geometry_is_closed_int_returns_geo_err_null_pointer_when_geometry_segment_start_is_null(void) {
  struct geo_point_int start1 = {0, 0};
  struct geo_point_int end1 = {3, 0};
  struct geo_point_int start2 = {3, 0};
  struct geo_point_int start3 = {1, 3};
  struct geo_point_int end3 = {0, 0};
  struct geo_segment_int segment1;
  struct geo_segment_int segment2;
  struct geo_segment_int segment3;
  struct geo_segment_int * segments[3];
  struct geo_geometry_int geometry;
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
  enum geo_result result = geo_geometry_is_closed_int(&geometry, &is_closed);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_geometry_is_closed_int_returns_geo_err_null_pointer_when_geometry_segment_end_is_null(void) {
  struct geo_point_int start1 = {0, 0};
  struct geo_point_int end1 = {3, 0};
  /*struct geo_point_int start2 = {3, 0};*/
  struct geo_point_int end2 = {1, 3};
  struct geo_point_int start3 = {1, 3};
  struct geo_point_int end3 = {0, 0};
  struct geo_segment_int segment1;
  struct geo_segment_int segment2;
  struct geo_segment_int segment3;
  struct geo_segment_int * segments[3];
  struct geo_geometry_int geometry;
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
  enum geo_result result = geo_geometry_is_closed_int(&geometry, &is_closed);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_geometry_is_closed_int_returns_geo_err_too_small_when_geometry_segment_count_less_than_3(void) {
  struct geo_point_int start1 = {2, 0};
  struct geo_point_int end1 = {3, 0};
  struct geo_point_int start2 = {3, 0};
  struct geo_point_int end2 = {6, 1};
  struct geo_segment_int segment1;
  struct geo_segment_int segment2;
  struct geo_segment_int * segments[2];
  struct geo_geometry_int geometry;
  segment1.start = &start1;
  segment1.end = &end1;
  segments[0] = &segment1;
  segment2.start = &start2;
  segment2.end = &end2;
  segments[1] = &segment2;
  geometry.segments_count = 2;
  geometry.segments = segments;

  bool is_closed = false;
  enum geo_result result = geo_geometry_is_closed_int(&geometry, &is_closed);
  assert(result == GEO_ERR_TOO_SMALL);
}

void geo_geometry_is_closed_int_returns_geo_success_and_is_closed_is_false_when_nth_segments_end_doesnt_equal_n_plus_1_segment_start(void) {
  struct geo_point_int start1 = {0, 0};
  struct geo_point_int end1 = {3, 0};
  struct geo_point_int start2 = {3, 0};
  struct geo_point_int end2 = {1, 3};
  struct geo_point_int start3 = {1, 3};

  /* GAP HERE */
  struct geo_point_int end3 = {-1, -1};
  struct geo_segment_int segment1;
  struct geo_segment_int segment2;
  struct geo_segment_int segment3;
  struct geo_segment_int * segments[3];
  struct geo_geometry_int geometry;
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
  enum geo_result result = geo_geometry_is_closed_int(&geometry, &is_closed);
  assert(result == GEO_SUCCESS);
  assert(is_closed == false);
}

void geo_geometry_is_closed_int_returns_geo_success_and_is_closed_is_true_when_nth_segments_end_equals_n_plus_1_segments_start(void) {
  struct geo_point_int start1 = {0, 0};
  struct geo_point_int end1 = {3, 0};
  struct geo_point_int start2 = {3, 0};
  struct geo_point_int end2 = {1, 3};
  struct geo_point_int start3 = {1, 3};
  struct geo_point_int end3 = {0, 0};
  struct geo_segment_int segment1;
  struct geo_segment_int segment2;
  struct geo_segment_int segment3;
  struct geo_segment_int * segments[3];
  struct geo_geometry_int geometry;
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
  enum geo_result result = geo_geometry_is_closed_int(&geometry, &is_closed);
  assert(result == GEO_SUCCESS);
  assert(is_closed == true);
}

/*----------------------------------
 * geo_geometry_is_simple_int tests
 *----------------------------------
 */
void geo_geometry_is_simple_int_returns_geo_err_null_pointer_when_geometry_is_null(void) {
  struct geo_geometry_int * geometry = NULL;
  bool is_simple = false;
  enum geo_result result = geo_geometry_is_simple_int(geometry, &is_simple);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_geometry_is_simple_int_returns_geo_err_null_pointer_when_geometry_segments_is_null(void) {
  struct geo_geometry_int geometry;
  geometry.segments_count = 0;
  geometry.segments = NULL;

  bool is_simple = false;
  enum geo_result result = geo_geometry_is_simple_int(&geometry, &is_simple);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_geometry_is_simple_int_returns_geo_err_null_pointer_when_geometry_segments_ith_start_is_null(void) {
  struct geo_point_int start1 = {0, 0};
  struct geo_point_int end1 = {3, 0};
  struct geo_point_int start2 = {3, 0};
  struct geo_point_int end2 = {3, 3};
  struct geo_point_int start3 = {3, 3};
  struct geo_point_int end3 = {0, 3};
  struct geo_point_int start4 = {0, 3};
  struct geo_point_int end4 = {0, 0};
  struct geo_segment_int segment1;
  struct geo_segment_int segment2;
  struct geo_segment_int segment3;
  struct geo_segment_int segment4;
  struct geo_segment_int * segments[4];
  struct geo_geometry_int geometry;
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
  enum geo_result result = geo_geometry_is_simple_int(&geometry, &is_simple);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_geometry_is_simple_int_returns_geo_err_null_pointer_when_geometry_segments_ith_end_is_null(void) {
  struct geo_point_int start1 = {0, 0};
  struct geo_point_int end1 = {3, 0};
  struct geo_point_int start2 = {3, 0};
  struct geo_point_int end2 = {3, 3};
  struct geo_point_int start3 = {3, 3};
  struct geo_point_int end3 = {0, 3};
  struct geo_point_int start4 = {0, 3};
  struct geo_point_int end4 = {0, 0};
  struct geo_segment_int segment1;
  struct geo_segment_int segment2;
  struct geo_segment_int segment3;
  struct geo_segment_int segment4;
  struct geo_segment_int * segments[4];
  struct geo_geometry_int geometry;
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
  enum geo_result result = geo_geometry_is_simple_int(&geometry, &is_simple);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_geometry_is_simple_int_returns_geo_err_too_small_when_geometry_segments_count_less_than_3(void) {
  struct geo_point_int start1 = {0, 0};
  struct geo_point_int end1 = {3, 0};
  struct geo_point_int start2 = {3, 0};
  struct geo_point_int end2 = {3, 3};
  struct geo_segment_int segment1;
  struct geo_segment_int segment2;
  struct geo_segment_int * segments[2];
  struct geo_geometry_int geometry;
  segment1.start = &start1;
  segment1.end = &end1;
  segments[0] = &segment1;
  segment2.start = &start2;
  segment2.end = &end2;
  segments[1] = &segment2;
  geometry.segments_count = 2;
  geometry.segments = segments;

  bool is_simple = false;
  enum geo_result result = geo_geometry_is_simple_int(&geometry, &is_simple);
  assert(result == GEO_ERR_TOO_SMALL);
}

void geo_geometry_is_simple_int_returns_geo_success_and_is_simple_is_false_when_any_segments_intersect(void) {
  struct geo_point_int start1 = {0, 0};
  struct geo_point_int end1 = {3, 3};
  struct geo_point_int start2 = {3, 3};
  struct geo_point_int end2 = {3, 0};
  struct geo_point_int start3 = {3, 0};
  struct geo_point_int end3 = {0, 3};
  struct geo_point_int start4 = {0, 3};
  struct geo_point_int end4 = {0, 0};
  struct geo_segment_int segment1;
  struct geo_segment_int segment2;
  struct geo_segment_int segment3;
  struct geo_segment_int segment4;
  struct geo_segment_int * segments[4];
  struct geo_geometry_int geometry;
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
  enum geo_result result = geo_geometry_is_simple_int(&geometry, &is_simple);
  assert(result == GEO_SUCCESS);
  assert(is_simple == false);
}

void geo_geometry_is_simple_int_returns_geo_success_and_is_simple_is_true_when_no_segments_intersect(void) {
  struct geo_point_int start1 = {0, 0};
  struct geo_point_int end1 = {3, 0};
  struct geo_point_int start2 = {3, 0};
  struct geo_point_int end2 = {3, 3};
  struct geo_point_int start3 = {3, 3};
  struct geo_point_int end3 = {0, 3};
  struct geo_point_int start4 = {0, 3};
  struct geo_point_int end4 = {0, 0};
  struct geo_segment_int segment1;
  struct geo_segment_int segment2;
  struct geo_segment_int segment3;
  struct geo_segment_int segment4;
  struct geo_segment_int * segments[4];
  struct geo_geometry_int geometry;
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
  enum geo_result result = geo_geometry_is_simple_int(&geometry, &is_simple);
  assert(result == GEO_SUCCESS);
  assert(is_simple == true);
}

/*----------------------------------
 * geo_point_in_geometry_int tests
 *----------------------------------
 */
void geo_point_in_geometry_int_returns_geo_err_null_pointer_when_point_is_null(void) {
  struct geo_geometry_int geometry;
  struct geo_segment_int * segments[3];
  bool strict = true;
  bool inside = false;
  geometry.segments = segments;
  geometry.segments_count = 3;
  enum geo_result result = geo_point_in_geometry_int(NULL, &geometry, strict, &inside);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_point_in_geometry_int_returns_geo_err_null_pointer_when_geometry_is_null(void) {
  struct geo_point_int point = { 0, 0 };
  bool strict = true;
  bool inside = false;
  enum geo_result result = geo_point_in_geometry_int(&point, NULL, strict, &inside);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_point_in_geometry_int_returns_geo_err_null_pointer_when_geometry_segments_is_null(void) {
  struct geo_geometry_int geometry;
  struct geo_point_int point = { 0, 0 };
  bool strict = true;
  bool inside = false;
  geometry.segments = NULL;
  geometry.segments_count = 3;

  enum geo_result result = geo_point_in_geometry_int(&point, &geometry, strict, &inside);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_point_in_geometry_int_returns_geo_err_null_pointer_when_geometry_segments_ith_start_is_null(void) {
  bool strict = true;
  bool inside = false;
  struct geo_point_int point = {1, 1};
  struct geo_point_int start1 = {0, 0};
  struct geo_point_int end1 = {3, 0};
  struct geo_point_int start2 = {3, 0};
  struct geo_point_int end2 = {3, 3};
  struct geo_point_int start3 = {3, 3};
  struct geo_point_int end3 = {0, 3};
  struct geo_point_int start4 = {0, 3};
  struct geo_point_int end4 = {0, 0};
  struct geo_segment_int segment1;
  struct geo_segment_int segment2;
  struct geo_segment_int segment3;
  struct geo_segment_int segment4;
  struct geo_segment_int * segments[4];
  struct geo_geometry_int geometry;
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

  enum geo_result result = geo_point_in_geometry_int(&point, &geometry, strict, &inside);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_point_in_geometry_int_returns_geo_err_null_pointer_when_geometry_segments_ith_end_is_null(void) {
  bool strict = true;
  bool inside = false;
  struct geo_point_int point = {1, 1};
  struct geo_point_int start1 = {0, 0};
  struct geo_point_int end1 = {3, 0};
  struct geo_point_int start2 = {3, 0};
  struct geo_point_int end2 = {3, 3};
  struct geo_point_int start3 = {3, 3};
  struct geo_point_int end3 = {0, 3};
  struct geo_point_int start4 = {0, 3};
  struct geo_point_int end4 = {0, 0};
  struct geo_segment_int segment1;
  struct geo_segment_int segment2;
  struct geo_segment_int segment3;
  struct geo_segment_int segment4;
  struct geo_segment_int * segments[4];
  struct geo_geometry_int geometry;
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

  enum geo_result result = geo_point_in_geometry_int(&point, &geometry, strict, &inside);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_point_in_geometry_int_returns_geo_err_too_small_when_geometry_segments_count_is_less_than_3(void) {
  bool strict = true;
  bool inside = false;
  struct geo_point_int point = {1, 1};
  struct geo_point_int start1 = {0, 0};
  struct geo_point_int end1 = {3, 0};
  struct geo_point_int start2 = {3, 0};
  struct geo_point_int end2 = {3, 3};
  struct geo_segment_int segment1;
  struct geo_segment_int segment2;
  struct geo_segment_int * segments[2];
  struct geo_geometry_int geometry;
  segment1.start = &start1;
  segment1.end = &end1;
  segments[0] = &segment1;
  segment2.start = &start2;
  segment2.end = &end2;
  segments[1] = &segment2;
  geometry.segments_count = 2;
  geometry.segments = segments;

  enum geo_result result = geo_point_in_geometry_int(&point, &geometry, strict, &inside);
  assert(result == GEO_ERR_TOO_SMALL);
}

void geo_poiny_in_geometry_returns_geo_success_and_is_inside_set_to_false_when_point_on_geometry_segment_and_strict_is_true(void) {
  bool strict = true;
  bool inside = false;
  struct geo_point_int point = {3, 1};
  struct geo_point_int start1 = {0, 0};
  struct geo_point_int end1 = {3, 0};
  struct geo_point_int start2 = {3, 0};
  struct geo_point_int end2 = {3, 3};
  struct geo_point_int start3 = {3, 3};
  struct geo_point_int end3 = {0, 3};
  struct geo_point_int start4 = {0, 3};
  struct geo_point_int end4 = {0, 0};
  struct geo_segment_int segment1;
  struct geo_segment_int segment2;
  struct geo_segment_int segment3;
  struct geo_segment_int segment4;
  struct geo_segment_int * segments[4];
  struct geo_geometry_int geometry;
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

  enum geo_result result = geo_point_in_geometry_int(&point, &geometry, strict, &inside);
  assert(result == GEO_SUCCESS);
  assert(inside == false);
}

void geo_poiny_in_geometry_returns_geo_success_and_is_inside_set_to_true_when_point_on_geometry_segment_and_strict_is_false(void) {
  bool strict = false;
  bool inside = false;
  struct geo_point_int point = {3, 1};
  struct geo_point_int start1 = {0, 0};
  struct geo_point_int end1 = {3, 0};
  struct geo_point_int start2 = {3, 0};
  struct geo_point_int end2 = {3, 3};
  struct geo_point_int start3 = {3, 3};
  struct geo_point_int end3 = {0, 3};
  struct geo_point_int start4 = {0, 3};
  struct geo_point_int end4 = {0, 0};
  struct geo_segment_int segment1;
  struct geo_segment_int segment2;
  struct geo_segment_int segment3;
  struct geo_segment_int segment4;
  struct geo_segment_int * segments[4];
  struct geo_geometry_int geometry;
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

  enum geo_result result = geo_point_in_geometry_int(&point, &geometry, strict, &inside);
  assert(result == GEO_SUCCESS);
  assert(inside == true);
}

void geo_poiny_in_geometry_returns_geo_success_and_is_inside_set_to_false_when_point_is_to_the_left_of_the_geometry_and_colinear_with_horizontal_segment(void) {
  bool strict = true;
  bool inside = false;
  struct geo_point_int point = {3, -1};
  struct geo_point_int start1 = {0, 0};
  struct geo_point_int end1 = {3, 0};
  struct geo_point_int start2 = {3, 0};
  struct geo_point_int end2 = {3, 3};
  struct geo_point_int start3 = {3, 3};
  struct geo_point_int end3 = {0, 3};
  struct geo_point_int start4 = {0, 3};
  struct geo_point_int end4 = {0, 0};
  struct geo_segment_int segment1;
  struct geo_segment_int segment2;
  struct geo_segment_int segment3;
  struct geo_segment_int segment4;
  struct geo_segment_int * segments[4];
  struct geo_geometry_int geometry;
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

  enum geo_result result = geo_point_in_geometry_int(&point, &geometry, strict, &inside);
  assert(result == GEO_SUCCESS);
  assert(inside == false);
}

void geo_poiny_in_geometry_returns_geo_success_and_is_inside_set_to_false_when_point_is_to_the_right_of_the_geometry_and_colinear_with_horizontal_segment(void) {
  bool strict = true;
  bool inside = false;
  struct geo_point_int point = {4, 0};
  struct geo_point_int start1 = {0, 0};
  struct geo_point_int end1 = {3, 0};
  struct geo_point_int start2 = {3, 0};
  struct geo_point_int end2 = {3, 3};
  struct geo_point_int start3 = {3, 3};
  struct geo_point_int end3 = {0, 3};
  struct geo_point_int start4 = {0, 3};
  struct geo_point_int end4 = {0, 0};
  struct geo_segment_int segment1;
  struct geo_segment_int segment2;
  struct geo_segment_int segment3;
  struct geo_segment_int segment4;
  struct geo_segment_int * segments[4];
  struct geo_geometry_int geometry;
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

  enum geo_result result = geo_point_in_geometry_int(&point, &geometry, strict, &inside);
  assert(result == GEO_SUCCESS);
  assert(inside == false);
}

void geo_poiny_in_geometry_returns_geo_success_and_is_inside_set_to_false_when_point_is_above_of_the_geometry_and_colinear_with_vertical_segment(void) {
  bool strict = true;
  bool inside = false;
  struct geo_point_int point = {0, 4};
  struct geo_point_int start1 = {0, 0};
  struct geo_point_int end1 = {3, 0};
  struct geo_point_int start2 = {3, 0};
  struct geo_point_int end2 = {3, 3};
  struct geo_point_int start3 = {3, 3};
  struct geo_point_int end3 = {0, 3};
  struct geo_point_int start4 = {0, 3};
  struct geo_point_int end4 = {0, 0};
  struct geo_segment_int segment1;
  struct geo_segment_int segment2;
  struct geo_segment_int segment3;
  struct geo_segment_int segment4;
  struct geo_segment_int * segments[4];
  struct geo_geometry_int geometry;
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

  enum geo_result result = geo_point_in_geometry_int(&point, &geometry, strict, &inside);
  assert(result == GEO_SUCCESS);
  assert(inside == false);
}

void geo_poiny_in_geometry_returns_geo_success_and_is_inside_set_to_false_when_point_is_below_of_the_geometry_and_colinear_with_vertical_segment(void) {
  bool strict = true;
  bool inside = false;
  struct geo_point_int point = {0, -1};
  struct geo_point_int start1 = {0, 0};
  struct geo_point_int end1 = {3, 0};
  struct geo_point_int start2 = {3, 0};
  struct geo_point_int end2 = {3, 3};
  struct geo_point_int start3 = {3, 3};
  struct geo_point_int end3 = {0, 3};
  struct geo_point_int start4 = {0, 3};
  struct geo_point_int end4 = {0, 0};
  struct geo_segment_int segment1;
  struct geo_segment_int segment2;
  struct geo_segment_int segment3;
  struct geo_segment_int segment4;
  struct geo_segment_int * segments[4];
  struct geo_geometry_int geometry;
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

  enum geo_result result = geo_point_in_geometry_int(&point, &geometry, strict, &inside);
  assert(result == GEO_SUCCESS);
  assert(inside == false);
}

/*----------------------------------
 * geo_geometry_in_geometry_int tests
 *----------------------------------
 */
void geo_geometry_in_geometry_int_returns_geo_err_null_pointer_when_parent_geometry_is_null(void) {
  bool is_inside = false;
  bool strict = true;
  enum geo_result result = GEO_SUCCESS;
  struct geo_point_int parent_vertex1 = { 0, 0 };
  struct geo_point_int parent_vertex2 = { 5, 0 };
  struct geo_point_int parent_vertex3 = { 5, 5 };
  struct geo_point_int parent_vertex4 = { 0, 5 };
  struct geo_point_int child_vertex1 = { 1, 1 };
  struct geo_point_int child_vertex2 = { 3, 1 };
  struct geo_point_int child_vertex3 = { 3, 3 };
  struct geo_point_int child_vertex4 = { 1, 3 };
  struct geo_segment_int parent_segment1;
  struct geo_segment_int parent_segment2;
  struct geo_segment_int parent_segment3;
  struct geo_segment_int parent_segment4;
  struct geo_segment_int child_segment1;
  struct geo_segment_int child_segment2;
  struct geo_segment_int child_segment3;
  struct geo_segment_int child_segment4;
  struct geo_segment_int *parent_segments[4];
  struct geo_segment_int *child_segments[4];
  struct geo_geometry_int parent;
  struct geo_geometry_int child;
  size_t parent_segments_count = 4;
  size_t child_segments_count = 4;
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
  result = geo_geometry_in_geometry_int(NULL, &child, strict, &is_inside);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_geometry_in_geometry_int_returns_geo_err_null_pointer_when_parent_geometry_segments_is_null(void) {
  bool is_inside = false;
  bool strict = true;
  enum geo_result result = GEO_SUCCESS;
  struct geo_point_int parent_vertex1 = { 0, 0 };
  struct geo_point_int parent_vertex2 = { 5, 0 };
  struct geo_point_int parent_vertex3 = { 5, 5 };
  struct geo_point_int parent_vertex4 = { 0, 5 };
  struct geo_point_int child_vertex1 = { 1, 1 };
  struct geo_point_int child_vertex2 = { 3, 1 };
  struct geo_point_int child_vertex3 = { 3, 3 };
  struct geo_point_int child_vertex4 = { 1, 3 };
  struct geo_segment_int parent_segment1;
  struct geo_segment_int parent_segment2;
  struct geo_segment_int parent_segment3;
  struct geo_segment_int parent_segment4;
  struct geo_segment_int child_segment1;
  struct geo_segment_int child_segment2;
  struct geo_segment_int child_segment3;
  struct geo_segment_int child_segment4;
  struct geo_segment_int *parent_segments[4];
  struct geo_segment_int *child_segments[4];
  struct geo_geometry_int parent;
  struct geo_geometry_int child;
  size_t parent_segments_count = 4;
  size_t child_segments_count = 4;
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
  result = geo_geometry_in_geometry_int(&parent, &child, strict, &is_inside);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_geometry_in_geometry_int_returns_geo_err_null_pointer_when_parent_geometry_ith_segment_is_null(void) {
  bool is_inside = false;
  bool strict = true;
  enum geo_result result = GEO_SUCCESS;
  struct geo_point_int parent_vertex1 = { 0, 0 };
  struct geo_point_int parent_vertex2 = { 5, 0 };
  struct geo_point_int parent_vertex3 = { 5, 5 };
  struct geo_point_int parent_vertex4 = { 0, 5 };
  struct geo_point_int child_vertex1 = { 1, 1 };
  struct geo_point_int child_vertex2 = { 3, 1 };
  struct geo_point_int child_vertex3 = { 3, 3 };
  struct geo_point_int child_vertex4 = { 1, 3 };
  struct geo_segment_int parent_segment1;
  struct geo_segment_int parent_segment2;
  struct geo_segment_int parent_segment3;
  struct geo_segment_int parent_segment4;
  struct geo_segment_int child_segment1;
  struct geo_segment_int child_segment2;
  struct geo_segment_int child_segment3;
  struct geo_segment_int child_segment4;
  struct geo_segment_int *parent_segments[4];
  struct geo_segment_int *child_segments[4];
  struct geo_geometry_int parent;
  struct geo_geometry_int child;
  size_t parent_segments_count = 4;
  size_t child_segments_count = 4;
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
  result = geo_geometry_in_geometry_int(&parent, &child, strict, &is_inside);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_geometry_in_geometry_int_returns_geo_err_null_pointer_when_parent_geometry_ith_segment_start_point_is_null(void) {
  bool is_inside = false;
  bool strict = true;
  enum geo_result result = GEO_SUCCESS;
  struct geo_point_int parent_vertex1 = { 0, 0 };
  struct geo_point_int parent_vertex2 = { 5, 0 };
  struct geo_point_int parent_vertex3 = { 5, 5 };
  struct geo_point_int parent_vertex4 = { 0, 5 };
  struct geo_point_int child_vertex1 = { 1, 1 };
  struct geo_point_int child_vertex2 = { 3, 1 };
  struct geo_point_int child_vertex3 = { 3, 3 };
  struct geo_point_int child_vertex4 = { 1, 3 };
  struct geo_segment_int parent_segment1;
  struct geo_segment_int parent_segment2;
  struct geo_segment_int parent_segment3;
  struct geo_segment_int parent_segment4;
  struct geo_segment_int child_segment1;
  struct geo_segment_int child_segment2;
  struct geo_segment_int child_segment3;
  struct geo_segment_int child_segment4;
  struct geo_segment_int *parent_segments[4];
  struct geo_segment_int *child_segments[4];
  struct geo_geometry_int parent;
  struct geo_geometry_int child;
  size_t parent_segments_count = 4;
  size_t child_segments_count = 4;
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
  result = geo_geometry_in_geometry_int(&parent, &child, strict, &is_inside);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_geometry_in_geometry_int_returns_geo_err_null_pointer_when_parent_geometry_ith_segment_end_point_is_null(void) {
  bool is_inside = false;
  bool strict = true;
  enum geo_result result = GEO_SUCCESS;
  struct geo_point_int parent_vertex1 = { 0, 0 };
  struct geo_point_int parent_vertex2 = { 5, 0 };
  struct geo_point_int parent_vertex3 = { 5, 5 };
  struct geo_point_int parent_vertex4 = { 0, 5 };
  struct geo_point_int child_vertex1 = { 1, 1 };
  struct geo_point_int child_vertex2 = { 3, 1 };
  struct geo_point_int child_vertex3 = { 3, 3 };
  struct geo_point_int child_vertex4 = { 1, 3 };
  struct geo_segment_int parent_segment1;
  struct geo_segment_int parent_segment2;
  struct geo_segment_int parent_segment3;
  struct geo_segment_int parent_segment4;
  struct geo_segment_int child_segment1;
  struct geo_segment_int child_segment2;
  struct geo_segment_int child_segment3;
  struct geo_segment_int child_segment4;
  struct geo_segment_int *parent_segments[4];
  struct geo_segment_int *child_segments[4];
  struct geo_geometry_int parent;
  struct geo_geometry_int child;
  size_t parent_segments_count = 4;
  size_t child_segments_count = 4;
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
  result = geo_geometry_in_geometry_int(&parent, &child, strict, &is_inside);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_geometry_in_geometry_int_returns_geo_err_null_pointer_when_child_geometry_is_null(void) {
  bool is_inside = false;
  bool strict = true;
  enum geo_result result = GEO_SUCCESS;
  struct geo_point_int parent_vertex1 = { 0, 0 };
  struct geo_point_int parent_vertex2 = { 5, 0 };
  struct geo_point_int parent_vertex3 = { 5, 5 };
  struct geo_point_int parent_vertex4 = { 0, 5 };
  struct geo_point_int child_vertex1 = { 1, 1 };
  struct geo_point_int child_vertex2 = { 3, 1 };
  struct geo_point_int child_vertex3 = { 3, 3 };
  struct geo_point_int child_vertex4 = { 1, 3 };
  struct geo_segment_int parent_segment1;
  struct geo_segment_int parent_segment2;
  struct geo_segment_int parent_segment3;
  struct geo_segment_int parent_segment4;
  struct geo_segment_int child_segment1;
  struct geo_segment_int child_segment2;
  struct geo_segment_int child_segment3;
  struct geo_segment_int child_segment4;
  struct geo_segment_int *parent_segments[4];
  struct geo_segment_int *child_segments[4];
  struct geo_geometry_int parent;
  struct geo_geometry_int child;
  size_t parent_segments_count = 4;
  size_t child_segments_count = 4;
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
  result = geo_geometry_in_geometry_int(&parent, NULL, strict, &is_inside);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_geometry_in_geometry_int_returns_geo_err_null_pointer_when_child_geometry_segments_is_null(void) {
  bool is_inside = false;
  bool strict = true;
  enum geo_result result = GEO_SUCCESS;
  struct geo_point_int parent_vertex1 = { 0, 0 };
  struct geo_point_int parent_vertex2 = { 5, 0 };
  struct geo_point_int parent_vertex3 = { 5, 5 };
  struct geo_point_int parent_vertex4 = { 0, 5 };
  struct geo_point_int child_vertex1 = { 1, 1 };
  struct geo_point_int child_vertex2 = { 3, 1 };
  struct geo_point_int child_vertex3 = { 3, 3 };
  struct geo_point_int child_vertex4 = { 1, 3 };
  struct geo_segment_int parent_segment1;
  struct geo_segment_int parent_segment2;
  struct geo_segment_int parent_segment3;
  struct geo_segment_int parent_segment4;
  struct geo_segment_int child_segment1;
  struct geo_segment_int child_segment2;
  struct geo_segment_int child_segment3;
  struct geo_segment_int child_segment4;
  struct geo_segment_int *parent_segments[4];
  struct geo_segment_int *child_segments[4];
  struct geo_geometry_int parent;
  struct geo_geometry_int child;
  size_t parent_segments_count = 4;
  size_t child_segments_count = 4;
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
  result = geo_geometry_in_geometry_int(&parent, &child, strict, &is_inside);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_geometry_in_geometry_int_returns_geo_err_null_pointer_when_child_geometry_ith_segment_is_null(void) {
  bool is_inside = false;
  bool strict = true;
  enum geo_result result = GEO_SUCCESS;
  struct geo_point_int parent_vertex1 = { 0, 0 };
  struct geo_point_int parent_vertex2 = { 5, 0 };
  struct geo_point_int parent_vertex3 = { 5, 5 };
  struct geo_point_int parent_vertex4 = { 0, 5 };
  struct geo_point_int child_vertex1 = { 1, 1 };
  struct geo_point_int child_vertex2 = { 3, 1 };
  struct geo_point_int child_vertex3 = { 3, 3 };
  struct geo_point_int child_vertex4 = { 1, 3 };
  struct geo_segment_int parent_segment1;
  struct geo_segment_int parent_segment2;
  struct geo_segment_int parent_segment3;
  struct geo_segment_int parent_segment4;
  struct geo_segment_int child_segment1;
  struct geo_segment_int child_segment2;
  struct geo_segment_int child_segment3;
  struct geo_segment_int child_segment4;
  struct geo_segment_int *parent_segments[4];
  struct geo_segment_int *child_segments[4];
  struct geo_geometry_int parent;
  struct geo_geometry_int child;
  size_t parent_segments_count = 4;
  size_t child_segments_count = 4;
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
  result = geo_geometry_in_geometry_int(&parent, &child, strict, &is_inside);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_geometry_in_geometry_int_returns_geo_err_null_pointer_when_child_geometry_ith_segment_start_point_is_null(void) {
  bool is_inside = false;
  bool strict = true;
  enum geo_result result = GEO_SUCCESS;
  struct geo_point_int parent_vertex1 = { 0, 0 };
  struct geo_point_int parent_vertex2 = { 5, 0 };
  struct geo_point_int parent_vertex3 = { 5, 5 };
  struct geo_point_int parent_vertex4 = { 0, 5 };
  struct geo_point_int child_vertex1 = { 1, 1 };
  struct geo_point_int child_vertex2 = { 3, 1 };
  struct geo_point_int child_vertex3 = { 3, 3 };
  struct geo_point_int child_vertex4 = { 1, 3 };
  struct geo_segment_int parent_segment1;
  struct geo_segment_int parent_segment2;
  struct geo_segment_int parent_segment3;
  struct geo_segment_int parent_segment4;
  struct geo_segment_int child_segment1;
  struct geo_segment_int child_segment2;
  struct geo_segment_int child_segment3;
  struct geo_segment_int child_segment4;
  struct geo_segment_int *parent_segments[4];
  struct geo_segment_int *child_segments[4];
  struct geo_geometry_int parent;
  struct geo_geometry_int child;
  size_t parent_segments_count = 4;
  size_t child_segments_count = 4;
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
  result = geo_geometry_in_geometry_int(&parent, &child, strict, &is_inside);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_geometry_in_geometry_int_returns_geo_err_null_pointer_when_child_geometry_ith_segment_end_point_is_null(void) {
  bool is_inside = false;
  bool strict = true;
  enum geo_result result = GEO_SUCCESS;
  struct geo_point_int parent_vertex1 = { 0, 0 };
  struct geo_point_int parent_vertex2 = { 5, 0 };
  struct geo_point_int parent_vertex3 = { 5, 5 };
  struct geo_point_int parent_vertex4 = { 0, 5 };
  struct geo_point_int child_vertex1 = { 1, 1 };
  struct geo_point_int child_vertex2 = { 3, 1 };
  struct geo_point_int child_vertex3 = { 3, 3 };
  struct geo_point_int child_vertex4 = { 1, 3 };
  struct geo_segment_int parent_segment1;
  struct geo_segment_int parent_segment2;
  struct geo_segment_int parent_segment3;
  struct geo_segment_int parent_segment4;
  struct geo_segment_int child_segment1;
  struct geo_segment_int child_segment2;
  struct geo_segment_int child_segment3;
  struct geo_segment_int child_segment4;
  struct geo_segment_int *parent_segments[4];
  struct geo_segment_int *child_segments[4];
  struct geo_geometry_int parent;
  struct geo_geometry_int child;
  size_t parent_segments_count = 4;
  size_t child_segments_count = 4;
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
  result = geo_geometry_in_geometry_int(&parent, &child, strict, &is_inside);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_geometry_in_geometry_int_returns_geo_err_too_small_when_parent_geometry_segments_count_less_than_3(void) {
  bool is_inside = false;
  bool strict = true;
  enum geo_result result = GEO_SUCCESS;
  struct geo_point_int parent_vertex1 = { 0, 0 };
  struct geo_point_int parent_vertex2 = { 5, 0 };
  struct geo_point_int parent_vertex3 = { 5, 5 };
  struct geo_point_int parent_vertex4 = { 0, 5 };
  struct geo_point_int child_vertex1 = { 1, 1 };
  struct geo_point_int child_vertex2 = { 3, 1 };
  struct geo_point_int child_vertex3 = { 3, 3 };
  struct geo_point_int child_vertex4 = { 1, 3 };
  struct geo_segment_int parent_segment1;
  struct geo_segment_int parent_segment2;
  struct geo_segment_int parent_segment3;
  struct geo_segment_int parent_segment4;
  struct geo_segment_int child_segment1;
  struct geo_segment_int child_segment2;
  struct geo_segment_int child_segment3;
  struct geo_segment_int child_segment4;
  struct geo_segment_int *parent_segments[4];
  struct geo_segment_int *child_segments[4];
  struct geo_geometry_int parent;
  struct geo_geometry_int child;
  size_t parent_segments_count = 2;
  size_t child_segments_count = 4;
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
  result = geo_geometry_in_geometry_int(&parent, &child, strict, &is_inside);
  assert(result == GEO_ERR_TOO_SMALL);
}

void geo_geometry_in_geometry_int_returns_geo_err_too_small_when_child_geometry_segments_count_less_than_3(void) {
  bool is_inside = false;
  bool strict = true;
  enum geo_result result = GEO_SUCCESS;
  struct geo_point_int parent_vertex1 = { 0, 0 };
  struct geo_point_int parent_vertex2 = { 5, 0 };
  struct geo_point_int parent_vertex3 = { 5, 5 };
  struct geo_point_int parent_vertex4 = { 0, 5 };
  struct geo_point_int child_vertex1 = { 1, 1 };
  struct geo_point_int child_vertex2 = { 3, 1 };
  struct geo_point_int child_vertex3 = { 3, 3 };
  struct geo_point_int child_vertex4 = { 1, 3 };
  struct geo_segment_int parent_segment1;
  struct geo_segment_int parent_segment2;
  struct geo_segment_int parent_segment3;
  struct geo_segment_int parent_segment4;
  struct geo_segment_int child_segment1;
  struct geo_segment_int child_segment2;
  struct geo_segment_int child_segment3;
  struct geo_segment_int child_segment4;
  struct geo_segment_int *parent_segments[4];
  struct geo_segment_int *child_segments[4];
  struct geo_geometry_int parent;
  struct geo_geometry_int child;
  size_t parent_segments_count = 4;
  size_t child_segments_count = 2;
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
  result = geo_geometry_in_geometry_int(&parent, &child, strict, &is_inside);
  assert(result == GEO_ERR_TOO_SMALL);
}

void geo_geometry_in_geometry_int_returns_geo_success_and_is_inside_set_to_true_when_all_points_in_child_geometry_are_inside_parent_geometry(void) {
  bool is_inside = false;
  bool strict = true;
  enum geo_result result = GEO_SUCCESS;
  struct geo_point_int parent_vertex1 = { 0, 0 };
  struct geo_point_int parent_vertex2 = { 5, 0 };
  struct geo_point_int parent_vertex3 = { 5, 5 };
  struct geo_point_int parent_vertex4 = { 0, 5 };
  struct geo_point_int child_vertex1 = { 1, 1 };
  struct geo_point_int child_vertex2 = { 3, 1 };
  struct geo_point_int child_vertex3 = { 3, 3 };
  struct geo_point_int child_vertex4 = { 1, 3 };
  struct geo_segment_int parent_segment1;
  struct geo_segment_int parent_segment2;
  struct geo_segment_int parent_segment3;
  struct geo_segment_int parent_segment4;
  struct geo_segment_int child_segment1;
  struct geo_segment_int child_segment2;
  struct geo_segment_int child_segment3;
  struct geo_segment_int child_segment4;
  struct geo_segment_int *parent_segments[4];
  struct geo_segment_int *child_segments[4];
  struct geo_geometry_int parent;
  struct geo_geometry_int child;
  size_t parent_segments_count = 4;
  size_t child_segments_count = 4;
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
  result = geo_geometry_in_geometry_int(&parent, &child, strict, &is_inside);
  assert(result == GEO_SUCCESS);
  assert(is_inside == true);
}

void geo_geometry_in_geometry_int_returns_geo_success_and_is_inside_set_to_false_when_any_points_in_child_geometry_are_outside_parent_geometry(void) {
  bool is_inside = false;
  bool strict = true;
  enum geo_result result = GEO_SUCCESS;
  struct geo_point_int parent_vertex1 = { 0, 0 };
  struct geo_point_int parent_vertex2 = { 5, 0 };
  struct geo_point_int parent_vertex3 = { 5, 5 };
  struct geo_point_int parent_vertex4 = { 0, 5 };
  struct geo_point_int child_vertex1 = { 1, 1 };
  struct geo_point_int child_vertex2 = { 3, 1 };
  struct geo_point_int child_vertex3 = { 6, 3 }; /* outside parent */
  struct geo_point_int child_vertex4 = { 1, 3 };
  struct geo_segment_int parent_segment1;
  struct geo_segment_int parent_segment2;
  struct geo_segment_int parent_segment3;
  struct geo_segment_int parent_segment4;
  struct geo_segment_int child_segment1;
  struct geo_segment_int child_segment2;
  struct geo_segment_int child_segment3;
  struct geo_segment_int child_segment4;
  struct geo_segment_int *parent_segments[4];
  struct geo_segment_int *child_segments[4];
  struct geo_geometry_int parent;
  struct geo_geometry_int child;
  size_t parent_segments_count = 4;
  size_t child_segments_count = 4;
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
  result = geo_geometry_in_geometry_int(&parent, &child, strict, &is_inside);
  assert(result == GEO_SUCCESS);
  assert(is_inside == false);
}

void geo_geometry_in_geometry_int_returns_geo_success_and_is_inside_set_to_false_when_any_points_in_child_geometry_are_on_segment_of_parent_geometry_and_strict_is_true(void) {
  bool is_inside = false;
  bool strict = true;
  enum geo_result result = GEO_SUCCESS;
  struct geo_point_int parent_vertex1 = { 0, 0 };
  struct geo_point_int parent_vertex2 = { 5, 0 };
  struct geo_point_int parent_vertex3 = { 5, 5 };
  struct geo_point_int parent_vertex4 = { 0, 5 };
  struct geo_point_int child_vertex1 = { 1, 1 };
  struct geo_point_int child_vertex2 = { 3, 1 };
  struct geo_point_int child_vertex3 = { 5, 3 }; /* on parent geometry segment */
  struct geo_point_int child_vertex4 = { 1, 3 };
  struct geo_segment_int parent_segment1;
  struct geo_segment_int parent_segment2;
  struct geo_segment_int parent_segment3;
  struct geo_segment_int parent_segment4;
  struct geo_segment_int child_segment1;
  struct geo_segment_int child_segment2;
  struct geo_segment_int child_segment3;
  struct geo_segment_int child_segment4;
  struct geo_segment_int *parent_segments[4];
  struct geo_segment_int *child_segments[4];
  struct geo_geometry_int parent;
  struct geo_geometry_int child;
  size_t parent_segments_count = 4;
  size_t child_segments_count = 4;
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
  result = geo_geometry_in_geometry_int(&parent, &child, strict, &is_inside);
  assert(result == GEO_SUCCESS);
  assert(is_inside == false);
}

void geo_geometry_in_geometry_int_returns_geo_success_and_is_inside_set_to_true_when_any_points_in_child_geometry_are_on_segment_of_parent_geometry_and_strict_is_false(void) {
  bool is_inside = false;
  bool strict = false;
  enum geo_result result = GEO_SUCCESS;
  struct geo_point_int parent_vertex1 = { 0, 0 };
  struct geo_point_int parent_vertex2 = { 5, 0 };
  struct geo_point_int parent_vertex3 = { 5, 5 };
  struct geo_point_int parent_vertex4 = { 0, 5 };
  struct geo_point_int child_vertex1 = { 1, 1 };
  struct geo_point_int child_vertex2 = { 3, 1 };
  struct geo_point_int child_vertex3 = { 5, 3 }; /* on parent geometry segment */
  struct geo_point_int child_vertex4 = { 1, 3 };
  struct geo_segment_int parent_segment1;
  struct geo_segment_int parent_segment2;
  struct geo_segment_int parent_segment3;
  struct geo_segment_int parent_segment4;
  struct geo_segment_int child_segment1;
  struct geo_segment_int child_segment2;
  struct geo_segment_int child_segment3;
  struct geo_segment_int child_segment4;
  struct geo_segment_int *parent_segments[4];
  struct geo_segment_int *child_segments[4];
  struct geo_geometry_int parent;
  struct geo_geometry_int child;
  size_t parent_segments_count = 4;
  size_t child_segments_count = 4;
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
  result = geo_geometry_in_geometry_int(&parent, &child, strict, &is_inside);
  assert(result == GEO_SUCCESS);
  assert(is_inside == true);
}

/*----------------------------------
 * geo_convex_hull_int tests
*----------------------------------
 */
void geo_convex_hull_int_returns_geo_err_null_pointer_when_points_array_is_null(void) {
  size_t count = 5;
  struct geo_point_int *hull[5];
  size_t hull_size = 0;
  enum geo_result result = geo_convex_hull_int(NULL, hull, count, &hull_size);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_convex_hull_int_returns_geo_err_null_pointer_when_hull_array_is_null(void) {
  size_t count = 3;
  size_t hull_size = 0;
  struct geo_point_int *points[3];
  struct geo_point_int point1 = { 0, 0 };
  struct geo_point_int point2 = { 2, 0 };
  struct geo_point_int point3 = { 1, 1 };
  points[0] = &point1;
  points[1] = &point2;
  points[2] = &point3;

  enum geo_result result = geo_convex_hull_int(points, NULL, count, &hull_size);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_convex_hull_int_returns_geo_err_too_small_when_size_is_less_than_3(void) {
  size_t count = 2;
  size_t hull_size = 0;
  struct geo_point_int *hull[2];
  struct geo_point_int *points[2];
  struct geo_point_int point1 = { 0, 0 };
  struct geo_point_int point2 = { 1, 0 };
  points[0] = &point1;
  points[1] = &point2;

  enum geo_result result = geo_convex_hull_int(points, hull, count, &hull_size);
  assert(result == GEO_ERR_TOO_SMALL);
}

void geo_convex_hull_int_returns_geo_err_null_pointer_when_any_point_in_points_is_null(void) {
  size_t count = 3;
  size_t hull_size = 0;
  struct geo_point_int *hull[3];
  struct geo_point_int *points[3];
  struct geo_point_int point1 = { 0, 0 };
  struct geo_point_int point3 = { 1, 1 };
  points[0] = &point1;
  points[1] = NULL;
  points[2] = &point3;

  enum geo_result result = geo_convex_hull_int(points, hull, count, &hull_size);
  assert(result == GEO_ERR_NULL_POINTER);
}

void geo_convex_hull_int_returns_geo_success_and_sets_hull_size_to_3_and_hull_has_points_in_order_when_given_points_for_triangle(void) {
  size_t count = 3;
  size_t hull_size = 0;
  struct geo_point_int *hull[3];
  struct geo_point_int *points[3];
  struct geo_point_int point1 = { 0, 0 };
  struct geo_point_int point2 = { 1, 0 };
  struct geo_point_int point3 = { 1, 1 };
  points[0] = &point1;
  points[1] = &point3;
  points[2] = &point2;

  enum geo_result result = geo_convex_hull_int(points, hull, count, &hull_size);
  assert(result == GEO_SUCCESS);
  assert(hull_size == 3);
  assert(hull[0] == &point1);
  assert(hull[1] == &point2);
  assert(hull[2] == &point3);
}

void geo_convex_hull_int_returns_geo_success_and_sets_hull_size_to_5_and_hull_has_points_in_ccw_order_when_given_point_cloud(void) {
  size_t count = 7;
  size_t hull_size = 0;
  struct geo_point_int *hull[7];
  struct geo_point_int *points[7];
  struct geo_point_int point1 = { 1, 1 };
  struct geo_point_int point2 = { 7, 0 };
  struct geo_point_int point3 = { 4, 2 };
  struct geo_point_int point4 = { 6, 4 };
  struct geo_point_int point5 = { 3, 5 };
  struct geo_point_int point6 = { 5, 6 };
  struct geo_point_int point7 = { 2, 7 };

  points[0] = &point1;
  points[1] = &point2;
  points[2] = &point3;
  points[3] = &point4;
  points[4] = &point5;
  points[5] = &point6;
  points[6] = &point7;
  enum geo_result result = geo_convex_hull_int(points, hull, count, &hull_size);

  assert(result == GEO_SUCCESS);
  assert(hull_size == 5);
  assert(hull[0] == &point2);
  assert(hull[1] == &point4);
  assert(hull[2] == &point6);
  assert(hull[3] == &point7);
  assert(hull[4] == &point1);
}

void geo_convex_hull_int_returns_geo_success_and_sets_hull_size_to_4_and_hull_has_points_in_ccw_order_using_furthest_colinear_point_when_given_point_cloud_with_colinear_points(void) {
  size_t count = 6;
  size_t hull_size = 0;
  struct geo_point_int *hull[6];
  struct geo_point_int *points[6];
  struct geo_point_int point1 = { 0, 0 };
  struct geo_point_int point2 = { 3, 0 };
  struct geo_point_int point3 = { 3, 1 };
  struct geo_point_int point4 = { 3, 2 };
  struct geo_point_int point5 = { 3, 3 };
  struct geo_point_int point6 = { 0, 3 };
  points[0] = &point1;
  points[1] = &point6;
  points[2] = &point3;
  points[3] = &point2;
  points[4] = &point5;
  points[5] = &point4;

  enum geo_result result = geo_convex_hull_int(points, hull, count, &hull_size);
  assert(result == GEO_SUCCESS);
  assert(hull_size == 4);
  assert(hull[0] == &point1);
  assert(hull[1] == &point2);
  assert(hull[2] == &point5);
  assert(hull[3] == &point6);
}

void geo_convex_hull_int_with_30_points_returns_geo_success_and_sets_hull_size_to_12_and_hull_has_points_in_ccw_order(void) {
  size_t count = 30;
  size_t hull_size = 0;
  struct geo_point_int *hull[30];
  struct geo_point_int *points[30];
  struct geo_point_int point1 = { -100, 100 };
  struct geo_point_int point2 = { -125, 125 };
  struct geo_point_int point3 = { -150, 125 };
  struct geo_point_int point4 = { -175, 100 };
  struct geo_point_int point5 = { -200, 50 };
  struct geo_point_int point6 = { -200, -50 };
  struct geo_point_int point7 = { -175, -100 };
  struct geo_point_int point8 = { -150, -125 };
  struct geo_point_int point9 = { -125, -125 };
  struct geo_point_int point10 = { -100, -100 };
  struct geo_point_int point11 = { 75, 150 };
  struct geo_point_int point12 = { 25, 200 };
  struct geo_point_int point13 = { -25, 200 };
  struct geo_point_int point14 = { -75, 125 };
  struct geo_point_int point15 = { -25, 50 };
  struct geo_point_int point16 = { 25, -50 };
  struct geo_point_int point17 = { 75, -125 };
  struct geo_point_int point18 = { 25, -200 };
  struct geo_point_int point19 = { -25, -200 };
  struct geo_point_int point20 = { -75, -150 };
  struct geo_point_int point21 = { 200, 125 };
  struct geo_point_int point22 = { 150, 125 };
  struct geo_point_int point23 = { 100, 125 };
  struct geo_point_int point24 = { 100, 50 };
  struct geo_point_int point25 = { 100, 0 };
  struct geo_point_int point26 = { 150, 0 };
  struct geo_point_int point27 = { 100, -50 };
  struct geo_point_int point28 = { 100, -125 };
  struct geo_point_int point29 = { 150, -125 };
  struct geo_point_int point30 = { 200, -125 };
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

  enum geo_result result = geo_convex_hull_int(points, hull, count, &hull_size);
  assert(result == GEO_SUCCESS);
  assert(hull_size == 12);
}

int main(void) {
  /* geo_points_equal_int tests */
  geo_points_equal_int_returns_geo_err_null_pointer_result_code_when_lhs_is_null();
  geo_points_equal_int_returns_geo_err_null_pointer_result_code_when_rhs_is_null();
  geo_points_equal_int_returns_geo_success_and_is_equal_set_to_1_when_lhs_and_rhs_are_exactly_equal();
  geo_points_equal_int_returns_geo_success_and_is_equal_set_to_0_when_lhs_neither_x_or_y_and_rhs_x_or_y_are_within_epsilon();

  /* geo_segments_intersect_int tests */
  geo_segments_intersect_int_returns_geo_err_null_pointer_result_code_when_segment_1_is_null();
  geo_segments_intersect_int_returns_geo_err_null_pointer_result_code_when_segment_2_is_null();
  geo_segments_intersect_int_returns_geo_err_null_pointer_result_code_when_segment_1_start_is_null();
  geo_segments_intersect_int_returns_geo_err_null_pointer_result_code_when_segment_1_end_is_null();
  geo_segments_intersect_int_returns_geo_err_null_pointer_result_code_when_segment_2_start_is_null();
  geo_segments_intersect_int_returns_geo_err_null_pointer_result_code_when_segment_2_end_is_null();
  geo_segments_intersect_int_returns_geo_success_and_intersect_count_is_0_when_segments_are_parallel();
  geo_segments_intersect_int_returns_geo_success_and_intersect_count_is_0_when_segments_are_colinear_but_dont_intersect();
  geo_segments_intersect_int_returns_geo_success_and_intersect_count_is_0_when_segments_dont_intersect();
  geo_segments_intersect_int_returns_geo_success_and_intersect_count_is_1_when_segments_properly_intersect();
  geo_segments_intersect_int_returns_geo_success_and_intersect_count_is_2_when_segment_1_end_is_equal_to_segment_2_start();
  geo_segments_intersect_int_returns_geo_success_and_intersect_count_is_2_when_one_segment_is_section_of_other_segment();
  geo_segments_intersect_int_returns_geo_success_and_intersect_count_is_4_when_segment_1_is_the_same_segment_as_segment_2();

  /* geo_geometry_is_closed_int tests */
  geo_geometry_is_closed_int_returns_geo_err_null_pointer_when_geometry_is_null();
  geo_geometry_is_closed_int_returns_geo_err_null_pointer_when_geometry_segments_is_null();
  geo_geometry_is_closed_int_returns_geo_err_null_pointer_when_geometry_segment_start_is_null();
  geo_geometry_is_closed_int_returns_geo_err_null_pointer_when_geometry_segment_end_is_null();
  geo_geometry_is_closed_int_returns_geo_err_too_small_when_geometry_segment_count_less_than_3();
  geo_geometry_is_closed_int_returns_geo_success_and_is_closed_is_false_when_nth_segments_end_doesnt_equal_n_plus_1_segment_start();
  geo_geometry_is_closed_int_returns_geo_success_and_is_closed_is_true_when_nth_segments_end_equals_n_plus_1_segments_start();

  /* geo_geometry_is_simple_int tests */
  geo_geometry_is_simple_int_returns_geo_err_null_pointer_when_geometry_is_null();
  geo_geometry_is_simple_int_returns_geo_err_null_pointer_when_geometry_segments_is_null();
  geo_geometry_is_simple_int_returns_geo_err_null_pointer_when_geometry_segments_ith_start_is_null();
  geo_geometry_is_simple_int_returns_geo_err_null_pointer_when_geometry_segments_ith_end_is_null();
  geo_geometry_is_simple_int_returns_geo_err_too_small_when_geometry_segments_count_less_than_3();
  geo_geometry_is_simple_int_returns_geo_success_and_is_simple_is_false_when_any_segments_intersect();
  geo_geometry_is_simple_int_returns_geo_success_and_is_simple_is_true_when_no_segments_intersect();

  /* geo_point_in_geometry_int tests */
  geo_point_in_geometry_int_returns_geo_err_null_pointer_when_point_is_null();
  geo_point_in_geometry_int_returns_geo_err_null_pointer_when_geometry_is_null();
  geo_point_in_geometry_int_returns_geo_err_null_pointer_when_geometry_segments_is_null();
  geo_point_in_geometry_int_returns_geo_err_null_pointer_when_geometry_segments_ith_start_is_null();
  geo_point_in_geometry_int_returns_geo_err_null_pointer_when_geometry_segments_ith_end_is_null();
  geo_point_in_geometry_int_returns_geo_err_too_small_when_geometry_segments_count_is_less_than_3();
  geo_poiny_in_geometry_returns_geo_success_and_is_inside_set_to_false_when_point_on_geometry_segment_and_strict_is_true();
  geo_poiny_in_geometry_returns_geo_success_and_is_inside_set_to_true_when_point_on_geometry_segment_and_strict_is_false();
  geo_poiny_in_geometry_returns_geo_success_and_is_inside_set_to_false_when_point_is_to_the_left_of_the_geometry_and_colinear_with_horizontal_segment();
  geo_poiny_in_geometry_returns_geo_success_and_is_inside_set_to_false_when_point_is_to_the_right_of_the_geometry_and_colinear_with_horizontal_segment();
  geo_poiny_in_geometry_returns_geo_success_and_is_inside_set_to_false_when_point_is_above_of_the_geometry_and_colinear_with_vertical_segment();
  geo_poiny_in_geometry_returns_geo_success_and_is_inside_set_to_false_when_point_is_below_of_the_geometry_and_colinear_with_vertical_segment();


  /* geo_geometry_in_geometry_int tests */
  geo_geometry_in_geometry_int_returns_geo_err_null_pointer_when_parent_geometry_is_null();
  geo_geometry_in_geometry_int_returns_geo_err_null_pointer_when_parent_geometry_segments_is_null();
  geo_geometry_in_geometry_int_returns_geo_err_null_pointer_when_parent_geometry_ith_segment_is_null();
  geo_geometry_in_geometry_int_returns_geo_err_null_pointer_when_parent_geometry_ith_segment_start_point_is_null();
  geo_geometry_in_geometry_int_returns_geo_err_null_pointer_when_parent_geometry_ith_segment_end_point_is_null();
  geo_geometry_in_geometry_int_returns_geo_err_null_pointer_when_child_geometry_is_null();
  geo_geometry_in_geometry_int_returns_geo_err_null_pointer_when_child_geometry_segments_is_null();
  geo_geometry_in_geometry_int_returns_geo_err_null_pointer_when_child_geometry_ith_segment_is_null();
  geo_geometry_in_geometry_int_returns_geo_err_null_pointer_when_child_geometry_ith_segment_start_point_is_null();
  geo_geometry_in_geometry_int_returns_geo_err_null_pointer_when_child_geometry_ith_segment_end_point_is_null();
  geo_geometry_in_geometry_int_returns_geo_err_too_small_when_parent_geometry_segments_count_less_than_3();
  geo_geometry_in_geometry_int_returns_geo_err_too_small_when_child_geometry_segments_count_less_than_3();
  geo_geometry_in_geometry_int_returns_geo_success_and_is_inside_set_to_true_when_all_points_in_child_geometry_are_inside_parent_geometry();
  geo_geometry_in_geometry_int_returns_geo_success_and_is_inside_set_to_false_when_any_points_in_child_geometry_are_outside_parent_geometry();
  geo_geometry_in_geometry_int_returns_geo_success_and_is_inside_set_to_false_when_any_points_in_child_geometry_are_on_segment_of_parent_geometry_and_strict_is_true();
  geo_geometry_in_geometry_int_returns_geo_success_and_is_inside_set_to_true_when_any_points_in_child_geometry_are_on_segment_of_parent_geometry_and_strict_is_false();

  /* geo_convex_hull_int tests */
  geo_convex_hull_int_returns_geo_err_null_pointer_when_points_array_is_null();
  geo_convex_hull_int_returns_geo_err_null_pointer_when_hull_array_is_null();
  geo_convex_hull_int_returns_geo_err_too_small_when_size_is_less_than_3();
  geo_convex_hull_int_returns_geo_err_null_pointer_when_any_point_in_points_is_null();
  geo_convex_hull_int_returns_geo_success_and_sets_hull_size_to_3_and_hull_has_points_in_order_when_given_points_for_triangle();
  geo_convex_hull_int_returns_geo_success_and_sets_hull_size_to_5_and_hull_has_points_in_ccw_order_when_given_point_cloud();
  geo_convex_hull_int_returns_geo_success_and_sets_hull_size_to_4_and_hull_has_points_in_ccw_order_using_furthest_colinear_point_when_given_point_cloud_with_colinear_points();
  geo_convex_hull_int_with_30_points_returns_geo_success_and_sets_hull_size_to_12_and_hull_has_points_in_ccw_order();
  printf("All int tests pass.\n");
  return 0;
}
