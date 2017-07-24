#include "tile_view.h"
#include "libtcod.hpp"

int TileView::characterCode(TileType type) {
  switch (type) {
    case FREE: return 0;
    case TOP_LEFT_CORNER: return 201;
    case HORIZONTAL_WALL: return 205;
    case TOP_RIGHT_CORNER: return 187;
    case VERTICAL_WALL: return 186;
    case BOTTOM_RIGHT_CORNER: return 188;
    case BOTTOM_LEFT_CORNER: return 200;
    default: return 0;
  }
}
