#ifndef TILE_H
#define TILE_H

#include "point.h"

enum TileType {
  FREE,
  TOP_LEFT_CORNER,
  HORIZONTAL_WALL,
  TOP_RIGHT_CORNER,
  VERTICAL_WALL,
  BOTTOM_RIGHT_CORNER,
  BOTTOM_LEFT_CORNER
};

struct Tile {
  Point* position;
  TileType type;

  Tile(TileType tileType = FREE, int x = 0, int y = 0) {
    type = tileType;
    position = new Point(x, y);
  }
  ~Tile() {
    delete position;
  }

  bool isFree() const { return type == FREE; }
};
#endif
