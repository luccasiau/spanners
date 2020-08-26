#ifndef SPANNERS_SRC_MODELS_SPANNER_GRAPH_H
#define SPANNERS_SRC_MODELS_SPANNER_GRAPH_H

#include <algorithm>
#include <set>
#include <vector>
#include "convex_points.h"
#include "point2d.h"

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

  // Returns the shortest path between node. Recalculates ALL PAIRS to
  // update distance if needed.
  // Input:
  //  - bool update_if_needed [default=true]: If there have been changes to
  //  the graph since the last calculation, it will recalculate ALL shortest
  //  paths in the graph using Floyd-Warshall.
  // Returns infinity if a and b are not in [0, N).
  ld shortest_path(int a, int b, bool update_if_needed=true);

  // Returns the planarity of the graph.
  // Input:
  //  - bool update_if_needed [default=true]: if there have been any changes to
  // the graph that could have altered the planarity from the last time it was
  // calculated and update_if_needed is true, it will first recalculate the
  // graph's planarity.
  bool is_planar(bool update_if_needed=true);

  // Returns the degree of vertex x.
  // If x is not in [0, N), it will return the invalid degree of -1.
  int degree(int x);

  // Returns the Euclidean distance between vertices a and b.
  // If a or b are not in [0, N), it will return the invalid distance of -1.
  ld euclidean_distance(int a, int b);

  // Returns number of nodes in the graph.
  int size();

  // Returns the number of bidirectional edges.
  int number_edges();

  // Returns BOOLEAN adjacency matrix. True indicating whether two points
  // are connected (by an edge with their Euclidean distance)
  vector<vector<bool>> adjacency_matrix();

  // Returns SET of PAIRS of edges.
  std::set<std::pair<int, int>> edge_set();

  // Return the point of index i
  // If i is not in [0, N), it will mod it to be there. This might be handy, or
  // I might regret it. Only time will tell.
  Point2D point(int i);

  // Return the set of convex points
  ConvexPoints convex_points();

  // Returns (in linear time) the maximum of all degrees.
  int max_degree();

 private:
  const ld INF=1e18;

  int N;
  int num_edges;
  ConvexPoints m_convex_points;

  bool is_shortest_path_updated;
  vector<int> m_degree;
  // FIXME: Change this to an unordered_set with a default hash function.
  std::set<std::pair<int, int>> m_edge_set;
  // adj_matrix[i][j] is true if the two nodes are connected. If they are, the
  // distance will be denominated by euclidean_distance.
  vector<vector<bool>> adj_matrix;
  vector<vector<ld>> sp_matrix;

  vector<vector<ld>> m_euclidean_distance;

  bool is_spanning_ratio_updated;
  ld m_spanning_ratio;

  bool is_planarity_updated;
  bool m_is_planar;
 
  // Updates spanning ratio.
  void update_spanning_ratio();

  // Recalculates shortest distance between all pairs.
  void update_shortest_paths();

  // Calculates all-pairs of euclidean distances and caches it. This avoid
  // repeatedly calculating the same distances.
  void calculate_euclidean_distances();

  void update_planarity();
};

#endif  // SPANNERS_SRC_MODELS_SPANNER_GRAPH_H
