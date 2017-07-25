#include "cell.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

void Cell::init(const int y, const int x, const int walls) {
    setPosition(y, x);
    setWalls(walls);
}
Cell::Cell() { init(0, 0, 0); }
Cell::Cell(const int y, const int x) { init(y, x, 0); }
Cell::Cell(const int y, const int x, const int walls) { init(y, x, walls); }

void Cell::removeWall(const int w) {
    if (w!=WALL_NORTH && w!=WALL_EAST && w!=WALL_SOUTH && w!=WALL_WEST)
        throw std::string("Illegal wall argument");
    walls &= ~w;
}
int Cell::getWalls() const { return walls & WALL_ALL; }
void Cell::setWalls(const int w) { walls = w & WALL_ALL; }
void Cell::setPosition(const int y, const int x) { Y = y; X = x; }


std::ostream& operator<<(std::ostream& strm, const Cell& c) {
            if ((c.getWalls() & Cell::WALL_WEST) != 0) strm << '|';
            else strm << ' ';
            if ((c.getWalls() & Cell::WALL_SOUTH) != 0) strm << '_';
            else strm << ' ';

    return strm;
}
