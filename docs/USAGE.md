# Library Usage
This document defines how to include the library in a project, all the macros that can be defined to fine tune the library, and the public enums, functions, and structs that are available.

## Basic Usage
The basic steps are to copy the header file, define the macros that are needed, and then start using it.

### Include the Header
Depending on what type your 2d geometries will use, copy over the correct header.
Type | Header
---|---
`double` | `geo_decimal_template.h`
`float` | `geo_decimal_template.h`
`long` | `geo_integer_template.h`
`int` | `geo_integer_template.h`

[Warning](../README.md#warning) to only use binary floating point types with `geo_decimal_template.h`.

### Define Required Macros
Macro             | Description                                                            | Value                                                                     | Required
------------------|------------------------------------------------------------------------|---------------------------------------------------------------------------|-----------------------------------
`TMPL_IMPL`       | Defining this includes the implementation of the library               |                                                                           | X 
`TMPL_TYPE`       | Defines which generic type for the implementation                      | This is the `type` that your geometries will be                           | X
`TMPL_TYPE_FIXED` | Used in [unit of least percison](../README.md#references) calculation  | Must be an int type that satisfies `sizeof(TMPL_TYPE) == TMPL_TYPE_FIXED` | X (only for floating point types).
`ABS_EPSILON`     | Used in floating point comparison                                      | Suggested values: `1e-12` for `double` and `1e-9` for `float`             | X (only for floating point types).
`REL_EPSILON`     | Used in floating point comparison                                      | Suggested values: `1e-9` for `double` and `1e-6` for `float`              | X (only for floating point types).
`MAX_ULPS`        | Used in floating point comparison                                      | Suggested value: `4` (this is what `Boost` libraries use)                 | X (only for floating point types).

### Use The Library
This is a complete, slim, example of copying and including the header, define the required macros, and use the library.
```c
// 1. copy `geo_decimal_template.h` into header dir

// 2. in my geo_double.h source file, define needed macros
#define TMPL_TYPE double
#define TMPL_TYPE_FIXED int64_t
#define ABS_EPSILON 1e-12
#define REL_EPSILON 1e-9
#define MAX_ULPS 4
#include "geo_decimal_template.h"
#undef MAX_ULPS
#undef REL_EPSILON
#undef ABS_EPSILON
#undef TMPL_TYPE_FIXED
#undef TMPL_TYPE

// 3. in my geo_double.c source file, define implementation macro

#define TMPL_IMPL
#include "geo_double.h"
#undef TMPL_IMPL

// 4. in main.c, use the library
#include "geo_double.h"

int main(void) {
    struct geo_point_double point1 = { .x = 1.0005, .y = 1.0101 };
    struct geo_point_double point2 = { .x = 10.005, .y = 10.010 };
    bool is_equal = false;
    enum geo_result res = geo_points_equal_double(&point1, &point2, &is_equal);
    if (res != GEO_SUCCESS) {
        return 1;
    }

    // do something with is_equal

    return 0;
}
```

## Public API
This provides an overview of all usable enums, functions, and structs in the library.

### Enums
`geo_result` - This is the return type of all publicaly accessible functions. It should be checked to verify the success of a function or, if not a success, why it failed.
```c
enum geo_result {
    GEO_SUCCESS = 0,
    GEO_ERR_NULL_POINTER = 1,
    GEO_ERR_TOO_SMALL = 2,
    GEO_ERR_OVERFLOW = 3  // unused for now
};
```
### Functions
Function Declaration | Description | Notes
---|---|---
`enum geo_result geo_points_equal_<type>(struct geo_point_<type> const* lhs, struct geo_point_<type> const* lhs, bool* is_equal);` | Compares to see if two points are equal | `is_equal` is only set and usable when the function returns `GEO_SUCCESS`
`enum geo_result geo_segments_intersect_<type>(struct geo_segment_<type> const* segment1, struct geo_segment_<type> const* segment2, size_t* intersect_count);` | Determines "count" of times two segments intersect. | `intersect_count` is only set and usable when the function returns `GEO_SUCCESS`. `intersect_count == 0` when the 2 segments never intersect, `1` when the segments properly intersect, `2` when the segments share an endpoint or when one segment is a section of the other, `3` when one segment is a section of the other AND they share an endpoint, `4` when the segments have identical start and end points.
`enum geo_result geo_geometry_is_closed_<type>(struct geo_geometry_<type> const* geometry, bool* is_closed);` | Checks if a geometry is considered closed. This is commonly referred to as a "ring" | `is_closed` is only set and usable when the function returns `GEO_SUCCESS`
`enum geo_result geo_geometry_is_simple_<type>(struct geo_geometry_<type> const* geometry, bool* is_simple);` | Checks if a geometry is considered simple. This means that no segments intersect. | `is_simple` is only set and usable when the function returns `GEO_SUCCESS`
`enum geo_result geo_point_in_geometry_<type>(struct geo_point_<type> const* point, struct geo_geometry_<type> const* geometry, bool strict, bool* is_inside);` | Determines if a point is inside a geometry. | `is_inside` is only set and usable when the function returns `GEO_SUCCESS`. `strict` decides if points on a segment are considered outside or inside the geometry. This function is also only valid when the geometry is both closed and simple. Check those both BEFORE using this function.
`enum geo_result geo_geometry_in_geometry_<type>(struct geo_geometry_<type>* parent, struct geo_geometry_<type>* child, bool strict, bool* is_inside);` | Determines if one geometry is inside another geometry. | `is_inside` is only set and usable when the function returns `GEO_SUCCESS`. `strict` decides if points on a segment are considered outside or inside the geometry. This function is also only valid when both geometries are both closed and simple. Check those both BEFORE using this function.
`enum geo_result geo_convex_hull_<type>(struct geo_point_<type>** points, struct geo_point_<type>** convex_hull, size_t size, size_t* convex_hull_size);` | Generates the list of points, in order, that form a closed and simple geometry that contain all points in `points` | `convex_hull` and `convex_hull_size` are only set and usable when the function returns `GEO_SUCCESS`. The `convex_hull` buffer passed in should be the same size as the `points` buffer for the scenario when all points are needed to form the hull.

### Structs
`geo_point_<type>` - represents a 2d point
```c
struct geo_point_<type> {
    <type> x;
    <type> y;
}
```

`geo_segment_<type>` - a line segment between `start` and `end`
```c
struct geo_segment_<type> {
    struct geo_point_<type> * start;
    struct geo_point_<type> * end;
}
```

`geo_geometry_<type>` - geometry formed by a series of line segments
```c
struct geo_geometry_<type> {
    struct geo_segments_<type> ** segments;
    size_t segments_count;
}
```

## As a Shared or Static Library
while library was written as a header only library, technically, it does provide `src/geo_<type>.c` files which include the header for the respective type. This nothing stops you from turning it into a dynamic (.so/.dll/.dylib) or static (.a/.lib) library but I have not done this myself.
