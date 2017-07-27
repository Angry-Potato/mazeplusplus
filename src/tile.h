#ifndef TILE_H
#define TILE_H

#include "point.h"

struct Tile {
  enum TileType {
    FREE,
    TOP_LEFT_CORNER,
    HORIZONTAL_WALL,
    TOP_RIGHT_CORNER,
    VERTICAL_WALL,
    BOTTOM_RIGHT_CORNER,
    BOTTOM_LEFT_CORNER,
    T_JUNCTION,
    INVERTED_T_JUNCTION,
    LEFT_T_JUNCTION,
    RIGHT_T_JUNCTION,
    CROSSROADS,
    PLAYER_SPAWN,
    FINISH
  };

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
