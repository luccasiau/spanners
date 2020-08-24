#ifndef SPANNERS_SRC_ALGORITHMS_PATH_GREEDY_H
#define SPANNERS_SRC_ALGORITHMS_PATH_GREEDY_H

#include "../models/convex_points.h"
#include "../models/spanner_graph.h"

namespace path_greedy {

using ld=long double;

// Algorithm: PathGreedy(convex_points, t)
// inputs:
//  - convex_points: a set of points in convex position in R^2.
//  - t: a real number > 1.
// output:
//  - spanner_graph guaranteed to be a t-spanner
//
// Note: when sorting (N choose 2) pairs of points in non-decreasing distance
// order, the TIES ARE BROKEN BY SMALLEST ELEMENT INDEX
SpannerGraph path_greedy(ConvexPoints convex_points, ld t);

}

#endif  // SPANNERS_SRC_ALGORITHMS_PATH_GREEDY_H
