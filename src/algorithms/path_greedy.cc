#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <tuple>
#include <vector>
#include "path_greedy.h"

bool plane_greedy_sort(std::tuple<ld, int, int> a, std::tuple<ld, int, int> b);

SpannerGraph path_greedy::path_greedy(ConvexPoints convex_points, ld t, ld epsilon) {
  SpannerGraph spanner = SpannerGraph(convex_points);
  std::vector<std::tuple<ld, int, int>> all_pairs;
  for (int i = 0; i < spanner.size(); i++) {
    for (int j = i+1; j < spanner.size(); j++) {
      all_pairs.push_back(std::make_tuple(spanner.euclidean_distance(i, j), i, j));
    }
  }

  std::sort(all_pairs.begin(), all_pairs.end(), plane_greedy_sort);

  for (auto& p : all_pairs) {
    int a = std::get<1>(p);
    int b = std::get<2>(p);

    // If shortest-path between a and b is greater than t * euclidean(a, b),
    // then we draw an edge.
    if (spanner.shortest_path(a, b) > t * spanner.euclidean_distance(a, b)
        + epsilon) {
      spanner.add_edge(a, b);
    }
  }

  return spanner;
}

bool plane_greedy_sort(std::tuple<ld, int, int> a, std::tuple<ld, int, int> b) {
  // FIXME: 1e-8 shouldn't be hardcoded here.
  if (abs(std::get<0>(a) - std::get<0>(b)) > 1e-8) {
    return std::get<0>(a) < std::get<0>(b);
  }
  if (std::get<1>(a) != std::get<1>(b)) {
    return std::get<1>(a) < std::get<1>(b);
  }
  return std::get<2>(a) < std::get<2>(b);
}
