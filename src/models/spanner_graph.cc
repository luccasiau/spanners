#include <algorithm>
#include "convex_points.h"
#include "geo_math.h"
#include "spanner_graph.h"
#include "../algorithms/floyd_warshall.h"

// --------------------------------------------------------------
// --------------------------- PUBLIC ---------------------------
// --------------------------------------------------------------

SpannerGraph::SpannerGraph(ConvexPoints points) : m_convex_points(points) {
  N = (int)m_convex_points.points.size();
  num_edges = 0;

  is_shortest_path_updated = false;
  m_degree = vector<int>(N, 0);
  adj_matrix = vector<vector<bool>>(N, vector<bool>(N, false)); 
  for (int i = 0; i < N; i++) adj_matrix[i][i] = true;

  sp_matrix = vector<vector<ld>>(N, vector<ld>(N, INF));

  m_is_planar = true;
  is_planarity_updated = true;

  is_spanning_ratio_updated = false;
  calculate_euclidean_distances();
}

void SpannerGraph::add_edge(int a, int b) {
  if (a < 0 || a >= N || b < 0 || b >= N || a == b) {
    return;
  }
  if (adj_matrix[a][b]) {
    return;
  }

  adj_matrix[a][b] = adj_matrix[b][a] = true; 
  m_degree[a]++;
  m_degree[b]++;
  num_edges++;
  is_shortest_path_updated = false;
  is_spanning_ratio_updated = false;
  m_edge_set.insert({std::min(a, b), std::max(a, b)});

  if (m_is_planar) {
    is_planarity_updated = false;
  }
}

void SpannerGraph::remove_edge(int a, int b) {
  if (a < 0 || a >= N || b < 0 || b >= N || a == b) {
    return;
  }
  if (!adj_matrix[a][b]) {
    return;
  }

  adj_matrix[a][b] = adj_matrix[b][a] = false;
  m_degree[a]--;
  m_degree[b]--;
  num_edges--;
  is_shortest_path_updated = false;
  is_spanning_ratio_updated = false;
  m_edge_set.erase({std::min(a, b), std::max(a, b)});

  if (!m_is_planar) {
    is_planarity_updated = false;
  }
}

ld SpannerGraph::spanning_ratio(bool update_if_needed) {
  if (update_if_needed && !is_spanning_ratio_updated) {
    update_spanning_ratio();
  }

  return m_spanning_ratio;
}

ld SpannerGraph::shortest_path(int a, int b, bool update_if_needed) {
  if (a < 0 || a >= N || b < 0 || b >= N) {
    return INF;
  } 
  if (update_if_needed && !is_shortest_path_updated) {
    update_shortest_paths();
  }
 
  return sp_matrix[a][b];
}

bool SpannerGraph::is_planar(bool update_if_needed) {
  if (update_if_needed && is_planarity_updated) {
    update_planarity();
  }
  return m_is_planar;
}

int SpannerGraph::degree(int x) {
  if (x < 0 || x >= N) {
    return -1;
  }
  return m_degree[x];
}

ld SpannerGraph::euclidean_distance(int a, int b) {
  if (a < 0 || a >= N || b < 0 || b >= N) {
    return -1;
  }
  return m_euclidean_distance[a][b];
}

int SpannerGraph::size() {
  return N;
}

int SpannerGraph::number_edges() {
  return num_edges;
}

vector<vector<bool>> SpannerGraph::adjacency_matrix() {
  return adj_matrix;
}

std::set<std::pair<int, int>> SpannerGraph::edge_set() {
  return m_edge_set;
}

Point2D SpannerGraph::point(int i) {
  i %= N;
  if (i < 0) {
    i += N;
  }
  return m_convex_points.points[i];
}

ConvexPoints SpannerGraph::convex_points() {
  return m_convex_points;
}

int SpannerGraph::max_degree() {
  int ret = 0;
  for (int i = 0; i < N; i++) {
    ret = std::max(ret, m_degree[i]);
  }
  return ret;
}

// -----------------------------------------------------------
// ------------------------- PRIVATE -------------------------
// -----------------------------------------------------------
void SpannerGraph::calculate_euclidean_distances() {
  m_euclidean_distance = vector<vector<ld>>(N, vector<ld>(N, 0));
  for (int i = 0; i < N; i++) {
    for (int j = i; j < N; j++) {
      m_euclidean_distance[i][j] = m_euclidean_distance[j][i] =
        geo_math::distance(m_convex_points.points[i], m_convex_points.points[j]);
    }
  }
}

void SpannerGraph::update_spanning_ratio() {
  if (!is_shortest_path_updated) {
    update_shortest_paths();
  }

  is_spanning_ratio_updated = true;
  m_spanning_ratio = 0.0;
  for (int i = 0; i < N; i++) {
    for (int j = i+1; j < N; j++) {
      if (sp_matrix[i][j] > INF-0.1) {
        m_spanning_ratio = INF;
        return;
      }

      m_spanning_ratio = std::max(m_spanning_ratio,
                           sp_matrix[i][j]/m_euclidean_distance[i][j]);
    }
  }
}

void SpannerGraph::update_shortest_paths() {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      sp_matrix[i][j] = adj_matrix[i][j] ? m_euclidean_distance[i][j] : INF;
    }
  }
  auto floyd = floyd_warshall::floyd_warshall(sp_matrix);
  if (floyd.has_value()) {
    is_shortest_path_updated = true;
    sp_matrix = floyd.value();
  }
}

void SpannerGraph::update_planarity() {
  is_planarity_updated = true;
  for (auto it_i = m_edge_set.begin(); it_i != m_edge_set.end(); it_i++) {
    for (auto it_j = it_i; it_j != m_edge_set.end(); it_j++) {
      auto seg1 = std::make_pair(m_convex_points.points[it_i->first],
                                 m_convex_points.points[it_i->second]);
      auto seg2 = std::make_pair(m_convex_points.points[it_j->first],
                                 m_convex_points.points[it_j->second]);
      if (geo_math::seg_x_seg(seg1, seg2, false)) {
        m_is_planar = false;
        return;
      }
    }
  }
  m_is_planar = true;
}
