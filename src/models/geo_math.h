#ifndef SPANNERS_SRC_MODELS_GEO_MATH_H
#define SPANNERS_SRC_MODELS_GEO_MATH_H

#include <algorithm>
#include "point2d.h"

namespace geo_math {

// Returns the "cross"-product of both two-dimensional vectors.
// This will be returned as a single scalar
//   example: cross(Point2D(1, 2), Point2D(3, 4)) returns -2.
ld cross(Point2D a, Point2D b);

// Returns the dot product of both vectors.
//   example: dot(Point2D(1, 2), Point2D(3, 4)) returns 11.
ld dot(Point2D a, Point2D b);

// Returns the distance between two points, which is the norm of their
// difference.
//   example: distance(Point2D(1, 2), Point2D(1, 4)) returns 2.
ld distance(Point2D a, Point2D b);

// Returns the squared distance between two points, which is the squared norm
// of their difference
//  example: sq_distance(Point2D(1, 2), Point2D(1, 4)) returns 4.
ld sq_distance(Point2D a, Point2D b);

// Returns true iff points a, b, and c are colinear. Epsilon can be tuned with
// the argument.
//   example: colinear(Point2D(0, 0), Point2D(1, 1), Point2D(2, 2)) returns
//  true.
bool colinear(Point2D a, Point2D b, Point2D c, ld epsilon=1e-9);

// Returns true iff point p is within the segment. Use include_endpoints
// [default true] to decide whether to count the segment's endpoints. Epsilon
// can be use to tune comparisons.
bool within_segment(Point2D p, std::pair<Point2D, Point2D> seg,
    bool include_endpoints=true, ld eps=1e-9);

// Returns true iff points (a, b, c) are in counter-clockwise order and ARE
// NOT COLINEAR! Can be calibrated with epsilon. If you want to allow
// colinearity, you can use the above function (recommended) or pass in a
// negative value for epsilon (not recommended).
//  example: ccw(Point2D(0, 0), Point2D(1, 0), Point2D(0, -1)) return false.
bool ccw(Point2D a, Point2D b, Point2D c, ld epsilon=1e-9);

// Returns true iff the two given segments intersect. Use the argument
// include_endpoints to decide whether both segments should include their
// endpoints. Default value is true.
//  example: seg_x_seg({Point2D(0, 0), Point2D(1, 1)}, Point2D(0, 1),
// Point2D(0, 1)}) returns true.
// FIXME: Current version doesn't actually use epsilon.
bool seg_x_seg(std::pair<Point2D, Point2D> seg1,
    std::pair<Point2D, Point2D> seg2, bool include_endpoints=true,
    ld eps=1e-9);
};


#endif // SPANNERS_SRC_MODELS_GEO_MATH_H
