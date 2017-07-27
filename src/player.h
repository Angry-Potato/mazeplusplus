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

  inline void updatePosition() {
    previousPosition->X = position->X;
    previousPosition->Y = position->Y;
  };
  inline void returnToPreviousPosition() {
    position->X = previousPosition->X;
    position->Y = previousPosition->Y;
  };
  Point velocity() {
    Point v;
    v.X = position->X - previousPosition->X;
    v.Y = position->Y - previousPosition->Y;
    return v;
  }
};
#endif
