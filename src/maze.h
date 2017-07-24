#include "tile.h"

class Maze {
public :
  int height;
  int width;

  Maze(const int* tileData, int rows, int cols);
  ~Maze();

  bool isFree(int x, int y) const;
  TileType tile(int x, int y) const;

  Tile* tiles;
};
