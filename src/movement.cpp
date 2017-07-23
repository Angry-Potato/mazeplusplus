#include "point.h"
#include "movement.h"

void Movement::move(Point* point, Point* amount) const {
  point->X += amount->X;
  point->Y += amount->Y;
}
