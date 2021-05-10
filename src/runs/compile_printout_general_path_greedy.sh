#!/bin/bash
# Temporary and for personal convenience while I don't prepare a CMake file. (ha)
g++ -O2 --std=c++17 printout_general_path_greedy_test.cc ../models/geo_math.cc ../models/convex_points.cc ../models/spanner_graph.cc ../models/point2d.cc ../algorithms/general_path_greedy.cc ../algorithms/floyd_warshall.cc -o printout_general_path_greedy_test
