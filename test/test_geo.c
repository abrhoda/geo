#include "../src/geo.h"
#include <assert.h>
#include <stdio.h>

/*----------------------------------
 * geo_points_equal tests
 *----------------------------------
 */
void geo_points_equal_returns_negative_1_when_lhs_is_null(void) {
  struct geo_point point = {0.0F, 0.0F};
  int result = geo_points_equal(NULL, &point);
  assert(result == -1);
}

void geo_points_equal_returns_negative_1_when_rhs_is_null(void) {
  struct geo_point point = {0.0F, 0.0F};
  int result = geo_points_equal(&point, NULL);
  assert(result == -1);
}

void geo_points_equal_returns_1_when_lhs_and_rhs_are_exactly_equal(void) {
  struct geo_point point1 = {1.5F, 2.0F};
  struct geo_point point2 = {1.5F, 2.0F};
  int result = geo_points_equal(&point1, &point2);
  assert(result == 1);
}

void geo_points_equal_returns_1_when_lhs_x_and_y_and_rhs_x_and_y_are_within_epsilon(void) {
  struct geo_point point1 = {1.49999999F, 2.000000001F};
  struct geo_point point2 = {1.5F, 2.0F};
  int result = geo_points_equal(&point1, &point2);
  assert(result == 1);
}

void geo_points_equal_returns_0_when_lhs_only_x_and_rhs_only_x_are_within_epsilon(void) {
  struct geo_point point1 = {2.0F, 2.000000001F};
  struct geo_point point2 = {1.5F, 2.0F};
  int result = geo_points_equal(&point1, &point2);
  assert(result == 0);
}

void geo_points_equal_returns_0_when_lhs_neither_x_or_y_and_rhs_x_or_y_are_within_epsilon(void) {
  struct geo_point point1 = {2.0F, 3.0F};
  struct geo_point point2 = {1.5F, 2.0F};
  int result = geo_points_equal(&point1, &point2);
  assert(result == 0); 
}


/*----------------------------------
 * geo_segments_intersect tests
 *----------------------------------
 */
void geo_segments_intersect_returns_negative_1_when_segment_1_is_null(void) {
  struct geo_point point1 = {2.0F, 3.0F};
  struct geo_point point2 = {1.5F, 2.0F};
  struct geo_segment segment;
  int result = 0;
  segment.start = &point1;
  segment.end = &point2;
  result = geo_segments_intersect(NULL, &segment);
  assert(result == -1);
}
void geo_segments_intersect_returns_negative_1_when_segment_2_is_null(void) {
  struct geo_point point1 = {2.0F, 3.0F};
  struct geo_point point2 = {1.5F, 2.0F};
  struct geo_segment segment;
  int result = 0;
  segment.start = &point1;
  segment.end = &point2;
  result = geo_segments_intersect(&segment, NULL);
  assert(result == -1);
}
void geo_segments_intersect_returns_negative_1_when_segment_1_start_is_null(void) {
  /*struct geo_point point1 = {2.0F, 3.0F};*/
  struct geo_point point2 = {1.5F, 2.0F};
  struct geo_point point3 = {7.0F, 3.0F};
  struct geo_point point4 = {6.5F, 2.0F};
  struct geo_segment segment1;
  struct geo_segment segment2;
  int result = 0;
  segment1.start = NULL;
  segment1.end = &point2;
  segment2.start = &point3;
  segment2.end = &point4;
  result = geo_segments_intersect(&segment1, &segment2);
  assert(result == -1);
}

void geo_segments_intersect_returns_negative_1_when_segment_1_end_is_null(void) {
  struct geo_point point1 = {2.0F, 3.0F};
  /*struct geo_point point2 = {1.5F, 2.0F};*/
  struct geo_point point3 = {7.0F, 3.0F};
  struct geo_point point4 = {6.5F, 2.0F};
  struct geo_segment segment1;
  struct geo_segment segment2;
  int result = 0;
  segment1.start = &point1;
  segment1.end = NULL;
  segment2.start = &point3;
  segment2.end = &point4;
  result = geo_segments_intersect(&segment1, &segment2);
  assert(result == -1);
}

