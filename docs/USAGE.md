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

### Define Macros
Macro Name   | Description   | Default Value  |  Valid For Types | Required?
-------------|---------------|----------------|------------------|----------
`GEO_TMPL_IMPL`       | Defining this includes the implementation of the library               |                                                                           | | X |
`GEO_TMPL_TYPE`       | Defines which generic type for the implementation                      | No defualt. This is the `type` that your geometries will be               | | X |
`GEO_TMPL_TYPE_SIZE`  | Defines the size (in bits) of the `GEO_TMPL_TYPE`                      | No default. This should be the output of `sizeof(GEO_TMPL_TYPE)*4` for the `GEO_TMPL_TYPE` being used  | Floating Point only | X |
`GEO_TMPL_TYPE_FIXED` | Fixed size int type used in [unit of least percison](../README.md#references) calculation  | `int32_t` when `GEO_TMPL_TYPE_SIZE == 32` and `int64_t` when `GEO_TMPL_TYPE_SIZE == 64`| Floating Point only | |
`GEO_ABS_EPSILON`     | Used in floating point comparison                                      | `1e-12` for `double` and `1e-9` for `float`             | Floating Point only | |
`GEO_REL_EPSILON`     | Used in floating point comparison                                      | `1e-9` for `double` and `1e-6` for `float`              | Floating Point only | |
`GEO_MAX_ULPS`        | Used in floating point comparison                                      | `4` (this is what `Boost` libraries use)                 | Floating Point only | |
`GEO_UNSAFE`       | Defining this strips out any and all null and length checks. Use only if you check null pointers and that all geometries have a segment count of 3 or more before calling any library function     |  | | |

### Use The Library
This is a complete, slim, example of copying and including the header, define the required macros, and use the library.
```c
// 1. copy `geo_decimal_template.h` into header dir

// 2. in my geo_double.h source file, define needed macros
#define GEO_TMPL_TYPE double
#define GEO_TMPL_TYPE_SIZE 64
// I could define addition GEO_ABS_EPSILON if I don't like the default.
#include "geo_decimal_template.h"
#undef GEO_TMPL_TYPE_SIZE
#undef GEO_TMPL_TYPE

// 3. in my geo_double.c source file, define implementation macro

#define GEO_TMPL_IMPL
#include "geo_double.h"
#undef GEO_TMPL_IMPL

// 4. in main.c, use the library
#include <stdbool.h>
#include "geo_double.h"

int main(void) {
    struct GeoPoint_double point1 = { .x = 1.0005, .y = 1.0101 };
    struct GeoPoint_double point2 = { .x = 10.005, .y = 10.010 };
    bool is_equal = false;
    enum GeoResult res = geo_points_equal_double(&point1, &point2, &is_equal);
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
enum GeoResult {
    GEO_SUCCESS = 0,
    GEO_ERR_NULL_POINTER = 1,
    GEO_ERR_TOO_SMALL = 2,
    GEO_ERR_OVERFLOW = 3  // unused for now
};
```
### Functions
Function Declaration | Description | Notes
---|---|---
`enum GeoResult geo_points_equal_<type>(struct GeoPoint_<type> const* lhs, struct GeoPoint_<type> const* lhs, bool* is_equal);` | Compares to see if two points are equal | `is_equal` is only set and usable when the function returns `GEO_SUCCESS`
`enum GeoResult geo_segments_intersect_<type>(struct GeoSegment_<type> const* segment1, struct GeoSegment_<type> const* segment2, size_t* intersect_count);` | Determines "count" of times two segments intersect. | `intersect_count` is only set and usable when the function returns `GEO_SUCCESS`. `intersect_count == 0` when the 2 segments never intersect, `1` when the segments properly intersect, `2` when the segments share an endpoint or when one segment is a section of the other, `3` when one segment is a section of the other AND they share an endpoint, `4` when the segments have identical start and end points.
`enum GeoResult geo_geometry_is_closed_<type>(struct GeoGeometry_<type> const* geometry, bool* is_closed);` | Checks if a geometry is considered closed. This is commonly referred to as a "ring" | `is_closed` is only set and usable when the function returns `GEO_SUCCESS`
`enum GeoResult geo_geometry_is_simple_<type>(struct GeoGeometry_<type> const* geometry, bool* is_simple);` | Checks if a geometry is considered simple. This means that no segments intersect. | `is_simple` is only set and usable when the function returns `GEO_SUCCESS`
`enum GeoResult geo_point_in_geometry_<type>(struct GeoPoint_<type> const* point, struct GeoGeometry_<type> const* geometry, bool strict, bool* is_inside);` | Determines if a point is inside a geometry. | `is_inside` is only set and usable when the function returns `GEO_SUCCESS`. `strict` decides if points on a segment are considered outside or inside the geometry. This function is also only valid when the geometry is both closed and simple. Check those both BEFORE using this function.
`enum GeoResult geo_geometry_in_geometry_<type>(struct GeoGeometry_<type>* parent, struct GeoGeometry_<type>* child, bool strict, bool* is_inside);` | Determines if one geometry is inside another geometry. | `is_inside` is only set and usable when the function returns `GEO_SUCCESS`. `strict` decides if points on a segment are considered outside or inside the geometry. This function is also only valid when both geometries are both closed and simple. Check those both BEFORE using this function.
`enum GeoResult geo_convex_hull_<type>(struct GeoPoint_<type>** points, struct GeoPoint_<type>** convex_hull, size_t size, size_t* convex_hull_size);` | Generates the list of points, in order, that form a closed and simple geometry that contain all points in `points` | `convex_hull` and `convex_hull_size` are only set and usable when the function returns `GEO_SUCCESS`. The `convex_hull` buffer passed in should be the same size as the `points` buffer for the scenario when all points are needed to form the hull.

### Structs
`GeoPoint_<type>` - represents a 2d point
```c
struct GeoPoint_<type> {
    <type> x;
    <type> y;
}
```

`GeoSegment_<type>` - a line segment between `start` and `end`
```c
struct GeoSegment_<type> {
    struct GeoPoint_<type> * start;
    struct GeoPoint_<type> * end;
}
```

`GeoGeometry_<type>` - geometry formed by a series of line segments
```c
struct GeoGeometry_<type> {
    struct GeoSegments_<type> ** segments;
    size_t segments_count;
}
```

## As a Shared or Static Library
While library was written as a header only library, technically, it does provide `src/geo_<type>.c` files which include the header for the respective type. This means nothing stops you from turning it into a dynamic (.so/.dll/.dylib) or static (.a/.lib) library but I have not done this myself.
