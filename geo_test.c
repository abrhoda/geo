#include <assert.h>

#include "geo.h"

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

void geo_geometry_is_closed_returns_1_when_closed(void) {
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

void geo_geometry_is_closed_returns_0_when_not_closed(void) {
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


void geo_geometry_is_simple_returns_1_when_simple(void) {

}

void geo_geometry_is_simple_returns_0_when_not_simple(void) {
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
  point4.y = 2.0F;

  segment1.start = &point1;
  segment1.end = &point2;
  segments[0] = &segment1;
  segment2.start = &point2;
  segment2.end = &point3;
  segments[1] = &segment2;
  segment3.start = &point4;
  segment3.end = &point1;
  segments[2] = &segment3;

  geometry.segments = segments;
  geometry.segments_count = 3;

  result = geo_geometry_is_simple(&geometry);
  assert(result == 0);

}

int main(void) {
  test_geo_points_equal_returns_1_when_points_are_equal();
  test_geo_points_equal_returns_0_when_points_arent_equal();
  test_geo_points_equal_returns_1_when_difference_less_than_epsilon();
  test_geo_points_equal_returns_0_when_difference_more_than_epsilon();
  geo_geometry_is_closed_returns_1_when_closed();
  geo_geometry_is_closed_returns_0_when_not_closed();
  geo_geometry_is_simple_returns_1_when_simple();
  geo_geometry_is_simple_returns_0_when_not_simple();

  return 0;
}
