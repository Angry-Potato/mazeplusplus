#include "mazegen.h"
#include "cell.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

using std::cout;
using std::vector;

void Mazegen::prepMaze(Cell* cells, int width, int height) {
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      cells[locate(x, y, width)].setPosition(y, x);
      cells[locate(x, y, width)].setWalls(Cell::WALL_ALL);
    }
  }
}

void Mazegen::genMaze(Cell* cells, int width, int height) {
  vector<Cell> trail;
  trail.push_back(cells[locate(1, 1, width)]);
  vector<DIR> availableDirs;
  while(!trail.empty()) {
    availableDirs.clear();
    Cell* current = &(trail.back());

    setAvailableDirs(availableDirs, cells, current->X, current->Y, width, height);

    if(!availableDirs.empty()) {
      int randDir = availableDirs[rand() % availableDirs.size()];
      Cell* p = forgePath(cells, current->X, current->Y, width, height, randDir);
      trail.push_back(*p);
    }
    else {
      trail.pop_back();
    }
  }
}

Cell* Mazegen::cellNeighbour(Cell* cells, int width, int height, int x, int y, int dir) const {
  switch (dir) {
    case NORTH: return y > 0        ? &(cells[locate(x, y-1, width)]) : NULL;
    case SOUTH: return y < height-1 ? &(cells[locate(x, y+1, width)]) : NULL;
    case EAST:  return x < width-1  ? &(cells[locate(x+1, y, width)]) : NULL;
    case WEST:  return x > 0        ? &(cells[locate(x-1, y, width)]) : NULL;
    default:    return NULL;
  }
}

bool Mazegen::isDirAvailable(Cell* cells, int width, int height, int x, int y, int dir) const {
  Cell* neighbour = cellNeighbour(cells, width, height, x, y, dir);
  return neighbour == (Cell*)NULL ? false : neighbour->getWalls() == Cell::WALL_ALL;
}

int Mazegen::opposite(int dir) const {
  switch (dir) {
    case NORTH: return SOUTH;
    case SOUTH: return NORTH;
    case EAST: return WEST;
    case WEST: return EAST;
    default: return dir;
  }
}

Cell* Mazegen::forgePath(Cell* cells, int x, int y, int width, int height, int dir) {
  cells[locate(x, y, width)].removeWall(dir);
  Cell* neighbour = cellNeighbour(cells, width, height, x, y, dir);
  neighbour->removeWall(opposite(dir));
  return neighbour;
}

void Mazegen::setAvailableDirs(vector<DIR> &availableDirs, Cell* cells, int x, int y, int width, int height) {
  DIR directions[4] = { NORTH, SOUTH, EAST, WEST };
  for (size_t i = 0; i < 4; i++) {
    if(isDirAvailable(cells, width, height, x, y, directions[i]))
      availableDirs.push_back(directions[i]);
  }
}

void Mazegen::gen(int width, int height) {
  srand(time(NULL));

  Cell maze[height*width];

  prepMaze(maze, width, height);
  genMaze(maze, width, height);

  int r, c;
  // for (c=0; c<width; c++) {
  //   if (c == 0) cout << " _";
  //   else cout << "__";
  // }
  cout << '\n';
  for (r=0; r<height; r++) {
    for (c=0; c<width; c++) {
      cout << maze[locate(c, r, width)];
    }
    cout << "|\n";
  }
}
