#ifndef PHYSICS_H
#define PHYSICS_H

class Point;
class Maze;
class Player;
class Physics {
public :
  bool isCollision(Point* playerPos, Point* movement, Maze* maze) const;
  void updatePlayer(Player* player, Maze* maze, int playerCount) const;
};
#endif
