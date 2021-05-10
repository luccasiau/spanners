// Run ./printout_genereal_path_greedy_test t_ratio

// Version 1: Still primitive, I just want to get this working.
// Using Standard IO
// This version is to be used in the jupyter notebook to get the image
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "../algorithms/general_path_greedy.h"
#include "../models/spanner_graph.h"
#include "../models/convex_points.h"
#include "../models/point2d.h"
#include "../models/geo_math.h"
#define DEBUG false 
using namespace std;
using ld=long double;

int main(int argc, char* argv[]) {
  if (argc < 2) {
    cerr << "ERROR: Must specify t-ratio" << endl;
    exit(1);
  }

  ld t_ratio;
  try {
    t_ratio = stod(argv[1]);
  } catch (const std::invalid_argument& ia) {
    cerr << "EXCEPTION: parsing t-ratio: " << ia.what() << endl;
    exit(1);
  }

  cerr << "t-ratio: " << t_ratio << endl;

  int N, eBefore, eAfter;
  cin >> N >> eBefore >> eAfter;

  vector<Point2D> points(N);
  for (int i = 0; i < N; i++) {
    ld x, y;
    cin >> x >> y;
    points[i] = Point2D(x, y);
  }

  vector<tuple<int, int>> beforeEdges, afterEdges;
  for (int i = 0; i < eBefore; i++) {
    int a, b;
    cin >> a >> b;
    beforeEdges.push_back(make_tuple(a, b));
  }
  for (int i = 0; i < eAfter; i++) {
    int a, b;
    cin >> a >> b;
    afterEdges.push_back(make_tuple(a, b));
  }

  cerr << beforeEdges.size() << " " << afterEdges.size() << endl;

  SpannerGraph spanner = general_path_greedy::general_path_greedy(
    SpannerGraph(ConvexPoints(points)), t_ratio, beforeEdges, afterEdges);

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