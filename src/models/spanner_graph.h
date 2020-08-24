#ifndef SPANNERS_SRC_MODELS_SPANNER_GRAPH_H
#define SPANNERS_SRC_MODELS_SPANNER_GRAPH_H

#include <vector>
#include "convex_points.h"

using ld=long double;
using std::vector;

// Representation of a spanner graph of points in convex position
// in R^2. The points are indexed from 0 to N-1.
class SpannerGraph {
 public:
  SpannerGraph(ConvexPoints points);

  // Adds an edge between vertices a and b. The weight of the edge will be their
  // Euclidean distance. This also sets the "updated" booleans to false.
  // Silently ignored if there is a pre-existing edge.
  // Silently ignored if a and b are not in [0, N)
  // Silently ignored if a == b
  void add_edge(int a, int b);

  // Removes an edge between vertices a and b.
  // This also sets the "updated" booleans to false.
  // Silently ignored if there's no edge.
  // Silently ignored if a and b are not in [0, N)
  // Silently ignored if a == b
  void remove_edge(int a, int b);

  // Returns the spanning ratio.
  // Input:
  //  - bool update_if_needed [default=true]: if there have been changes to the
  //  graph since the last time the spanning ratio was calculated, it will
  //  first update the spanning ratio.
  //  If two vertices are not connected, the spanning ratio will be infinity.
  ld spanning_ratio(bool update_if_needed=true);

  // Updates spanning ratio.
  void update_spanning_ratio();

  // Returns the shortest path between node. Recalculates ALL PAIRS to
  // update distance if needed.
  // Input:
  //  - bool update_if_needed [default=true]: If there have been changes to
  //  the graph since the last calculation, it will recalculate ALL shortest
  //  paths in the graph using Floyd-Warshall.
  // Returns infinity if a and b are not in [0, N).
  ld shortest_path(int a, int b, bool update_if_needed=true);

  // Recalculates shortest distance between all pairs.
  void update_shortest_paths();

  // Returns the degree of vertex x.
  // If x is not in [0, N), it will return the invalid degree of -1.
  int degree(int x);

  // Returns the Euclidean distance between vertices a and b.
  // If a or b are not in [0, N), it will return the invalid distance of -1.
  ld euclidean_distance(int a, int b);

  // TODO: Add the functions I need to get info about the graph 
  // Some of them are: getN, getEdges...
  int size();

  // Returns the number of bidirectional edges.
  int number_edges();

  // Returns BOOLEAN adjacency matrix. True indicating whether two points
  // are connected (by an edge with their Euclidean distance)
  vector<vector<bool>> adjacency_matrix();

 private:
  const ld INF=1e18;

  int N;
  int num_edges;
  ConvexPoints convex_points;

  bool is_shortest_path_updated;
  vector<int> m_degree;
  // adj_matrix[i][j] is true if the two nodes are connected. If they are, the
  // distance will be denominated by euclidean_distance.
  vector<vector<bool>> adj_matrix;
  vector<vector<ld>> sp_matrix;

  vector<vector<ld>> m_euclidean_distance;

  bool is_spanning_ratio_updated;
  ld m_spanning_ratio;

  // Calculates all-pairs of euclidean distances and caches it. This avoid
  // repeatedly calculating the same distances.
  void calculate_euclidean_distances();
};

#endif  // SPANNERS_SRC_MODELS_SPANNER_GRAPH_H
