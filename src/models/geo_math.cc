#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include "geo_math.h"

ld geo_math::cross(Point2D a, Point2D b) {
  return a.x * b.y - a.y * b.x;
}

ld geo_math::dot(Point2D a, Point2D b) {
  return a.x * b.x + a.y * b.y;
}

ld geo_math::distance(Point2D a, Point2D b) {
  return (a-b).norm();
}

ld geo_math::sq_distance(Point2D a, Point2D b) {
  return (a-b).squared_norm();
}

bool geo_math::colinear(Point2D a, Point2D b, Point2D c, ld epsilon) {
  return abs(cross(b-a, c-a)) < epsilon;
}

bool geo_math::ccw(Point2D a, Point2D b, Point2D c, ld epsilon) {
  return cross(b-a, c-a) > epsilon;
}

bool geo_math::within_segment(Point2D p, std::pair<Point2D, Point2D> seg,
    bool include_endpoints, ld eps) {
  if (p == seg.first || p == seg.second) {
    return include_endpoints;
  }
  return abs(distance(seg.first, seg.second) - distance(seg.first, p)
      - distance(seg.second, p)) < eps;
}

// Not my proudest implementation, but at least I understand it.
bool geo_math::seg_x_seg(std::pair<Point2D, Point2D> seg1,
        std::pair<Point2D, Point2D> seg2, bool include_endpoints, ld eps) {
  Point2D a = seg1.first;
  Point2D b = seg1.second;
  Point2D c = seg2.first;
  Point2D d = seg2.second;
  
  if (include_endpoints) { 
    if (within_segment(a, seg2) || within_segment(b, seg2)) {
      return true;
    }
    if (within_segment(c, seg1) || within_segment(d, seg1)) {
      return true;
    }
  }

  int total_colinearities=0;
  if (colinear(a, b, c)) total_colinearities++;
  if (colinear(a, b, d)) total_colinearities++;
  if (colinear(a, c, d)) total_colinearities++;
  if (colinear(b, c, d)) total_colinearities++;

  // All four points in a line
  if (total_colinearities == 4) {
    if (within_segment(c, seg1, false) || within_segment(d, seg1, false)) {
      return true;
    }
    if (within_segment(a, seg2, false) || within_segment(b, seg2, false)) {
      return true;
    }
    return false;
  }
  // This means there's a line with 3 points, but not all of them. The relevant
  // case would have been caught above. So anything here means no intersection.
  else if (total_colinearities > 0) {
    return false;
  }

  // Non-Colinear case (phew)
  if (ccw(a, c, d) == ccw(b, c, d)) return false;
  if (ccw(c, a, b) == ccw(d, a, b)) return false;
  return true;
}
