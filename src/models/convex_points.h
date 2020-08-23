#ifndef SPANNERS_SRC_MODELS_CONVEX_POINTS_H
#define SPANNERS_SRC_MODELS_CONVEX_POINTS_H

#include "point2d.h"
#include <vector>

// Class to handle a set of convex points. As one can see, right now it is
// just a bare shell.
// 
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !! WARNING: For now, I assume the user is responsible and provides a set !!
// !! of points that is convex. Currently, there is no checking for that.   !!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
// TODO: Add the following functionality
// - Default ccw-sort for the input points.
// - Check if input set is actually convex.

class ConvexPoints {
 public:
  std::vector<Point2D> points;

  ConvexPoints(std::vector<Point2D> points_): points(points_) {}
};


#endif // SPANNERS_SRC_MODELS_CONVEX_POINTS_H
