#include "physics.h"
#include "point.h"
#include "maze.h"
#include "tile.h"

bool Physics::isCollision(Point* playerPos, Point* movement, Maze* maze) const {
  Point futurePos = *playerPos + *movement;
  int magnitude = movement->magnitude();
  int count = 0;
  Point progression;
  while (count < magnitude) {
    progression.X += progression.X != movement->X ? (playerPos->X < movement->X ? 1 : -1) : 0;
    progression.Y += progression.Y != movement->Y ? (playerPos->Y < movement->Y ? 1 : -1) : 0;
    Point pointOnPath = *playerPos + progression;
    if (maze->tile(&pointOnPath) != Tile::FREE) {
      return true;
    }

    count++;
  }
  return false;
}
