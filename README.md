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

## TODOs
See [TODO.md](TODO.md) file.

## Code Layout, Contribution Guide, and Design Considerations
1. set up dirs with `make setup`
2. Run `make format && make lint`
3. Defensive coding. Check nulls even where excessive. It's the trade off of not owning memory allocations. `GEO_UNSAFE` macro should be implemented around null checks to optionally (and dangerously) strip them out.
4. Write unit tests.

## Unit Tests
Check list in [UNIT_TEST_CASES.md](UNIT_TEST_CASES.md) where I documented unit test cases. To run the unit tests, run `make setup && make test` from project root.

## References
1. [Handbook of Geometry for Competitive Programmers](https://victorlecomte.com/cp-geo.pdf) - used for learning about programmatic approaches to determining line segment intersections and other neat geometry things.
2. [Graham's Scan](https://en.wikipedia.org/wiki/Graham_scan) - pseudocode wiki page should be enough to implement.
