#include <algorithm>
#include <tuple>
#include "path_greedy.h"

using ld=long double;

SpannerGraph path_greedy::path_greedy(ConvexPoints convex_points, ld t) {
  int N = (int)convex_points.points.size();
  SpannerGraph spanner = SpannerGraph(convex_points);
  // TODO: FINISH
  std::vector<std::tuple<ld, int, int>> all_pairs;
  return spanner;
}

bool plane_greedy_sort(std::tuple<ld, int, int> a, std::tuple<ld, int, int> b) {
  if (abs(a.get(0) - b.get(0)) > 1e-8) {
    return a.get(0) < b.get(0);
  }
  if (a.get(1) != b.get(1) {
    return a.get(1) < b.get(1);
  }
  return a.get(2) < b.get(2);
}
