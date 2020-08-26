// Version 0: Very primitive, I just want to get this working.
// Using Standard IO
#include <algorithm>
#include <iostream>
#include <vector>
#include "../algorithms/path_greedy.h"
#include "../models/spanner_graph.h"
#include "../models/convex_points.h"
#include "../models/point2d.h"
#include "../models/geo_math.h"
using namespace std;
using ld=long double;

constexpr ld PI = 3.1415926535897932384626;
constexpr ld t = (3 + 4*PI)/3;

int main() {
  int N;
  cin >> N;

  vector<Point2D> points(N);
  for (int i = 0; i < N; i++) {
    ld x, y;
    cin >> x >> y;
    points[i] = Point2D(x, y);
  }

  SpannerGraph spanner = path_greedy::path_greedy(ConvexPoints(points), t);

  cout << "Spanner from PathGreedy with t = " << t << endl;
  cout << "#nodes: " << spanner.size() << endl;
  cout << "#edges: " << spanner.number_edges() << endl;
  cout << "----Nodes' degrees----" << endl;
  for (int i = 0; i < spanner.size(); i++) {
    cout << "degree(" << i << ") = " << spanner.degree(i) << endl;
  }
  cout << "----------------------" << endl;
  cout << "Adjacency matrix:" << endl;
  auto M = spanner.adjacency_matrix();
  cout << " ";
  for (int i = 0; i < spanner.size(); i++) cout << " " << i;
  cout << endl;
  for (int i = 0; i < (int)M.size(); i++) {
    cout << i;
    for (int j = 0; j < (int)M[i].size(); j++) {
      if (M[i][j] && i != j) cout << " T";
      else cout << "  ";
    }
    cout << endl;
  }

  return 0;
}
