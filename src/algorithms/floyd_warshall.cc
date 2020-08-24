#include <algorithm>
#include "floyd_warshall.h"

using ld=long double;

std::optional<std::vector<std::vector<ld>>> floyd_warshall::floyd_warshall(
    const std::vector<std::vector<ld>>& adj, ld INF) { 
  // Check if adj is a square
  int N = (int)adj.size();
  for (auto& row : adj) {
    if ((int)row.size() != N) {
      return {};
    }
  }

  // adj is a square
  std::vector<std::vector<ld>> dist = adj;
  for (int k = 0; k < N; k++) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }

  return dist;
}

