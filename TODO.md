# TODO Items (not in order)
- [ ] think about getting rid of need for `<math.h>`. The only function needed from there is `fabs`. Changing these to `value < EPSION && value > -EPSILON` would save needing this dependency to be linked but possibly slower in general.
- [ ] handle floats bounds checking. Currently, there's potential overflows in the cross and dot products. These should be handled correctly. c99 has `isnan` and `isinf` for this.
- [ ] create a `TYPE` macro to allow for support of `float` and `double` depending on how it's compiled.
- [ ] segments and points all all passed as `struct Type const * const name`. For trivial structs (such as point) that don't modify the point or segment, passing by value might be a better way to handle this. Need to think about whether this has a tangible benefit over just the `const *` being passed.
- [ ] for `geo_point_in_geometry`, would there be a benefit in finding the geometry's bounding box and seeing if the point is inside that before checking? could this speed up the calculation?
- [ ] implement `r-tree` or `r*-tree` for holding all geometries and points.
- [ ] change stdlib.h's `qsort` to other hand written sorting algo in order to facilitate removing stdlib.h/any reliance on the standard lib. Removing `qsort` also allows for not using the nasty little `global_starting_point` variable to sneaky pass an additional argument to the `compare` fn.
- [ ] consider not using local variables for everything. Example in `geo_convex_hull`, `current_y` and `miny_y` variables aren't needed. It just saved me from typing and saved the need to dereference the pointer to find the `y` values. C89 also required variables upfront which means sometimes extra vars are initialized that aren't actually used.
- [ ] Make a 3d variant. This requires a lot of work but would be intersting to do. I wonder if the easiest way to turn this into 3d is to introduce a `z` field on the struct and then use the 2d algorithms twice on the point. That means for point p1 = (x1, y1, z1), it is in volume1 if (x1, y1) are in the XY projection of volume1 and (y1, z1) are in the YZ projection of volume1. That would require research.
- [ ] convex hull function requires an "out" array. could save the space and use the "array" array and make the first N elements the hull in place. N = "out" convex\_hull\_size
- [ ] in the `geo_decimal_template.h`, the `GEO_TEST` macro could be used to switch from static linkage to extern that way the static functions can be easily tested.

## Cleanup Items
These items aren't feature work. Just cleaning up my mess.
- [ ] tests in both `test/test_geo_double.c` and `test/test_geo_float.c` having epsilon in the naming. That should be changed to "nearly" or "close"
- [ ] test, in both `test/test_geo_double.c` and `test/test_geo_float.c`, for large values that are close to utilze the `MAX_ULPS` check.
- [ ] tests say `...points_for_triangle`. `for` should be `form`.
- [ ] function params that are pointers should be `restrict`ed where it makes sense.
- [ ] get rid of `geo.h` and just put the enums directly into template headers.