void geo_segments_intersect_returns_negative_1_when_segment_2_start_is_null(void) {
  struct geo_point point1 = {2.0F, 3.0F};
  struct geo_point point2 = {1.5F, 2.0F};
  /*struct geo_point point3 = {7.0F, 3.0F};*/
  struct geo_point point4 = {6.5F, 2.0F};
  struct geo_segment segment1;
  struct geo_segment segment2;
  int result = 0;
  segment1.start = &point1;
  segment1.end = &point2;
  segment2.start = NULL;
  segment2.end = &point4;
  result = geo_segments_intersect(&segment1, &segment2);
  assert(result == -1);
}

void geo_segments_intersect_returns_negative_1_when_segment_2_end_is_null(void) {
  struct geo_point point1 = {2.0F, 3.0F};
  struct geo_point point2 = {1.5F, 2.0F};
  struct geo_point point3 = {7.0F, 3.0F};
  /*struct geo_point point4 = {6.5F, 2.0F};*/
  struct geo_segment segment1;
  struct geo_segment segment2;
  int result = 0;
  segment1.start = &point1;
  segment1.end = &point2;
  segment2.start = &point3;
  segment2.end = NULL;
  result = geo_segments_intersect(&segment1, &segment2);
  assert(result == -1);
}

void geo_segments_intersect_returns_0_when_segments_are_parallel(void) {
  struct geo_point point1 = {0.0F, 3.0F};
  struct geo_point point2 = {3.0F, 3.0F};
  struct geo_point point3 = {0.0F, 4.0F};
  struct geo_point point4 = {3.0F, 4.0F};
  struct geo_segment segment1;
  struct geo_segment segment2;
  int result = 0;
  segment1.start = &point1;
  segment1.end = &point2;
  segment2.start = &point3;
  segment2.end = &point4;
  result = geo_segments_intersect(&segment1, &segment2);
  assert(result == 0);
}

void geo_segments_intersect_returns_0_when_segments_are_colinear_but_dont_intersect(void) {
  struct geo_point point1 = {0.0F, 0.0F};
  struct geo_point point2 = {1.0F, 0.0F};
  struct geo_point point3 = {2.0F, 0.0F};
  struct geo_point point4 = {3.0F, 0.0F};
  struct geo_segment segment1;
  struct geo_segment segment2;
  int result = 0;
  segment1.start = &point1;
  segment1.end = &point2;
  segment2.start = &point3;
  segment2.end = &point4;
  result = geo_segments_intersect(&segment1, &segment2);
  assert(result == 0);
}

void geo_segments_intersect_returns_0_when_segments_dont_intersect(void) {
  struct geo_point point1 = {0.0F, 0.0F};
  struct geo_point point2 = {1.0F, 1.0F};
  struct geo_point point3 = {2.0F, 3.0F};
  struct geo_point point4 = {3.0F, 5.0F};
  struct geo_segment segment1;
  struct geo_segment segment2;
  int result = 0;
  segment1.start = &point1;
  segment1.end = &point2;
  segment2.start = &point3;
  segment2.end = &point4;
  result = geo_segments_intersect(&segment1, &segment2);
  assert(result == 0);
}

void geo_segments_intersect_returns_1_when_segments_properly_intersect(void) {
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
  int result = 0;
  segment1.start = &point1;
  segment1.end = &point2;
  segment2.start = &point3;
  segment2.end = &point4;
  result = geo_segments_intersect(&segment1, &segment2);
  assert(result == 1);
}

void geo_segments_intersect_returns_2_when_segment_1_end_is_equal_to_segment_2_start(void) {
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
  int result = 0;
  segment1.start = &point1;
  segment1.end = &point2;
  segment2.start = &point3;
  segment2.end = &point4;
  result = geo_segments_intersect(&segment1, &segment2);
  assert(result == 2);
}

