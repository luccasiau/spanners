#ifndef SPANNERS_SRC_ALGORITHMS_GENERAL_PATH_GREEDY_H
#define SPANNERS_SRC_ALGORITHMS_GENERAL_PATH_GREEDY_H

#include "../models/spanner_graph.h"

namespace general_path_greedy {

using ld = long double;

// Algorithm: GeneralPathGreedy. A path-greedy that allows the user to
// forcefully add edges before and after the run. It does NOT update the input
// graph; a copy is created.
//
// Inputs:
//  - SpannerGraph graph: a SpannerGraph in R^2. It may contain edges already.
//  - long double t: t-ratio for PathGreedy
//  - vector<tuple<int, int>> edges_add_before: edges to be added before
//  running path greedy. Default is an empty list.
//  - vector<tuple<int, int>> edges_add_after: edges to be added after running
//  PathGreedy. Default is an empty list.
//  - long double epsilon: for tuning double measurements
SpannerGraph general_path_greedy(
  SpannerGraph graph,
  ld t,
  std::vector<std::tuple<int, int>> edges_add_before = {},
  std::vector<std::tuple<int, int>> edges_add_after = {},
  ld epsilon = 1e-8);
}

#endif  // SPANNERS_SRC_ALGORITHMS_GENERAL_PATH_GREEDY_H