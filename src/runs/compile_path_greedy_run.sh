#!/bin/bash
# Temporary and for personal convenience while I don't prepare a CMake file.
g++ -O2 --std=c++17 path_greedy_test.cc ../models/geo_math.cc ../models/convex_points.cc ../models/spanner_graph.cc ../models/point2d.cc ../algorithms/path_greedy.cc ../algorithms/floyd_warshall.cc -o path_greedy_test
