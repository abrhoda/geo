#include "geo.h"
#include <stdio.h>

int main(void) {
  struct point point = { 0.5F, -0.5F };
  struct point vertex1 = {0.0F, 0.0F};
  struct point vertex2 = {3.0F, 0.0F};
  struct point vertex3 = {3.0F, 3.0F};
  struct point vertex4 = {0.0F, 3.0F};

  struct line line1;
  struct line line2;
  struct line line3;
  struct line line4;
  struct line *lines[4];

  struct geometry geometry;

  int is_inside = 0;

  line1.start = &vertex1;
  line1.end = &vertex2;
  line2.start = &vertex2;
  line2.end = &vertex3;
  line3.start = &vertex3;
  line3.end = &vertex4;
  line4.start = &vertex4;
  line4.end = &vertex1;

  lines[0] = &line1;
  lines[1] = &line2;
  lines[2] = &line3;
  lines[3] = &line4;

  geometry.lines = lines;
  geometry.lines_count = 4;

  is_inside = point_in_geometry(&point, &geometry);

  printf("point is in geometry: %d\n", is_inside);

  return 0;
}
