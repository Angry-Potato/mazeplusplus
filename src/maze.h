#ifndef MAZE_H
#define MAZE_H

class Tile;
class Maze {
public :
  int height;
  int width;

  Maze(const int* tileData, int tilesWide, int tilesTall);
  ~Maze();

  bool isFree(int x, int y) const;
  int tile(int x, int y) const;

  Tile* tiles;
};
#endif
