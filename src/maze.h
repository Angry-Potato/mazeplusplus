#ifndef MAZE_H
#define MAZE_H

class Tile;
class Point;
class Maze {
public :
  int height;
  int width;

  Maze(const int* tileData, int tilesWide, int tilesTall);
  ~Maze();

  bool isFree(int x, int y) const;
  int tile(int x, int y) const;
  int tile(Point* p) const;

  Tile* tiles;
};
#endif
