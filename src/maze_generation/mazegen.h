#ifndef MAZEGEN_H
#define MAZEGEN_H

class Cell;
class Mazegen {
public :
  enum DIR { NORTH, SOUTH, EAST, WEST };
  void gen(int width, int height);
  void prepMaze(Cell* cells, int width, int height);
  Cell* cellNeighbour(Cell* cells, int width, int height, int x, int y, int dir);
  bool isDirAvailable(Cell* cells, int width, int height, int x, int y, int dir);
};
#endif
