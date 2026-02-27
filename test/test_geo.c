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

  printf("All tests pass.\n");
  return 0;
}
