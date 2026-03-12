# geo
geofencing library in c89.

## Documentation

### Public API
See doxygen documentation.

### Flags/Macros
There are some useful flags that can be set at compile time:
- `GEO_EPSILON` - allows for control over the tolerance when comparing floats. Defaults to `0.00001`. Set this to a different value if you want a different tolerance.
- `GEO_UNSAFE` - setting this macro at compilation time removes all checks for null. These are not done through assertions and many of the public api will stop returning -1 on errors. *WARNING*: Setting this could lead to undefined behavior. This pushes all validation of NULL pointers and geometry's segment\_counts >= 3 onto the caller.
- `TEST` - currently unused but is set during the unit test compilation. This allows for any test specific behavior.

## TODO Items (not in order)
- [ ] think about getting rid of need for `<math.h>`. The only function needed from there is `fabs`. Changing these to `value < EPSION && value > -EPSILON` would save needing this dependecy to be linked but possibly slower in general.
- [ ] handle floats bounds checking. Currently, there's potential overflows in the cross and dot products. These should be handled correctly.
- [ ] create a `TYPE` macro to allow for support of `float` and `double` depending on how it's compiled.
- [ ] segments and points all all passed as `struct Type const * const name`. For trivial structs (such as point) that don't modify the point or segment, passing by value might be a better way to handle this. Need to think about whether this has a tangible benefit over just the `const *` being passed.
- [ ] for `geo_point_in_geometry`, would there be a benefit in finding the geometry's bounding box and seeing if the point is inside that before checking? could this speed up the calculation?
- [ ] implement `r-tree` and `r*-tree` for holding all geometries and points.
- [ ] switch to c99? `boolean`, `inline`, and designated initializers sound tasy.

## Code Layout, Contribution Guide, and Design Considerations
1. set up dirs with `make setup`
2. Run `make format && make lint`
3. Defensive coding. Check nulls even where excessive. It's the trade off of not owning memory allocations. `GEO_UNSAFE` macro removes this.
4. Write unit tests.

## Unit Tests
Check `UNIT_TEST_CASES.md` where I documented unit tests. To run the unit tests, run `make setup && make test` from project root.

## References
1. [Handbook of Geometry for Competitive Programmers](https://victorlecomte.com/cp-geo.pdf) - used for learning about programmatic approaches to determining line segment intersections and other neat geometry things.
