# geo
geofencing library in c89.

## Public API
See doxygen documentation.

### Properties of a Geometry
`geometry_is_closed` simply checks that a set of line segments form a closed loop through testing that the nth line segment ends at the start point of the (n+1)th line segment and that the last line segment ends at the start point of the first line segment.

`geometry_is_simple` checks that none of the line segments in a geometry intersect with each other. It should be noted that these lines should **not** be considered intersecting even while sharing exactly 1 point (segment n's end point and segment (n+1)'s start point).

### Intersecting Line Segments
In the `lines_intersect` function, there is the case where two line segments intersect at the start or end of one of the line segments. Example: segment AB = (0, 0) (0, 1) and segment CD = (0, -1) (0, 1). These two segments intersect at (0, 0). While this seems trivial, the `orient` based solution doesn't solve this. There is a section in reference 1 that I need to implement to solve this properly. There should be a boolean `count_endpoints_as_intersect`, or some shorter for brevity, that allows for the `line_segments_intersect` to handle the case in the example as well as the case in `geometry_is_simple` where one line segment's end point being the next line segment's starting point should **not** count as intersecting.

### Point In Polygon
In the `point_in_geometry` function, this entire function might need a rewrite due to the case where a point might share the same x coordinate as a point in the geometry. Example of how this can happen: segment AB = (0, 0) (3, 0), segment BC = (3, 0) (3, 3), segment CD = (3, 3) (2, 1), segment DE = (2, 1) (0, 3), and segment EF = (0, 3) (0, 0) and point P = (0.5, 1). This "ray" from P will intersect the geometry at D and then again at point (3, 1) on segment BC. If intersecting at the point were to count, it would cross the geometry twice which indicated it is outside the geometry while it is not. This means that when looking at the `point_in_polygon` function, intersecting at a point should not be considered an intersection.

However, if a point is colinear with any line segment of the geometry, the point could be considered in the geometry. In some uses of this library it could be considered inside while some other uses it could be considered outside. Allow for a boolean parameter to control this.

## TODOs For Future Me
- [ ] validate function input params for `NULL`. Currently, there's no input validation! Doing this will also require updating doxygen documentation in the `geo.h` file.
- [ ] think about getting rid of need for `<math.h>`. The only function needed from there is `fabs`. Changing these to `value < EPSION && value > -EPSILON` would save needing this dependecy to be linked but possibly slower in general.
- [ ] handle floats bounds checking. Currently, there's potential overflows in the cross and dot products. These should be handled correctly.
- [ ] create a `TYPE` macro to allow for support of `float` and `double` depending on how it's compiled.
- [ ] segments and points all all passed as `struct Type const * const name`. For trivial structs (such as point) that don't modify the point or segment, passing by value might be a better way to handle this. Need to think about whether this has a tangible benefit over just the `const *` being passed.

# Code Layout, Contribution Guide, and Design Considerations
1. set up dirs with `make setup`
2. Run `make format && make lint`
3. Defensive coding. Check nulls even where excessive. It's the trade off of not owning memory allocations.
4. Write unit tests.

## Unit Tests
Check `UNIT_TEST_CASES.md` where I documented unit tests. To run the unit tests, run `make setup && make test` from project root.

## References
1. [Handbook of Geometry for Competitive Programmers](https://victorlecomte.com/cp-geo.pdf) - used for learning about programmatic approaches to determining line segment intersections and other neat geometry things.
