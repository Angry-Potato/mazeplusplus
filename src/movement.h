#ifndef MOVEMENT_H
#define MOVEMENT_H

class Point;
class Movement {
public :
  void move(Point* point, Point* amount) const;
};
#endif
