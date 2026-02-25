#include <assert.h>
#include <stdio.h>

#include "../src/geo.h"

void test_geo_points_equal_returns_1_when_points_are_equal(void) {
  struct geo_point point1;
  struct geo_point point2;
  int result = 0;

  point1.x = 1.0F;
  point1.y = 1.0F;
  point2.x = 1.0F;
  point2.y = 1.0F;

  result = geo_points_equal(&point1, &point2);

  assert(result);
}

void test_geo_points_equal_returns_0_when_points_arent_equal(void) {
  struct geo_point point1;
  struct geo_point point2;
  int result = 0;

  point1.x = 1.0F;
  point1.y = 1.0F;
  point2.x = 2.0F;
  point2.y = 2.0F;

  result = geo_points_equal(&point1, &point2);

  assert(result == 0);
}

void test_geo_points_equal_returns_1_when_difference_less_than_epsilon(void) {
  struct geo_point point1;
  struct geo_point point2;
  int result = 0;

  point1.x = 1.000001F;
  point1.y = 0.999999F;
  point2.x = 1.0F;
  point2.y = 1.0F;

  result = geo_points_equal(&point1, &point2);

  assert(result);
}

void test_geo_points_equal_returns_0_when_difference_more_than_epsilon(void) {
  struct geo_point point1;
  struct geo_point point2;
  int result = 0;

  point1.x = 1.000019F;
  point1.y = 0.9999F;
  point2.x = 1.0F;
  point2.y = 1.0F;

  result = geo_points_equal(&point1, &point2);

  assert(result == 0);
}

void test_geo_points_equal_returns__negative_1_when_lhs_is_null_ptr(void) {
  struct geo_point point;
  int result = 0;

  point.x = 1.0F;
  point.y = 1.0F;

  result = geo_points_equal(0, &point);

  assert(result == -1);
}

void test_geo_points_equal_returns__negative_1_when_rhs_is_null_ptr(void) {
  struct geo_point point;
  int result = 0;

  point.x = 1.0F;
  point.y = 1.0F;

  result = geo_points_equal(&point, 0);

  assert(result == -1);
}

void test_geo_segments_intersect_returns_0_when_no_intersection(void) {
  struct geo_point point1;
  struct geo_point point2;
  struct geo_point point3;
  struct geo_point point4;
  struct geo_segment segment1;
  struct geo_segment segment2;
  int result = 0;

  point1.x = 0.0F;
  point1.y = 0.0F;
  point2.x = 2.0F;
  point2.y = 0.0F;
  point3.x = 0.0F;
  point3.y = 2.0F;
  point4.x = 1.0F;
  point4.y = 1.0F;

  segment1.start = &point1;
  segment1.end = &point2;
  segment2.start = &point3;
  segment2.end = &point4;

  result = geo_segments_intersect(&segment1, &segment2);
  assert(result == 0);
}

void test_geo_segments_intersect_returns_1_when_proper_intersection(void) {
  struct geo_point point1;
  struct geo_point point2;
  struct geo_point point3;
  struct geo_point point4;
  struct geo_segment segment1;
  struct geo_segment segment2;
  int result = 0;

  point1.x = 0.0F;
  point1.y = 0.0F;
  point2.x = 2.0F;
  point2.y = 2.0F;
  point3.x = 0.0F;
  point3.y = 2.0F;
  point4.x = 2.0F;
  point4.y = 0.0F;

  segment1.start = &point1;
  segment1.end = &point2;
  segment2.start = &point3;
  segment2.end = &point4;

  result = geo_segments_intersect(&segment1, &segment2);
  assert(result == 1);
}

void test_geo_segments_intersect_returns_2_when_1_segment_entirely_contained_by_other_segment(void) {
  struct geo_point point1;
  struct geo_point point2;
  struct geo_point point3;
  struct geo_point point4;
  struct geo_segment segment1;
  struct geo_segment segment2;
  int result = 0;

  point1.x = 0.0F;
  point1.y = 0.0F;
  point2.x = 4.0F;
  point2.y = 0.0F;
  point3.x = 1.0F;
  point3.y = 0.0F;
  point4.x = 3.0F;
  point4.y = 0.0F;

  segment1.start = &point1;
  segment1.end = &point2;
  segment2.start = &point3;
  segment2.end = &point4;

  result = geo_segments_intersect(&segment1, &segment2);
  assert(result == 2);
}

