#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <map>
#include <tuple>
#include <vector>
#include <cstdlib>
#include "general_path_greedy.h"
#include <iostream>
#include <ctime>

std::map<std::pair<int, int>, int> lazy_rand;

bool path_greedy_sort(std::tuple<ld, int, int> a, std::tuple<ld, int, int> b);
bool path_greedy_sort_random_tiebreak(
  std::tuple<ld, int, int> a, std::tuple<ld, int, int> b);

SpannerGraph general_path_greedy::general_path_greedy(
    SpannerGraph graph,
    ld t,
    std::vector<std::tuple<int, int>> edges_add_before,
    std::vector<std::tuple<int, int>> edges_add_after,
    bool random_tiebreak,
    ld epsilon) {

  SpannerGraph spanner = graph;

  // Add edges before
  for (auto& tup : edges_add_before) {
    spanner.add_edge(std::get<0>(tup), std::get<1>(tup));
  }

  // Main PathGreedy
  std::vector<std::tuple<ld, int, int>> all_pairs;
  for (int i = 0; i < spanner.size(); i++) {
    for (int j = i+1; j < spanner.size(); j++) {
      all_pairs.push_back(std::make_tuple(spanner.euclidean_distance(i, j), i, j));
    }
  }

  if (random_tiebreak) {
    for (int i = 0; i < (int) spanner.size(); i++) {
      for (int j = 0; j < (int) spanner.size(); j++) {
        lazy_rand[{i, j}] = rand();
      }
    }
    std::sort(
      all_pairs.begin(), all_pairs.end(), path_greedy_sort_random_tiebreak);
  } else {
    std::sort(all_pairs.begin(), all_pairs.end(), path_greedy_sort);
  }

  for (auto& p : all_pairs) {
    int a = std::get<1>(p);
    int b = std::get<2>(p);

    // If ShortestPath(a, b) > t * euclidean(a, b), add an edge.
    if (spanner.shortest_path(a, b) >
          t * spanner.euclidean_distance(a, b) + epsilon) {
      spanner.add_edge(a, b);
    }
  }

  // Add edges after
  for (auto& tup : edges_add_after) {
    spanner.add_edge(std::get<0>(tup), std::get<1>(tup));
  }

  return spanner;
}


// Is this the same as the path greedy sort? Maybe I should avoid code copying
bool path_greedy_sort(std::tuple<ld, int, int> a, std::tuple<ld, int, int> b) {
  // FIXME: 1e-8 shouldn't be hardcoded here.
  if (abs(std::get<0>(a) - std::get<0>(b)) > 1e-8) {
    return std::get<0>(a) < std::get<0>(b);
  }
  if (std::get<1>(a) != std::get<1>(b)) {
    return std::get<1>(a) < std::get<1>(b);
  }
  return std::get<2>(a) < std::get<2>(b);
}

// Is this the same as the path greedy sort? Maybe I should avoid code copying
bool path_greedy_sort_random_tiebreak(
  std::tuple<ld, int, int> a, std::tuple<ld, int, int> b) {
  // FIXME: 1e-8 shouldn't be hardcoded here.
  if (abs(std::get<0>(a) - std::get<0>(b)) > 1e-8) {
    return std::get<0>(a) < std::get<0>(b);
  }
  return lazy_rand[{std::get<1>(a), std::get<2>(a)}] <
     lazy_rand[{std::get<1>(b), std::get<2>(b)}];
}