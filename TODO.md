# TODO Items (not in order)
- [ ] think about getting rid of need for `<math.h>`. The only function needed from there is `fabs`. Changing these to `value < EPSION && value > -EPSILON` would save needing this dependecy to be linked but possibly slower in general.
- [ ] handle floats bounds checking. Currently, there's potential overflows in the cross and dot products. These should be handled correctly.
- [ ] create a `TYPE` macro to allow for support of `float` and `double` depending on how it's compiled.
- [ ] segments and points all all passed as `struct Type const * const name`. For trivial structs (such as point) that don't modify the point or segment, passing by value might be a better way to handle this. Need to think about whether this has a tangible benefit over just the `const *` being passed.
- [ ] for `geo_point_in_geometry`, would there be a benefit in finding the geometry's bounding box and seeing if the point is inside that before checking? could this speed up the calculation?
- [ ] implement `r-tree` or `r*-tree` for holding all geometries and points.
- [ ] switch to c99? `boolean`, `inline`, designated initializers, and fixed width types sound tasty.
- [ ] change stdlib.h's `qsort` to other hand written sorting algo in order to facilitate removing stdlib.h/any reliance on the standard lib. Removing `qsort` also allows for not using the nasty little `global_starting_point` variable to sneaky pass an additional argument to the `compare` fn.
- [ ] consider not using local variables for everything. Example in `geo_convex_hull`, `current_y` and `miny_y` variables aren't needed. It just saved me from typing and saved the need to dereference the pointer to find the `y` values. C89 also required variables upfront which means sometimes extra vars are initialized that aren't actually used.