void test_geo_segments_intersect_returns_3_when_1_segment_entirely_contained_by_other_segment_sharing_1_endpoint(void) {
  struct geo_point point1;
  struct geo_point point2;
  struct geo_point point3;
  struct geo_point point4;
  struct geo_segment segment1;
  struct geo_segment segment2;
  int result = 0;

  point1.x = 0.0F;
  point1.y = 0.0F;
  point2.x = 4.0F;
  point2.y = 0.0F;
  point3.x = 1.0F;
  point3.y = 0.0F;
  point4.x = 4.0F;
  point4.y = 0.0F;

  segment1.start = &point1;
  segment1.end = &point2;
  segment2.start = &point3;
  segment2.end = &point4;

  result = geo_segments_intersect(&segment1, &segment2);
  assert(result == 3);
}

void test_geo_segments_intersect_returns_4_when_segments_are_exactly_equal(void) {
  struct geo_point point1;
  struct geo_point point2;
  struct geo_point point3;
  struct geo_point point4;
  struct geo_segment segment1;
  struct geo_segment segment2;
  int result = 0;

  point1.x = 0.0F;
  point1.y = 0.0F;
  point2.x = 4.0F;
  point2.y = 0.0F;
  point3.x = 0.0F;
  point3.y = 0.0F;
  point4.x = 4.0F;
  point4.y = 0.0F;

  segment1.start = &point1;
  segment1.end = &point2;
  segment2.start = &point3;
  segment2.end = &point4;

  result = geo_segments_intersect(&segment1, &segment2);
  assert(result == 4);
}

void test_geo_segments_intersect_returns_1_when_1_segments_start_endpoint_on_other_segment(void) {
  struct geo_point point1;
  struct geo_point point2;
  struct geo_point point3;
  struct geo_point point4;
  struct geo_segment segment1;
  struct geo_segment segment2;
  int result = 0;

  point1.x = 0.0F;
  point1.y = 0.0F;
  point2.x = 4.0F;
  point2.y = 0.0F;
  point3.x = 1.0F;
  point3.y = 0.0F;
  point4.x = 4.0F;
  point4.y = 4.0F;

  segment1.start = &point1;
  segment1.end = &point2;
  segment2.start = &point3;
  segment2.end = &point4;

  result = geo_segments_intersect(&segment1, &segment2);
  assert(result == 1);
}

void test_geo_geometry_is_closed_returns_1_when_closed(void) {
  struct geo_geometry geometry;
  struct geo_segment * segments[4];
  struct geo_segment segment1;
  struct geo_segment segment2;
  struct geo_segment segment3;
  struct geo_segment segment4;
  struct geo_point point1;
  struct geo_point point2;
  struct geo_point point3;
  struct geo_point point4;
  int result = 0;

  point1.x = 0.0F;
  point1.y = 0.0F;
  point2.x = 2.0F;
  point2.y = 0.0F;
  point3.x = 2.0F;
  point3.y = 2.0F;
  point4.x = 0.0F;
  point4.y = 2.0F;

  segment1.start = &point1;
  segment1.end = &point2;
  segments[0] = &segment1;
  segment2.start = &point2;
  segment2.end = &point3;
  segments[1] = &segment2;
  segment3.start = &point3;
  segment3.end = &point4;
  segments[2] = &segment3;
  segment4.start = &point4;
  segment4.end = &point1;
  segments[3] = &segment4;

  geometry.segments = segments;
  geometry.segments_count = 4;

  result = geo_geometry_is_closed(&geometry);
  assert(result);
}

