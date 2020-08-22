#include <iostream>
#include "geo_math.h"
#include "point2d.h"

int main() {
  ld x1, y1;
  ld x2, y2;

  std::cin >> x1 >> y1 >> x2 >> y2;

  Point2D p1 = Point2D(x1, y1);
  Point2D p2 = Point2D(x2, y2);

  std::cout << "C " << geo_math::cross(p1, p2) << std::endl;
  std::cout << "D " << geo_math::dot(p1, p2) << std::endl;
  std::cout << "Di " << geo_math::distance(p1, p2) << std::endl;
  std::cout << "Di2 " << geo_math::sq_distance(p1, p2) << std::endl;

  return 0;
}
