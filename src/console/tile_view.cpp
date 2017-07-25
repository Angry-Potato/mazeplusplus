#include "tile_view.h"
#include "../tile.h"
#include "libtcod.hpp"

int TileView::characterCode(int type) {
  switch ((Tile::TileType)type) {
    case Tile::FREE: return 0;
    case Tile::TOP_LEFT_CORNER: return 201;
    case Tile::INVERTED_T_JUNCTION: return 202;
    case Tile::T_JUNCTION: return 203;
    case Tile::HORIZONTAL_WALL: return 205;
    case Tile::TOP_RIGHT_CORNER: return 187;
    case Tile::LEFT_T_JUNCTION: return 185;
    case Tile::RIGHT_T_JUNCTION: return 204;
    case Tile::CROSSROADS: return 206;
    case Tile::VERTICAL_WALL: return 186;
    case Tile::BOTTOM_RIGHT_CORNER: return 188;
    case Tile::BOTTOM_LEFT_CORNER: return 200;
    default: return 0;
  }
}
