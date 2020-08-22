#ifndef SPANNERS_SRC_MODELS_GEO_MATH_H
#define SPANNERS_SRC_MODELS_GEO_MATH_H

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

};

#endif // SPANNERS_SRC_MODELS_GEO_MATH_H