void test_geo_geometry_is_closed_returns_0_when_gap_in_geometry(void) {
  struct geo_geometry geometry;
  struct geo_segment * segments[4];
  struct geo_segment segment1;
  struct geo_segment segment2;
  struct geo_segment segment3;
  struct geo_segment segment4;
  struct geo_point point1;
  struct geo_point point2;
  struct geo_point point3;
  struct geo_point point4;
  struct geo_point point5;
  int result = 0;

  point1.x = 0.0F;
  point1.y = 0.0F;
  point2.x = 2.0F;
  point2.y = 0.0F;
  point3.x = 2.0F;
  point3.y = 2.0F;
  point4.x = 0.0F;
  point4.y = 2.0F;
  point5.x = 0.0F;
  point5.y = 1.0F;

  segment1.start = &point1;
  segment1.end = &point2;
  segments[0] = &segment1;
  segment2.start = &point2;
  segment2.end = &point3;
  segments[1] = &segment2;
  segment3.start = &point3;
  segment3.end = &point4;
  segments[2] = &segment3;
  segment4.start = &point4;
  segment4.end = &point5;
  segments[3] = &segment4;

  geometry.segments = segments;
  geometry.segments_count = 4;

  result = geo_geometry_is_closed(&geometry);
  assert(result == 0);
}

void test_geo_geometry_is_closed_returns_0_when_2_segments_intersect(void) {
  struct geo_geometry geometry;
  struct geo_segment * segments[3];
  struct geo_segment segment1;
  struct geo_segment segment2;
  struct geo_segment segment3;
  struct geo_point point1;
  struct geo_point point2;
  struct geo_point point3;
  struct geo_point point4;
  int result = 0;

  point1.x = 0.0F;
  point1.y = 0.0F;
  point2.x = 2.0F;
  point2.y = 2.0F;
  point3.x = 0.0F;
  point3.y = 2.0F;
  point4.x = 2.0F;
  point4.y = 0.0F;

  segment1.start = &point1;
  segment1.end = &point2;
  segments[0] = &segment1;
  segment2.start = &point2;
  segment2.end = &point3;
  segments[1] = &segment2;
  segment3.start = &point3;
  segment3.end = &point4;
  segments[2] = &segment3;

  geometry.segments = segments;
  geometry.segments_count = 3;

  result = geo_geometry_is_closed(&geometry);
  assert(result == 0);
}

void test_geo_geometry_is_simple_returns_1_when_simple(void) {
  struct geo_geometry geometry;
  struct geo_segment * segments[3];
  struct geo_segment segment1;
  struct geo_segment segment2;
  struct geo_segment segment3;
  struct geo_point point1;
  struct geo_point point2;
  struct geo_point point3;
  int result = 0;

  point1.x = 0.0F;
  point1.y = 0.0F;
  point2.x = 2.0F;
  point2.y = 0.0F;
  point3.x = 1.0F;
  point3.y = 1.0F;

  segment1.start = &point1;
  segment1.end = &point2;
  segments[0] = &segment1;
  segment2.start = &point2;
  segment2.end = &point3;
  segments[1] = &segment2;
  segment2.start = &point3;
  segment3.end = &point1;
  segments[2] = &segment3;

  geometry.segments = segments;
  geometry.segments_count = 3;

  result = geo_geometry_is_simple(&geometry);
  assert(result == 0);
}

void test_geo_geometry_is_simple_returns_0_when_is_open_shape(void) {
  struct geo_geometry geometry;
  struct geo_segment * segments[4];
  struct geo_segment segment1;
  struct geo_segment segment2;
  struct geo_segment segment3;
  struct geo_segment segment4;
  struct geo_point point1;
  struct geo_point point2;
  struct geo_point point3;
  struct geo_point point4;
  struct geo_point point5;
  int result = 0;

  point1.x = 0.0F;
  point1.y = 0.0F;
  point2.x = 2.0F;
  point2.y = 0.0F;
  point3.x = 2.0F;
  point3.y = 2.0F;
  point4.x = 0.0F;
  point4.y = 2.0F;
  point5.x = 0.0F;
  point5.y = 1.0F;

  segment1.start = &point1;
  segment1.end = &point2;
  segments[0] = &segment1;
  segment2.start = &point2;
  segment2.end = &point3;
  segments[1] = &segment2;
  segment3.start = &point3;
  segment3.end = &point4;
  segments[2] = &segment3;
  segment4.start = &point4;
  segment4.end = &point5;
  segments[3] = &segment4;

  geometry.segments = segments;
  geometry.segments_count = 4;

  result = geo_geometry_is_simple(&geometry);
  assert(result == 0);
}

