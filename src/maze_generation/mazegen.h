#ifndef MAZEGEN_H
#define MAZEGEN_H

class Cell;
class Mazegen {
public :
  void gen(int width, int height);
  void prepMaze(Cell* cells, int width, int height);
};
#endif
