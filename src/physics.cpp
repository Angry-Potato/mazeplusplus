#include "physics.h"
#include "point.h"
#include "maze.h"
#include "tile.h"
#include "player.h"

bool Physics::isCollision(Point* playerPos, Point* movement, Maze* maze) const {
  Point futurePos = *playerPos + *movement;
  int magnitude = movement->magnitude();
  int count = 0;
  Point progression;
  while (count < magnitude) {
    progression.X += progression.X != movement->X ? (playerPos->X < futurePos.X ? 1 : -1) : 0;
    progression.Y += progression.Y != movement->Y ? (playerPos->Y < futurePos.Y ? 1 : -1) : 0;
    Point pointOnPath = *playerPos + progression;
    if (maze->tile(&pointOnPath) != Tile::FREE &&
        maze->tile(&pointOnPath) != Tile::PLAYER_SPAWN &&
        maze->tile(&pointOnPath) != Tile::FINISH) {
      return true;
    }

    count++;
  }
  return false;
}

void Physics::updatePlayer(Player* player, Maze* maze) const {
  Point movement = player->velocity();
  if (isCollision(player->previousPosition, &movement, maze)) {
    player->returnToPreviousPosition();
  }
  else {
    player->updatePosition();
  }
}