void test_geo_geometry_is_simple_returns_0_when_2_segments_cross(void) {
  struct geo_geometry geometry;
  struct geo_segment * segments[3];
  struct geo_segment segment1;
  struct geo_segment segment2;
  struct geo_segment segment3;
  struct geo_point point1;
  struct geo_point point2;
  struct geo_point point3;
  struct geo_point point4;
  int result = 0;

  point1.x = 0.0F;
  point1.y = 0.0F;
  point2.x = 2.0F;
  point2.y = 2.0F;
  point3.x = 0.0F;
  point3.y = 2.0F;
  point4.x = 2.0F;
  point4.y = 0.0F;

  segment1.start = &point1;
  segment1.end = &point2;
  segments[0] = &segment1;
  segment2.start = &point2;
  segment2.end = &point3;
  segments[1] = &segment2;
  segment3.start = &point3;
  segment3.end = &point4;
  segments[2] = &segment3;

  geometry.segments = segments;
  geometry.segments_count = 3;

  result = geo_geometry_is_simple(&geometry);
  assert(result == 0);
}

void test_geo_point_in_geometry_returns_1_when_point_in_geometry_and_strict_true(void){
  int result = 0;
  int strict = 1;
  struct geo_point to_test = { 1.0F, 1.5F };
  struct geo_point point1 = { 0.0F, 0.0F };
  struct geo_point point2 = { 4.0F, 0.0F };
  struct geo_point point3 = { 5.0F, 2.0F };
  struct geo_point point4 = { 5.0F, 3.0F };
  struct geo_point point5 = { 2.0F, 1.0F };
  struct geo_point point6 = { 2.0F, 2.0F };
  struct geo_point point7 = { 0.0F, 2.0F };
  struct geo_segment segment1;
  struct geo_segment segment2;
  struct geo_segment segment3;
  struct geo_segment segment4;
  struct geo_segment segment5;
  struct geo_segment segment6;
  struct geo_segment segment7;
  struct geo_segment * segments[7];
  struct geo_geometry geom;
  segment1.start = &point1;
  segment1.end = &point2;
  segments[0] = &segment1;
  segment2.start = &point2;
  segment2.end = &point3;
  segments[1] = &segment2;
  segment3.start = &point3;
  segment3.end = &point4;
  segments[2] = &segment3;
  segment4.start = &point4;
  segment4.end = &point5;
  segments[3] = &segment4;
  segment5.start = &point5;
  segment5.end = &point6;
  segments[4] = &segment5;
  segment6.start = &point6;
  segment6.end = &point7;
  segments[5] = &segment6;
  segment7.start = &point7;
  segment7.end = &point1;
  segments[6] = &segment7;

  geom.segments = segments;
  geom.segments_count = 7;

  result = geo_point_in_geometry(&to_test, &geom, strict);
  assert(result == 1);
}

