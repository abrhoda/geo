# geo
geofencing library in c99.

## Documentation

### Public API
See doxygen documentation.

### Code Design
Most (if not all) functions in the public API return a `enum geo_result` return value and use out params. Out params should only be used when the returned `enum geo_result value == GEO_SUCCESS`.

### Flags/Macros
There are some useful flags that can be set at compile time:
- `GEO_EPSILON` - allows for control over the tolerance when comparing floats. Defaults to `0.00001`. Set this to a different value if you want a different tolerance.
- `GEO_UNSAFE` - setting this macro at compilation time removes all checks for null. These are not done through assertions and many of the public api will stop returning -1 on errors. *WARNING*: Setting this could lead to undefined behavior. This pushes all validation of NULL pointers and geometry's segment\_counts >= 3 onto the caller.
- `TEST` - currently unused but is set during the unit test compilation. This allows for any test specific behavior.

## TODOs
See [TODO.md](TODO.md) file.

## Code Layout, Contribution Guide, and Design Considerations
1. Set up dirs with `make setup`
2. Run `make clean` after `make setup` to run unit tests.
3. Run `make format && make lint` before committing.
4. Defensive coding. Check nulls even where excessive. It's the trade off of not owning memory allocations. `GEO_UNSAFE` macro should be implemented around null checks to optionally (and dangerously) strip them out.
5. Write unit tests. See `Unit Tests` section below.

## Unit Tests
Check list in [UNIT_TEST_CASES.md](UNIT_TEST_CASES.md) where I documented unit test cases. To run the unit tests, run `make setup && make test` from project root.

## References
1. [Handbook of Geometry for Competitive Programmers](https://victorlecomte.com/cp-geo.pdf) - used for learning about programmatic approaches to determining line segment intersections and other neat geometry things.
2. [PNPOLY - Point Inclusion in Polygon Test](https://wrfranklin.org/Research/Short_Notes/pnpoly.html) - more computational geometry reading to help understand some topics.
3. [Graham's Scan](https://en.wikipedia.org/wiki/Graham_scan) - pseudocode wiki page should be enough to implement.
4. [Comparing Floating Point Numbers, 2012 Edition](https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/) - "fun" with floating point values. Needed in the project for making the dot and cross product implementations robust.
5. [Comparing Floating-Points Numbers Is Tricky](https://bitbashing.io/comparing-floats.html) - more information on ways to compare floats
