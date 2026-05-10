# geo
2 dimensional geometry library in c99.

## Documentation
See [USAGE.md](docs/USAGE.md) for complete documentation.

### Code Design
Most (if not all) functions in the public API return a `enum GeoResult` return value and use out params. Out params should only be used when the returned `enum GeoResult value == GEO_SUCCESS`.

### Flags/Macros
There are some useful flags that can be set at compile time:

#### General
- `TMPL_IMPL` - set this in the `.c` or `.cpp` source file you plan to include the header in. This should be set in **exactly 1** source file. This follows the pattern of common header only libraries such as [nothings/stb](https://github.com/nothings/stb#how-do-i-use-these-libraries). Due to headers from this library potentially being multiple times (once for `double` and once for `int`), cleaning up the macro after including the header file. This ends up looking something like:

```c
#define TMPL_IMPL
#define GEO_TMPL_TYPE int
#include "geo_integer_template.h"
#undef GEO_TMPL_TYPE
#undef TMPL_IMPL

```
- `TMPL_TYPE` - sets the type for the template header. This should be the types your geometries and points use. Typically, this will be either `double` or `float` but a separate header simplified specifically for integer types is available (`int` or `long` are tested).
- `GEO_UNSAFE` - setting this macro at compilation time removes all checks for null. These are not done through assertions and many of the public api will stop returning -1 on errors. *WARNING*: Setting this could lead to undefined behavior. This pushes all validation of NULL pointers and geometry's segment\_counts >= 3 onto the caller. If you do not check these before calling a library function, do not set this!!
- `TEST` - currently unused but is set during the unit test compilation. This allows for any test specific behavior.

#### Double/Float
There is 1 addition macro that is required to be set along with the `TMPL_TYPE` macro for floating points usage. Due to how comparisons are done between floating points numbers, the `TMPL_TYPE_SIZE` macro is required to be set.

```c
#define GEO_TMPL_TYPE float
#define GEO_TMPL_TYPE_SIZE 32
#include "geo_decimal_template.h"
#undef GEO_TMPL_TYPE_SIZE
#undef GEO_TMPL_TYPE
```

These are addition macros that can optionally be set to fine tune how floating point comparison are done. Check the [USAGE.md](docs/USAGE.md) file to more about those.

## TODOs
See [TODO.md](docs/TODO.md) file.

## Code Layout, Contribution Guide, and Design Considerations
1. Set up dirs with `make setup`
2. Run `make clean` after `make setup` to run unit tests.
3. Run `make format && make lint` before committing.
4. Defensive coding. Check nulls even where excessive. It's the trade off of not owning memory allocations. `GEO_UNSAFE` macro should be implemented around null checks to optionally (and dangerously) strip them out.
5. Write unit tests for effected header file when changes are made. This means that an edit to the `include/geo_integer_template.h` file will require a unit test in both the `test/test_geo_int.c` and `test/test_geo_long.c` files.

## Unit Tests
To run the unit tests, run `make setup && make test` from project root.

## Warning
1. This library was built to meet my needs. It may not meet yours. I am providing "as is" and "as I make changes I like". That said, pull requests are welcome.
2. Using `include/geo_decimal_template.h` (by setting `TMPL_TYPE` as `double` or `float`) expects floating points to be IEEE 754 (binary floating point) compliant. If you include the template header and set the `TMPL_TYPE` to something that is base 10 instead of base 2, this might not work. It's untested.

## References
1. [Handbook of Geometry for Competitive Programmers](https://victorlecomte.com/cp-geo.pdf) - used for learning about programmatic approaches to determining line segment intersections and other neat geometry things.
2. [PNPOLY - Point Inclusion in Polygon Test](https://wrfranklin.org/Research/Short_Notes/pnpoly.html) - more computational geometry reading to help understand some topics.
3. [Graham's Scan](https://en.wikipedia.org/wiki/Graham_scan) - pseudocode wiki page should be enough to implement.
4. [Comparing Floating Point Numbers, 2012 Edition](https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/) - "fun" with floating point values. Needed in the project for making the dot and cross product implementations robust.
5. [Comparing Floating-Points Numbers Is Tricky](https://bitbashing.io/comparing-floats.html) - more information on ways to compare floats

## License
[MIT License](docs/LICENSE)