void test_geo_point_in_geometry_returns_0_when_point_to_the_right_of_geometry_and_strict_true(void) {
  int result = 0;
  int strict = 1;
  struct geo_point to_test = { 6.0F, 1.5F };
  struct geo_point point1 = { 0.0F, 0.0F };
  struct geo_point point2 = { 4.0F, 0.0F };
  struct geo_point point3 = { 5.0F, 2.0F };
  struct geo_point point4 = { 5.0F, 3.0F };
  struct geo_point point5 = { 2.0F, 1.0F };
  struct geo_point point6 = { 2.0F, 2.0F };
  struct geo_point point7 = { 0.0F, 2.0F };
  struct geo_segment segment1;
  struct geo_segment segment2;
  struct geo_segment segment3;
  struct geo_segment segment4;
  struct geo_segment segment5;
  struct geo_segment segment6;
  struct geo_segment segment7;
  struct geo_segment * segments[7];
  struct geo_geometry geom;
  segment1.start = &point1;
  segment1.end = &point2;
  segments[0] = &segment1;
  segment2.start = &point2;
  segment2.end = &point3;
  segments[1] = &segment2;
  segment3.start = &point3;
  segment3.end = &point4;
  segments[2] = &segment3;
  segment4.start = &point4;
  segment4.end = &point5;
  segments[3] = &segment4;
  segment5.start = &point5;
  segment5.end = &point6;
  segments[4] = &segment5;
  segment6.start = &point6;
  segment6.end = &point7;
  segments[5] = &segment6;
  segment7.start = &point7;
  segment7.end = &point1;
  segments[6] = &segment7;

  geom.segments = segments;
  geom.segments_count = 7;

  result = geo_point_in_geometry(&to_test, &geom, strict);
  assert(result == 0);
}

void test_geo_point_in_geometry_returns_0_when_point_to_the_left_of_geometry_and_strict_true(void) {
  int result = 0;
  int strict = 1;
  struct geo_point to_test = { -1.0F, 1.5F };
  struct geo_point point1 = { 0.0F, 0.0F };
  struct geo_point point2 = { 4.0F, 0.0F };
  struct geo_point point3 = { 5.0F, 2.0F };
  struct geo_point point4 = { 5.0F, 3.0F };
  struct geo_point point5 = { 2.0F, 1.0F };
  struct geo_point point6 = { 2.0F, 2.0F };
  struct geo_point point7 = { 0.0F, 2.0F };
  struct geo_segment segment1;
  struct geo_segment segment2;
  struct geo_segment segment3;
  struct geo_segment segment4;
  struct geo_segment segment5;
  struct geo_segment segment6;
  struct geo_segment segment7;
  struct geo_segment * segments[7];
  struct geo_geometry geom;
  segment1.start = &point1;
  segment1.end = &point2;
  segments[0] = &segment1;
  segment2.start = &point2;
  segment2.end = &point3;
  segments[1] = &segment2;
  segment3.start = &point3;
  segment3.end = &point4;
  segments[2] = &segment3;
  segment4.start = &point4;
  segment4.end = &point5;
  segments[3] = &segment4;
  segment5.start = &point5;
  segment5.end = &point6;
  segments[4] = &segment5;
  segment6.start = &point6;
  segment6.end = &point7;
  segments[5] = &segment6;
  segment7.start = &point7;
  segment7.end = &point1;
  segments[6] = &segment7;

  geom.segments = segments;
  geom.segments_count = 7;

  result = geo_point_in_geometry(&to_test, &geom, strict);
  assert(result == 0);
}

void test_geo_point_in_geometry_returns_0_when_point_is_above_geometry_and_strict_true(void) {
  int result = 0;
  int strict = 1;
  struct geo_point to_test = { 1.0F, 7.0F };
  struct geo_point point1 = { 0.0F, 0.0F };
  struct geo_point point2 = { 4.0F, 0.0F };
  struct geo_point point3 = { 5.0F, 2.0F };
  struct geo_point point4 = { 5.0F, 3.0F };
  struct geo_point point5 = { 2.0F, 1.0F };
  struct geo_point point6 = { 2.0F, 2.0F };
  struct geo_point point7 = { 0.0F, 2.0F };
  struct geo_segment segment1;
  struct geo_segment segment2;
  struct geo_segment segment3;
  struct geo_segment segment4;
  struct geo_segment segment5;
  struct geo_segment segment6;
  struct geo_segment segment7;
  struct geo_segment * segments[7];
  struct geo_geometry geom;
  segment1.start = &point1;
  segment1.end = &point2;
  segments[0] = &segment1;
  segment2.start = &point2;
  segment2.end = &point3;
  segments[1] = &segment2;
  segment3.start = &point3;
  segment3.end = &point4;
  segments[2] = &segment3;
  segment4.start = &point4;
  segment4.end = &point5;
  segments[3] = &segment4;
  segment5.start = &point5;
  segment5.end = &point6;
  segments[4] = &segment5;
  segment6.start = &point6;
  segment6.end = &point7;
  segments[5] = &segment6;
  segment7.start = &point7;
  segment7.end = &point1;
  segments[6] = &segment7;

  geom.segments = segments;
  geom.segments_count = 7;

  result = geo_point_in_geometry(&to_test, &geom, strict);
  assert(result == 0);
}

