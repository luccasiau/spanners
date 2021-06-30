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
  int T = 1000;

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

  for (int ttt = 1; ttt <= T; ttt++) {
    srand(ttt);
    SpannerGraph spanner = general_path_greedy::general_path_greedy(
      SpannerGraph(ConvexPoints(points)),
      t_ratio,
      beforeEdges,
      afterEdges,
      true);

    numPlanar += spanner.is_planar();
    if (ttt % 100 == 0) {
      cerr << ttt << " iterations passed" << endl;
      cerr << "Planar cases: " << numPlanar << " (" << fixed <<
        (double(numPlanar*100)/ttt) << "%)" << endl;
      cerr << "Non-Planar cases: " << (ttt-numPlanar) << " (" << fixed <<
        (double((ttt-numPlanar)*100)/ttt) << "%)" << endl;
    }
  }

  cout << "---------------------------------------------" << endl;
  cout << N << 'x' << N << " grid\nT = " << T << " iterations" << endl;

  cout << "Planar cases: " << numPlanar << " (" << fixed <<
        (double(numPlanar*100)/T) << "%)" << endl;
  cout << "t-ratio: " << fixed << t_ratio << endl;
  cout << "Non-Planar cases: " << (T-numPlanar) << " (" << fixed <<
        (double((T-numPlanar)*100)/T) << "%)" << endl;

  return 0;
}