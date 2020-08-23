#ifndef SPANNERS_SRC_MODELS_POINT2D_H
#define SPANNERS_SRC_MODELS_POINT2D_H

using ld=long double;

/**
Class used to represent points in the euclidean plane. Everything is in long
doubles. Equality is checked within a default epsilon of 1e-9.

Naturally, this is also used to represent 2D vectors.
*/
class Point2D {
 public:
  ld x, y;

  Point2D(ld x_=0, ld y_=0): x(x_), y(y_) {}

  // Returns the squared 2-norm of the vector
  ld squared_norm();

  // Returns the 2-norm of the vector
  ld norm();

  bool operator ==(const Point2D& b);
  Point2D operator  -();
  Point2D operator  -(const Point2D& b);

 private:
  const ld EPS=1e-9;
};

#endif // SPANNERS_SRC_MODELS_POINT2D_H
