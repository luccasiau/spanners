// Version 0: Very primitive, I just want to get this working.
// Using Standard IO
// This version is to be used in the jupyter notebook to get the image
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "../algorithms/path_greedy.h"
#include "../models/spanner_graph.h"
#include "../models/convex_points.h"
#include "../models/point2d.h"
#include "../models/geo_math.h"
#define DEBUG false 
using namespace std;
using ld=long double;

constexpr ld PI = 3.1415926535897932384626;
//constexpr ld t = (3 + 4*PI)/3;
constexpr ld t = 2;

int main(int argc, char* argv[]) {
  int N;
  cin >> N;

  vector<Point2D> points(N);
  for (int i = 0; i < N; i++) {
    ld x, y;
    cin >> x >> y;
    points[i] = Point2D(x, y);
  }

  SpannerGraph spanner = path_greedy::path_greedy(ConvexPoints(points), t);

  auto M = spanner.adjacency_matrix();
  cout << N << endl;
  cout << "Planarity: " << (spanner.is_planar()?"":"NOT ") << "PLANAR" << endl;
  cout << "Max degree: " << spanner.max_degree() << endl;

  ld stretch = 1.0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      stretch = max(stretch,
                  spanner.shortest_path(i, j)/spanner.euclidean_distance(i, j));
    }
  }

  cout << "Stretch: " << stretch << endl;
  for (int i = 0; i < M.size(); i++) {
    for (int j = 0; j < (int)M[i].size(); j++) {
      if (M[i][j] && i != j) {
        cout << spanner.point(i).x << " " << spanner.point(i).y << " ";
        cout << spanner.point(j).x << " " << spanner.point(j).y << endl;
      }
    }
  }

  return 0;
}
