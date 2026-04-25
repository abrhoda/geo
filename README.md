# geo
geofencing library in c99.

## Usage
```
// in my geo_double.c source file

#define TMPL_IMPL
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
#undef TMPL_IMPL

// somewhere else in the code

struct geo_point_double point_a = {.x = 0.0, .y = 0.0};
struct geo_point_double point_b = {.x = 1.0, .y = 1.0};
bool is_equal = false;
enum geo_result res = geo_points_equal_double(&point_a, &point_b, &is_equal);
if (res != GEO_SUCCESS) {
    // error state!
}

// do something with is_equal

```

## Documentation
In depth documentation lives in `docs/`.

### Public API

### Code Design
Most (if not all) functions in the public API return a `enum geo_result` return value and use out params. Out params should only be used when the returned `enum geo_result value == GEO_SUCCESS`.

### Flags/Macros
There are some useful flags that can be set at compile time:

#### General
- `TMPL_IMPL` - set this in the `.c` or `.cpp` source file you plan to include the header in. This should be set in **exactly 1** source file. This follows the pattern of common header only libraries such as [nothings/stb](https://github.com/nothings/stb#how-do-i-use-these-libraries). Due to headers from this library potentially being multiple times (once for `double` and once for `int`), cleaning up the macro after including the header file. This ends up looking something like:
```
#define TMPL_IMPL
#include "geo_double.h"
#undef TMPL_IMPL

```
- `TMPL_TYPE` - sets the type for the template header. This should be the types your geometries and points use. Typically, this will be either `double` or `float` but a separate header simplified specifically for integer types is available (`int` or `long` are tested).
- `GEO_UNSAFE` - setting this macro at compilation time removes all checks for null. These are not done through assertions and many of the public api will stop returning -1 on errors. *WARNING*: Setting this could lead to undefined behavior. This pushes all validation of NULL pointers and geometry's segment\_counts >= 3 onto the caller.
- `TEST` - currently unused but is set during the unit test compilation. This allows for any test specific behavior.

#### Double/Float
These are in addition to the general macros. If you do not wish to deal with this and just want sane defaults, include BOTH the `geo_<type>.h` and `geo_decimal_template.h` (or `geo_integer_template.h` for int or long). You can see this is done in the testing of this repository. Example: `src/geo_double.c` --> `include/geo_double.h` --> `include/geo_decimal_template.h`
- `TMPL_TYPE_FIXED` - fixed size integer to use for ulp calculations. For `TMPL_TYPE == double`, set `TMPL_TYPE_FIXED == int64_t`. For `TMPL_TYPE == float`, set `TMPL_TYPE_FIXED == int32_t`. `sizeof(TMPL_TYPE) == sizeof(TMPL_TYPE_FIXED)` if you are looking to provide other types.
- `ABS_EPSILON` - sets a absolute epsilon value for comparing `TMPL_TYPE`s
- `REL_EPSILON` - sets a relative epsilon value for comparing `TMPL_TYPE`s
- `MAX_ULPS` - sets the maximum difference of `unit of least percision` when comparing `TMPL_TYPE`s. See references 4 and 5 if you are interested in knowing this deeper.

## TODOs
See [TODO.md](TODO.md) file.

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
