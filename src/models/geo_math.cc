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
