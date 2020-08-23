#include "floyd_warshall.h"

optional<vector<vector<ld>>> floyd_warshall::floyd_warshall(
    const vector<vector<ld>>& adj, ld INF) { 
  // Check if adj is a square
  int N = (int)adj.size();
  for (auto& row : adj) {
    if ((int)row.size() != N) {
      return {};
    }
  }

  // adj is a square
  vector<vector<ld>> dist = adj;
  for (int k = 0; k < N; k++) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }

  return dist;
}

