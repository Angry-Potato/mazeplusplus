#include "cell.h"

void Cell::init(const int y, const int x, const int walls) {
    setPosition(y, x);
    setWalls(walls);
}
Cell::Cell() { init(0, 0, 0); }
Cell::Cell(const int y, const int x) { init(y, x, 0); }
Cell::Cell(const int y, const int x, const int walls) { init(y, x, walls); }

void Cell::removeWall(const int w) {
    if (w!=WALL_NORTH && w!=WALL_EAST && w!=WALL_SOUTH && w!=WALL_WEST)
        throw "Illegal wall argument";
    walls &= ~w;
}
int Cell::getWalls() const { return walls & WALL_ALL; }
void Cell::setWalls(const int w) { walls = w & WALL_ALL; }
void Cell::setPosition(const int y, const int x) { Y = y; X = x; }
