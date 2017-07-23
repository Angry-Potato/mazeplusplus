#include "point.h"

struct Player {
   Point position;
   Point previousPosition;
   Player(int x = 0, int y = 0) : position(x, y), previousPosition(x, y) {}
};
