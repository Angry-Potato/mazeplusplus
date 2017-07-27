#ifndef POINT_H
#define POINT_H

#include <math.h>

struct Point {
  int X;
  int Y;
  Point(int x = 0, int y = 0) : X(x), Y(y) {}

  inline int magnitude() const {
    return sqrt(X*X + Y*Y);
  };

  friend Point operator+(Point lhs, const Point& rhs) {
    lhs.X += rhs.X;
    lhs.Y += rhs.Y;
    return lhs;
  }

  friend Point operator-(Point lhs, const Point& rhs) {
    lhs.X -= rhs.X;
    lhs.Y -= rhs.Y;
    return lhs;
  }
};
#endif
