#ifndef MAZEGEN_H
#define MAZEGEN_H

class Cell;
class Mazegen {
public :
  enum DIR { NORTH = 0x0008, SOUTH = 0x0002, EAST = 0x0004, WEST = 0x0001};
  int opposite(int dir) const;
  inline int locate(int x, int y, int width) const { return x+y*width; };
  void gen(int width, int height);
  void prepMaze(Cell* cells, int width, int height);
  Cell* cellNeighbour(Cell* cells, int width, int height, int x, int y, int dir) const;
  bool isDirAvailable(Cell* cells, int width, int height, int x, int y, int dir) const;
  void forgePath(Cell* cells, int x, int y, int width, int height, int dir);
};
#endif
