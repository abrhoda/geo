#include "geo_float.h"

#include <stdio.h>
int main(void) {
  struct geo_point_float first = { .x = 0.0F, .y = 1.0F};
  struct geo_point_float second = { .x = 0.0F, .y = 1.0F};
  bool equal = false;
  enum geo_result res = geo_points_equal_float(&first, &second, &equal);
  printf("res: %d.\n", res);
  return 0;
}
