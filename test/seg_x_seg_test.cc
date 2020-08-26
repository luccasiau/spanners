// I know this is not the best way to do testing. A proper testing suite is
// something I intend to work on. For now, I really need something to test my
// version of seg_x_seg.
#include <cassert>
#include <iostream>
#include "../src/models/geo_math.h"
using namespace std;
using namespace geo_math;

int main() {
  
  assert(seg_x_seg({Point2D(0, 0), Point2D(1, 1)},
                   {Point2D(1, 0), Point2D(0, 1)}) == true);

  assert(seg_x_seg({Point2D(0, 0), Point2D(0, 2)},
                   {Point2D(0, 1), Point2D(0, 3)}) == true);

  assert(seg_x_seg({Point2D(0, 0), Point2D(5, 5)},
                   {Point2D(3, 2), Point2D(4, 1)}) == false);

  assert(seg_x_seg({Point2D(0, 0), Point2D(5, 5)},
                   {Point2D(3, 3), Point2D(3, 4)}) == true);

  assert(seg_x_seg({Point2D(0, 0), Point2D(5, 5)},
                   {Point2D(3, 3), Point2D(3, 4)}, false) == false);

  assert(seg_x_seg({Point2D(0, 0), Point2D(10, 10)},
                   {Point2D(0, 0), Point2D(-1, -1)}) == true);

  assert(seg_x_seg({Point2D(0, 0), Point2D(10, 10)},
                   {Point2D(0, 0), Point2D(-1, -1)}, false) == false);

  assert(seg_x_seg({Point2D(3, 3), Point2D(5, 1)},
                   {Point2D(6, 0), Point2D(6, -1)}) == false);

  assert(seg_x_seg({Point2D(3, 3), Point2D(5, 1)},
                   {Point2D(6, 0), Point2D(6, -1)}, false) == false);

  cerr << "All assertions passed." << endl;

  return 0;
}
