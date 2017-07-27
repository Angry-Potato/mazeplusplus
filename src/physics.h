#ifndef PHYSICS_H
#define PHYSICS_H

class Point;
class Maze;
class Physics {
public :
  bool isCollision(Point* playerPos, Point* movement, Maze* maze) const;
};
#endif