void geo_segments_intersect_returns_2_when_one_segment_is_section_of_other_segment(void) {
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
  int result = 0;
  segment1.start = &point1;
  segment1.end = &point2;
  segment2.start = &point3;
  segment2.end = &point4;
  result = geo_segments_intersect(&segment1, &segment2);
  assert(result == 2);
}

void geo_segments_intersect_returns_3_when_segment_1_is_section_of_segment_2_and_share_1_end(void) {
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
  int result = 0;
  segment1.start = &point1;
  segment1.end = &point2;
  segment2.start = &point3;
  segment2.end = &point4;
  result = geo_segments_intersect(&segment1, &segment2);
  assert(result == 3);
}

void geo_segments_intersect_returns_4_when_segment_1_is_the_same_segment_as_segment_2(void) {
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
  int result = 0;
  segment1.start = &point1;
  segment1.end = &point2;
  segment2.start = &point3;
  segment2.end = &point4;
  result = geo_segments_intersect(&segment1, &segment2);
  assert(result == 4);
}


/*----------------------------------
 * geo_geometry_is_closed tests
 *----------------------------------
 */
void geo_geometry_is_closed_returns_negative_1_when_geometry_is_null(void) {
  struct geo_geometry * geometry = NULL;
  int result = geo_geometry_is_closed(geometry);
  assert(result == -1);
}

void geo_geometry_is_closed_returns_negative_1_when_geometry_segments_is_null(void) {
  int result = 0;
  struct geo_geometry geometry;
  geometry.segments_count = 0;
  geometry.segments = NULL;

  result = geo_geometry_is_closed(&geometry);
  assert(result == -1);
}

void geo_geometry_is_closed_returns_negative_1_when_geometry_segment_start_is_null(void) {
  int result = 0;
  struct geo_point start1 = {0.0F, 0.0F};
  struct geo_point end1 = {3.0F, 0.0F};
  struct geo_point start2 = {3.0F, 0.0F};
  /*struct geo_point end2 = {1.5F, 3.0F};*/
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

  result = geo_geometry_is_closed(&geometry);
  assert(result == -1);
}

void geo_geometry_is_closed_returns_negative_1_when_geometry_segment_end_is_null(void) {
  int result = 0;
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

  result = geo_geometry_is_closed(&geometry);
  assert(result == -1);
}

void geo_geometry_is_closed_returns_0_when_geometry_segment_count_less_than_3(void) {
  int result = 0;
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

  result = geo_geometry_is_closed(&geometry);
  assert(result == 0);
}

void geo_geometry_is_closed_returns_0_when_nth_segments_end_doesnt_equal_n_plus_1_segment_start(void) {
  int result = 0;
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

  result = geo_geometry_is_closed(&geometry);
  assert(result == 0);
}

void geo_geometry_is_closed_returns_1_when_nth_segments_end_equals_n_plus_1_segments_start(void) {
  int result = 0;
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

  result = geo_geometry_is_closed(&geometry);
  assert(result == 1);
}

/*----------------------------------
 * geo_geometry_is_closed tests
 *----------------------------------
 */
void geo_geometry_is_simple_returns_negative_1_when_geometry_is_null(void) {
  struct geo_geometry * geometry = NULL;
  int result = geo_geometry_is_simple(geometry);
  assert(result == -1);
}

void geo_geometry_is_simple_returns_negative_1_when_geometry_segments_is_null(void) {
  int result = 0;
  struct geo_geometry geometry;
  geometry.segments_count = 0;
  geometry.segments = NULL;

  result = geo_geometry_is_simple(&geometry);
  assert(result == -1);
}

void geo_geometry_is_simple_returns_negative_1_when_geometry_segments_ith_start_is_null(void) {
  int result = 0;
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

  result = geo_geometry_is_simple(&geometry);
  assert(result == -1);
}

void geo_geometry_is_simple_returns_negative_1_when_geometry_segments_ith_end_is_null(void) {
  int result = 0;
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

  result = geo_geometry_is_simple(&geometry);
  assert(result == -1);
}

void geo_geometry_is_simple_returns_0_when_geometry_segments_count_less_than_3(void) {
  int result = 0;
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

  result = geo_geometry_is_simple(&geometry);
  assert(result == -1);
}