void test_geo_point_in_geometry_returns_0_when_point_is_below_geometry_and_strict_true(void) {
  int result = 0;
  int strict = 1;
  struct geo_point to_test = { 1.0F, -1.5F };
  struct geo_point point1 = { 0.0F, 0.0F };
  struct geo_point point2 = { 4.0F, 0.0F };
  struct geo_point point3 = { 5.0F, 2.0F };
  struct geo_point point4 = { 5.0F, 3.0F };
  struct geo_point point5 = { 2.0F, 1.0F };
  struct geo_point point6 = { 2.0F, 2.0F };
  struct geo_point point7 = { 0.0F, 2.0F };
  struct geo_segment segment1;
  struct geo_segment segment2;
  struct geo_segment segment3;
  struct geo_segment segment4;
  struct geo_segment segment5;
  struct geo_segment segment6;
  struct geo_segment segment7;
  struct geo_segment * segments[7];
  struct geo_geometry geom;
  segment1.start = &point1;
  segment1.end = &point2;
  segments[0] = &segment1;
  segment2.start = &point2;
  segment2.end = &point3;
  segments[1] = &segment2;
  segment3.start = &point3;
  segment3.end = &point4;
  segments[2] = &segment3;
  segment4.start = &point4;
  segment4.end = &point5;
  segments[3] = &segment4;
  segment5.start = &point5;
  segment5.end = &point6;
  segments[4] = &segment5;
  segment6.start = &point6;
  segment6.end = &point7;
  segments[5] = &segment6;
  segment7.start = &point7;
  segment7.end = &point1;
  segments[6] = &segment7;

  geom.segments = segments;
  geom.segments_count = 7;

  result = geo_point_in_geometry(&to_test, &geom, strict);
  assert(result == 0);
}

void test_geo_point_in_geometry_returns_0_when_point_is_on_segment_of_geometry_and_strict_true(void) {
  int result = 0;
  int strict = 1;
  struct geo_point to_test = { 0.0F, 1.5F };
  struct geo_point point1 = { 0.0F, 0.0F };
  struct geo_point point2 = { 4.0F, 0.0F };
  struct geo_point point3 = { 5.0F, 2.0F };
  struct geo_point point4 = { 5.0F, 3.0F };
  struct geo_point point5 = { 2.0F, 1.0F };
  struct geo_point point6 = { 2.0F, 2.0F };
  struct geo_point point7 = { 0.0F, 2.0F };
  struct geo_segment segment1;
  struct geo_segment segment2;
  struct geo_segment segment3;
  struct geo_segment segment4;
  struct geo_segment segment5;
  struct geo_segment segment6;
  struct geo_segment segment7;
  struct geo_segment * segments[7];
  struct geo_geometry geom;
  segment1.start = &point1;
  segment1.end = &point2;
  segments[0] = &segment1;
  segment2.start = &point2;
  segment2.end = &point3;
  segments[1] = &segment2;
  segment3.start = &point3;
  segment3.end = &point4;
  segments[2] = &segment3;
  segment4.start = &point4;
  segment4.end = &point5;
  segments[3] = &segment4;
  segment5.start = &point5;
  segment5.end = &point6;
  segments[4] = &segment5;
  segment6.start = &point6;
  segment6.end = &point7;
  segments[5] = &segment6;
  segment7.start = &point7;
  segment7.end = &point1;
  segments[6] = &segment7;

  geom.segments = segments;
  geom.segments_count = 7;

  result = geo_point_in_geometry(&to_test, &geom, strict);
  assert(result == 0);
}

