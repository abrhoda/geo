# Unit Test Cases
Just a checklist of test cases per function.

## geo\_points\_equal
- [x] when lhs == NULL, assert -1
- [x] when rhs == NULL, assert -1
- [x] when lhs and rhs are exactly equal (x = 1.0F, y = 1.0F), assert 1
- [x] when lhs and rhs have both x and y within EPSILON difference, assert 1
- [x] when lhs and rhs have only x or y within EPSILON difference, assert 0
- [x] when lhs and rhs has niether x or y within EPSILON difference, assert 0

## geo\_segments\_intersect
- [x] when segment1 == NULL, assert -1
- [x] when segment2 == NULL, assert -1
- [x] when segment1-\>start == NULL, assert -1
- [x] when segment1-\>end == NULL, assert -1
- [x] when segment2-\>start == NULL, assert -1
- [x] when segment2-\>end == NULL, assert -1
- [x] when segment1 is parallel to segment2, assert 0
- [x] when segment1 is colinear to segment2 but doesn't intersect, assert 0
- [x] when segment1 doesn't intersect segment2, assert 0
- [x] when segment1 intersect segment2 properly, assert 1
- [x] when segment1 end point is equal to segment2 start point, assert 2
- [x] when segment1 is a section of segment 2, assert 2
- [x] when segment2 is a section of segment 1, assert 2
- [x] when segment1 and segment2 have the exact same endpoints, assert 4

## geo\_geometry\_is\_closed
- [x] when geometry == NULL, assert -1
- [x] when geometry-\>segments == NULL, assert -1
- [x] when geometry-\>segments[i]-\>start == NULL, assert -1
- [x] when geometry-\>segments[i]-\>end == NULL, assert -1
- [x] when geometry-\>segments\_count < 3, assert 0
- [x] when every nth segment-\>end == (n+1 [or 0 for last])th segment's-\>start, assert 1
- [x] when nth segment-\>end != (n+1)th segment-\>start, assert 0

## geo\_geometry\_is\_simple
- [ ] when geometry == NULL, assert -1
- [ ] when geometry-\>segments == NULL, assert -1
- [ ] when geometry-\>segments[i]-\>start == NULL, assert -1
- [ ] when geometry-\>segments[i]-\>end == NULL, assert -1
- [ ] when geometry-\>segments\_count < 3, assert 0
- [ ] when geometry-\>segments[i] and every [i..len] segment don't intersect, return 1
- [ ] when geometry-\>segments[i] and some of [i..len] segment do intersect, return 0

## geo\_point\_in\_geometry
- [ ] when point == NULL, assert -1
- [ ] when geometry == NULL, assert -1
- [ ] when geometry-\>segments == NULL, assert -1
- [ ] when geometry-\>segments\_count < 3, assert 0
- [ ] when geometry-\>segments[i] and every [i..len] segment don't intersect, return 1
- [ ] when geometry-\>segments[i]-\>start == NULL, assert -1
- [ ] when geometry-\>segments[i]-\>end == NULL, assert -1
- [ ] when atrict is 1 and point is on geometry-\>segments[i], assert 0
- [ ] when atrict is 0 and point is on geometry-\>segments[i], assert 1
- [ ] when point is to the left of the geometry and colinear with geometry-\>segment[i], return 0
- [ ] when point is to the right of the geometry, return 0
- [ ] when point is above of the geometry and colinear with geometry-\>segment[i], return 0
- [ ] when point is below of the geometry and colinear with geometry-\>segment[i], return 0
- [ ] when ray cast has the same y coordinate with exactly end/start pair, assert 1 (this is to test the case where a point in a geometry "crosses" 2 segment of the geometry exactly at thier endpoints.)
- [ ] when ray cast has the same y coordinate witt multiple end/start pair, assert 1 (this is to test the case where a point's ray can have an even number of crossings and still be inside the geometry)