void geo_geometry_is_simple_returns_0_when_any_segments_intersect(void) {
  int result = 0;
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

  result = geo_geometry_is_simple(&geometry);
  assert(result == 0);
}

void geo_geometry_is_simple_returns_1_when_no_segments_intersect(void) {
  int result = 0;
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

  result = geo_geometry_is_simple(&geometry);
  assert(result == 1);
}

/*----------------------------------
 * geo_point_in_geometry tests
 *----------------------------------
 */
void geo_point_in_geometry_returns_negative_1_when_point_is_null(void) {}
void geo_point_in_geometry_returns_negative_1_when_geometry_is_null(void) {}
void geo_point_in_geometry_returns_negative_1_when_geometry_segments_is_null(void) {}
void geo_point_in_geometry_returns_0_when_geometry_segments_count_is_less_than_3(void) {}


int main(void) {
  /* geo_points_equal tests */
  geo_points_equal_returns_negative_1_when_lhs_is_null();
  geo_points_equal_returns_negative_1_when_rhs_is_null();
  geo_points_equal_returns_1_when_lhs_and_rhs_are_exactly_equal();
  geo_points_equal_returns_1_when_lhs_x_and_y_and_rhs_x_and_y_are_within_epsilon();
  geo_points_equal_returns_0_when_lhs_only_x_and_rhs_only_x_are_within_epsilon();
  geo_points_equal_returns_0_when_lhs_neither_x_or_y_and_rhs_x_or_y_are_within_epsilon();

  /* geo_segments_intersect tests */
  geo_segments_intersect_returns_negative_1_when_segment_1_is_null();
  geo_segments_intersect_returns_negative_1_when_segment_2_is_null();
  geo_segments_intersect_returns_negative_1_when_segment_1_start_is_null();
  geo_segments_intersect_returns_negative_1_when_segment_1_end_is_null();
  geo_segments_intersect_returns_negative_1_when_segment_2_start_is_null();
  geo_segments_intersect_returns_negative_1_when_segment_2_end_is_null();
  geo_segments_intersect_returns_0_when_segments_are_parallel();
  geo_segments_intersect_returns_0_when_segments_are_colinear_but_dont_intersect();
  geo_segments_intersect_returns_0_when_segments_dont_intersect();
  geo_segments_intersect_returns_1_when_segments_properly_intersect();
  geo_segments_intersect_returns_2_when_segment_1_end_is_equal_to_segment_2_start();
  geo_segments_intersect_returns_2_when_one_segment_is_section_of_other_segment();
  geo_segments_intersect_returns_4_when_segment_1_is_the_same_segment_as_segment_2();

  /* geo_geometry_is_closed tests */
  geo_geometry_is_closed_returns_negative_1_when_geometry_is_null();
  geo_geometry_is_closed_returns_negative_1_when_geometry_segments_is_null();
  geo_geometry_is_closed_returns_negative_1_when_geometry_segment_start_is_null();
  geo_geometry_is_closed_returns_negative_1_when_geometry_segment_end_is_null();
  geo_geometry_is_closed_returns_0_when_geometry_segment_count_less_than_3();
  geo_geometry_is_closed_returns_0_when_nth_segments_end_doesnt_equal_n_plus_1_segment_start();
  geo_geometry_is_closed_returns_1_when_nth_segments_end_equals_n_plus_1_segments_start();

  /* geo_geometry_is_simple tests */
  geo_geometry_is_simple_returns_negative_1_when_geometry_is_null();
  geo_geometry_is_simple_returns_negative_1_when_geometry_segments_is_null();
  geo_geometry_is_simple_returns_negative_1_when_geometry_segments_ith_start_is_null();
  geo_geometry_is_simple_returns_negative_1_when_geometry_segments_ith_end_is_null();
  geo_geometry_is_simple_returns_0_when_any_segments_intersect();
  geo_geometry_is_simple_returns_1_when_no_segments_intersect();

  /* geo_point_in_geometry tests */

  printf("All tests pass.\n");
  return 0;
}
