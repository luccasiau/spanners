#include <algorithm>
#include "convex_points.h"
#include "geo_math.h"
#include "spanner_graph.h"
#include "../algorithms/floyd_warshall.h"

SpannerGraph::SpannerGraph(ConvexPoints points) : convex_points(points) {
  // convex_points = points; 
  N = (int)convex_points.points.size();

  is_shortest_path_updated = false;
  degree = vector<int>(N, 0);
  adj_matrix = vector<vector<ld>>(N, vector<ld>(N, INF)); 
  sp_matrix = vector<vector<ld>>(N, vector<ld>(N, INF));

  is_spanning_ratio_updated = false;
  calculate_euclidean_distances();
}

void SpannerGraph::add_edge(int a, int b) {
  if (a < 0 || a >= N || b < 0 || b >= N) {
    return;
  }
  if (adj_matrix[a][b] < INF - 0.1) {
    return;
  }

  adj_matrix[a][b] = adj_matrix[b][a] = euclidean_distance[a][b];
  degree[a]++;
  degree[b]++;
  is_shortest_path_updated = false;
  is_spanning_ratio_updated = false;
}

void SpannerGraph::remove_edge(int a, int b) {
  if (a < 0 || a >= N || b < 0 || b >= N) {
    return;
  }
  if (adj_matrix[a][b] > INF - 0.1) {
    return;
  }

  adj_matrix[a][b] = adj_matrix[b][a] = INF;
  degree[a]--;
  degree[b]--;
  is_shortest_path_updated = false;
  is_spanning_ratio_updated = false;
}

ld SpannerGraph::get_spanning_ratio(bool update_if_needed) {
  if (update_if_needed && !is_spanning_ratio_updated) {
    update_spanning_ratio();
  }

  return spanning_ratio;
}

void SpannerGraph::update_spanning_ratio() {
  if (!is_shortest_path_updated) {
    update_shortest_paths();
  }

  is_spanning_ratio_updated = true;
  spanning_ratio = 0.0;
  for (int i = 0; i < N; i++) {
    for (int j = i+1; j < N; j++) {
      if (sp_matrix[i][j] > INF-0.1) {
        spanning_ratio = INF;
        return;
      }

      spanning_ratio = std::max(spanning_ratio,
                           sp_matrix[i][j]/euclidean_distance[i][j]);
    }
  }
}

ld SpannerGraph::shortest_distance(int a, int b, bool update_if_needed) {
  if (a < 0 || a >= N || b < 0 || b >= N) {
    return INF;
  } 
  if (update_if_needed && !is_shortest_path_updated) {
    update_shortest_paths();
  }
 
  return sp_matrix[a][b];
}

void SpannerGraph::update_shortest_paths() {
  auto floyd = floyd_warshall::floyd_warshall(adj_matrix);
  if (floyd.has_value()) {
    is_shortest_path_updated = true;
    sp_matrix = floyd.value();
  }
}

void SpannerGraph::calculate_euclidean_distances() {
  euclidean_distance = vector<vector<ld>>(N, vector<ld>(N, 0));
  for (int i = 0; i < N; i++) {
    for (int j = i; j < N; j++) {
      euclidean_distance[i][j] = euclidean_distance[j][i] =
        geo_math::distance(convex_points.points[i], convex_points.points[j]);
    }
  }
}
