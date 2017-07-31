#include "physics.h"
#include "point.h"
#include "maze.h"
#include "tile.h"
#include "player.h"
#include <iostream>

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

void Physics::updatePlayers(Player* players, Maze* maze, int playerCount) const {
  for (int i = 0; i < playerCount; i++) {
    Point movement = players[i].velocity();
    if (isCollision(players[i].previousPosition, &movement, maze)) {
      players[i].returnToPreviousPosition();
    }
    else {
    // std::cout << "playerpos: " << players[i].position->X << ", " << players[i].position->Y << std::endl;
      players[i].updatePosition();
    }
  }
}
