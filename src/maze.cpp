#include "maze.h"
#include "tile.h"

Maze::Maze(int* tileData, int rows, int cols) {
  height = rows;
  width = cols;
  tiles=new Tile[width*height];
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      tiles[x+y*width].position->X = x;
      tiles[x+y*width].position->Y = y;
      tiles[x+y*width].type = (TileType)tileData[x+y*width];
    }
  }
}

Maze::~Maze() {
   delete [] tiles;
}

bool Maze::isFree(int x, int y) const {
   return tiles[x+y*width].isFree();
}

TileType Maze::tile(int x, int y) const {
   return tiles[x+y*width].type;
}
