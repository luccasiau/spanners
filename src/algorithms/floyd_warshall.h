#ifndef SPANNERS_SRC_ALGORITHMS_FLOYD_WARSHALL_H
#define SPANNERS_SRC_ALGORITHMS_FLOYD_WARSHALL_H

#include <vector>
#include <optional>

namespace floyd_warshall {

using ld=long double;
using std::vector;
using std::optional;

// Runs Floyd-Warshall algorithm for All-Pairs-Shortest-Paths.
// Inputs:
//   - vector<vector<ld>> adj: adjacency matrix of graph
//   - ld INF [optional]: Threshold for infinity value. Default is 1e18.
// Returns:
//   - Optional<vector<vector<ld>>>:
//   - - Distance matrix for the graph if everything is fine.
//   - - Empty optional if something went wrong.
optional<vector<vector<ld>>> floyd_warshall(
    const vector<vector<ld>>& adj, ld INF=1e18);

}
#endif  // SPANNERS_SRC_ALGORITHMS_FLOYD_WARSHALL_H
