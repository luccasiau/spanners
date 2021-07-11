#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include "../algorithms/general_path_greedy.h"
#include "../models/spanner_graph.h"
#include "../models/convex_points.h"
#include "../models/point2d.h"
#include "../models/geo_math.h"
#define DEBUG false 
using namespace std;
using ld=long double;

void printSpannerInfo(SpannerGraph spanner, int ttt, double t_ratio) {
  int N = spanner.size();
  auto M = spanner.adjacency_matrix();
  cout << N << endl;
  cout << "Planarity: " << (spanner.is_planar()?"":"NOT ") << "PLANAR" << endl;
  cout << "Iterations taken: " << ttt << endl;

  ld stretch = 1.0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      stretch = max(stretch,
                  spanner.shortest_path(i, j)/spanner.euclidean_distance(i, j));
    }
  }

  cout << "t = " << t_ratio << "; Stretch: " << stretch << endl;
  for (int i = 0; i < M.size(); i++) {
    for (int j = 0; j < (int)M[i].size(); j++) {
      if (M[i][j] && i != j) {
        cout << spanner.point(i).x << " " << spanner.point(i).y << " ";
        cout << spanner.point(j).x << " " << spanner.point(j).y << endl;
      }
    }
  }
}

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

  int N = 5;
  int T = 1000; // upper bound on the number of tries

  if (argc >= 3) {
    N = stoi(argv[2]);
  }
  if (argc >= 4) {
    T = stoi(argv[3]);
  }

  vector<Point2D> points(N*N);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      points[i*N + j] = Point2D(i, j);
    }    
  }

  vector<tuple<int, int>> beforeEdges, afterEdges;

  int numPlanar = 0;

  cout.precision(2);
  cerr.precision(2);
 
  srand(time(NULL));
  for (int ttt = 1; ttt <= T; ttt++) {
    srand(rand() + ttt);
    SpannerGraph trySpanner = general_path_greedy::general_path_greedy(
      SpannerGraph(ConvexPoints(points)),
      t_ratio,
      beforeEdges,
      afterEdges,
      true);
    
    if (!trySpanner.is_planar()) {
      cerr << "Found one in " << ttt << " iterations" << endl;
      printSpannerInfo(trySpanner, ttt, t_ratio);
      return 0;
    }
    
    if (ttt % 100 == 0) {
      cerr << ttt << " iterations passed" << endl;
    }
  }
  
  cout << N << endl;
  cout << "t = " << t_ratio << endl;
  cout << T << " iterations" << endl;
  cout << "no non-planar spanner found" << endl;
  // sad face

  // eyes
  cout << "0 0 0 0" << endl;
  cout << "2 0 2 0" << endl;

  // frown
  cout << "0 2 1 1" << endl;  
  cout << "2 2 1 1" << endl;

  return 0;
}