void test_geo_point_in_geometry_returns_1_when_point_is_on_segment_of_geometry_and_strict_false(void) {
  int result = 0;
  int strict = 0;
  struct geo_point to_test = { 2.0F, 0.0F };
  struct geo_point point1 = { 0.0F, 0.0F };
  struct geo_point point2 = { 4.0F, 0.0F };
  struct geo_point point3 = { 5.0F, 2.0F };
  struct geo_point point4 = { 5.0F, 3.0F };
  struct geo_point point5 = { 2.0F, 1.0F };
  struct geo_point point6 = { 2.0F, 2.0F };
  struct geo_point point7 = { 0.0F, 2.0F };
  struct geo_segment segment1;
  struct geo_segment segment2;
  struct geo_segment segment3;
  struct geo_segment segment4;
  struct geo_segment segment5;
  struct geo_segment segment6;
  struct geo_segment segment7;
  struct geo_segment * segments[7];
  struct geo_geometry geom;
  segment1.start = &point1;
  segment1.end = &point2;
  segments[0] = &segment1;
  segment2.start = &point2;
  segment2.end = &point3;
  segments[1] = &segment2;
  segment3.start = &point3;
  segment3.end = &point4;
  segments[2] = &segment3;
  segment4.start = &point4;
  segment4.end = &point5;
  segments[3] = &segment4;
  segment5.start = &point5;
  segment5.end = &point6;
  segments[4] = &segment5;
  segment6.start = &point6;
  segment6.end = &point7;
  segments[5] = &segment6;
  segment7.start = &point7;
  segment7.end = &point1;
  segments[6] = &segment7;

  geom.segments = segments;
  geom.segments_count = 7;

  result = geo_point_in_geometry(&to_test, &geom, strict);
  assert(result == 1);
}

/* these edge cases along with images are documented */
void test_geo_point_in_geometry_returns_1_when_point_crosses_at_vertex_and_different_sgement(void) {
  int result = 0;
  int strict = 1;
  struct geo_point to_test = { 1.0F, 1.0F };
  struct geo_point point1 = { 0.0F, 0.0F };
  struct geo_point point2 = { 4.0F, 0.0F };
  struct geo_point point3 = { 5.0F, 2.0F };
  struct geo_point point4 = { 5.0F, 3.0F };
  struct geo_point point5 = { 2.0F, 1.0F };
  struct geo_point point6 = { 2.0F, 2.0F };
  struct geo_point point7 = { 0.0F, 2.0F };
  struct geo_segment segment1;
  struct geo_segment segment2;
  struct geo_segment segment3;
  struct geo_segment segment4;
  struct geo_segment segment5;
  struct geo_segment segment6;
  struct geo_segment segment7;
  struct geo_segment * segments[7];
  struct geo_geometry geom;
  segment1.start = &point1;
  segment1.end = &point2;
  segments[0] = &segment1;
  segment2.start = &point2;
  segment2.end = &point3;
  segments[1] = &segment2;
  segment3.start = &point3;
  segment3.end = &point4;
  segments[2] = &segment3;
  segment4.start = &point4;
  segment4.end = &point5;
  segments[3] = &segment4;
  segment5.start = &point5;
  segment5.end = &point6;
  segments[4] = &segment5;
  segment6.start = &point6;
  segment6.end = &point7;
  segments[5] = &segment6;
  segment7.start = &point7;
  segment7.end = &point1;
  segments[6] = &segment7;

  geom.segments = segments;
  geom.segments_count = 7;

  result = geo_point_in_geometry(&to_test, &geom, strict);
  assert(result == 1);
}

