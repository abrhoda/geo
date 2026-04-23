#ifndef GEO_H
#define GEO_H

enum geo_result {
  GEO_SUCCESS = 0,
  GEO_ERR_NULL_POINTER = 1,
  GEO_ERR_TOO_SMALL = 2,
  GEO_ERR_OVERFLOW = 3  // unused for now
};

enum geo_orientation { RIGHT = -1, COLINEAR = 0, LEFT = 1 };
#endif
