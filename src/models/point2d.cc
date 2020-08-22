#include <algorithm>
#include <cmath>
#include "point2d.h"

ld Point2D::squared_norm() {
  return x*x + y*y;
}


ld Point2D::norm() {
  return sqrt(x*x + y*y);
}


bool Point2D::operator ==(const Point2D& b) {
  return std::abs(x - b.x) < EPS && std::abs(y - b.y) < EPS;
}


Point2D Point2D::operator -() {
  return Point2D(-x, -y);
}

Point2D Point2D::operator -(const Point2D& b) {
  return Point2D(x - b.x, y - b.y);
}
