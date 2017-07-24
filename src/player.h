#ifndef PLAYER_H
#define PLAYER_H

#include "point.h"

struct Player {
  int id;
  Point* position;
  Point* previousPosition;
  Player(int playerId = 0, int x = 0, int y = 0) {
    id = playerId;
    position = new Point(x, y);
    previousPosition = new Point(x, y);
  }
  ~Player() {
    delete position;
    delete previousPosition;
  }
};
#endif