void test_geo_point_in_geometry_returns_1_when_point_crosses_at_only_segment_vertex_geometry(void) {
  int result = 0;
  int strict = 1;
  struct geo_point to_test = { 4.9F, 2.0F };
  struct geo_point point1 = { 0.0F, 0.0F };
  struct geo_point point2 = { 2.0F, 0.0F };
  struct geo_point point3 = { 5.0F, 2.0F };
  struct geo_point point4 = { 5.0F, 3.0F };
  struct geo_point point5 = { 2.0F, 1.0F };
  struct geo_point point6 = { 2.0F, 2.0F };
  struct geo_point point7 = { 0.0F, 2.0F };
  struct geo_segment segment1;
  struct geo_segment segment2;
  struct geo_segment segment3;
  struct geo_segment segment4;
  struct geo_segment segment5;
  struct geo_segment segment6;
  struct geo_segment segment7;
  struct geo_segment * segments[7];
  struct geo_geometry geom;
  segment1.start = &point1;
  segment1.end = &point2;
  segments[0] = &segment1;
  segment2.start = &point2;
  segment2.end = &point3;
  segments[1] = &segment2;
  segment3.start = &point3;
  segment3.end = &point4;
  segments[2] = &segment3;
  segment4.start = &point4;
  segment4.end = &point5;
  segments[3] = &segment4;
  segment5.start = &point5;
  segment5.end = &point6;
  segments[4] = &segment5;
  segment6.start = &point6;
  segment6.end = &point7;
  segments[5] = &segment6;
  segment7.start = &point7;
  segment7.end = &point1;
  segments[6] = &segment7;

  geom.segments = segments;
  geom.segments_count = 7;

  result = geo_point_in_geometry(&to_test, &geom, strict);
  assert(result == 1);
}

int main(void) {
  test_geo_points_equal_returns_1_when_points_are_equal();
  test_geo_points_equal_returns_0_when_points_arent_equal();
  test_geo_points_equal_returns_1_when_difference_less_than_epsilon();
  test_geo_points_equal_returns_0_when_difference_more_than_epsilon();
  test_geo_points_equal_returns__negative_1_when_lhs_is_null_ptr();
  test_geo_points_equal_returns__negative_1_when_rhs_is_null_ptr();

  test_geo_segments_intersect_returns_0_when_no_intersection();
  test_geo_segments_intersect_returns_1_when_proper_intersection();
  test_geo_segments_intersect_returns_2_when_1_segment_entirely_contained_by_other_segment();
  test_geo_segments_intersect_returns_3_when_1_segment_entirely_contained_by_other_segment_sharing_1_endpoint();
  test_geo_segments_intersect_returns_4_when_segments_are_exactly_equal();
  test_geo_segments_intersect_returns_1_when_1_segments_start_endpoint_on_other_segment();

  test_geo_geometry_is_closed_returns_1_when_closed();
  test_geo_geometry_is_closed_returns_0_when_gap_in_geometry();
  test_geo_geometry_is_closed_returns_0_when_2_segments_intersect();

  test_geo_geometry_is_simple_returns_1_when_simple();
  test_geo_geometry_is_simple_returns_0_when_is_open_shape();
  test_geo_geometry_is_simple_returns_0_when_2_segments_cross();

  test_geo_point_in_geometry_returns_1_when_point_in_geometry_and_strict_true();
  test_geo_point_in_geometry_returns_0_when_point_to_the_right_of_geometry_and_strict_true();
  test_geo_point_in_geometry_returns_0_when_point_to_the_left_of_geometry_and_strict_true();
  test_geo_point_in_geometry_returns_0_when_point_is_above_geometry_and_strict_true();
  test_geo_point_in_geometry_returns_0_when_point_is_below_geometry_and_strict_true();

  test_geo_point_in_geometry_returns_0_when_point_is_on_segment_of_geometry_and_strict_true();
  test_geo_point_in_geometry_returns_1_when_point_is_on_segment_of_geometry_and_strict_false();

  test_geo_point_in_geometry_returns_1_when_point_crosses_at_vertex_and_different_sgement();
  test_geo_point_in_geometry_returns_1_when_point_crosses_at_only_segment_vertex_geometry();
  (void) fprintf(stderr, "Tests all passed.\n");
  return 0;
}
