#ifndef MAZEGEN_H
#define MAZEGEN_H

#include <vector>

class Cell;
class Mazegen {
public :
  enum DIR { NORTH = 0x0008, SOUTH = 0x0002, EAST = 0x0004, WEST = 0x0001};
  int opposite(int dir) const;
  static inline int locate(int x, int y, int width) { return x+y*width; };
  void generate(int width, int height, Cell* cells);
  void prepMaze(Cell* cells, int width, int height);
  void genMaze(Cell* cells, int width, int height);
  Cell* cellNeighbour(Cell* cells, int width, int height, int x, int y, int dir) const;
  bool isDirAvailable(Cell* cells, int width, int height, int x, int y, int dir) const;
  Cell* forgePath(Cell* cells, int x, int y, int width, int height, int dir);
  void setAvailableDirs(std::vector<DIR> &availableDirs, Cell* cells, int x, int y, int width, int height);
};
#endif
