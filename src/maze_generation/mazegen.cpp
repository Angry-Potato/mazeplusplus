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
  return neighbour == (Cell*)NULL ? false : neighbour->getWalls()==Cell::WALL_ALL;
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

void Mazegen::forgePath(Cell* cells, int x, int y, int width, int height, int dir) {
  cells[locate(x, y, width)].removeWall(dir);
  cellNeighbour(cells, width, height, x, y, dir)->removeWall(opposite(dir));
}

void Mazegen::gen(int width, int height) {
  srand(time(NULL));

  Cell maze[height*width];
  vector<Cell> trail;
  vector<DIR> availableDirs;

  prepMaze(maze, width, height);

  int curY = rand() % height;
  int curX = rand() % width;

  trail.push_back(maze[locate(curX, curY, width)]);

  while(!trail.empty()) {
    availableDirs.clear();

    if(isDirAvailable(maze, width, height, curX, curY, WEST))
      availableDirs.push_back(WEST);
    if(isDirAvailable(maze, width, height, curX, curY, EAST))
      availableDirs.push_back(EAST);
    if(isDirAvailable(maze, width, height, curX, curY, NORTH))
      availableDirs.push_back(NORTH);
    if(isDirAvailable(maze, width, height, curX, curY, SOUTH))
      availableDirs.push_back(SOUTH);

    if(!availableDirs.empty()) {
      switch(availableDirs[rand() % availableDirs.size()]) {
        case NORTH:
          forgePath(maze, curX, curY--, width, height, NORTH);
          break;
        case SOUTH:
          forgePath(maze, curX, curY++, width, height, SOUTH);
          break;
        case EAST:
          forgePath(maze, curX++, curY, width, height, EAST);
          break;
        case WEST:
          forgePath(maze, curX--, curY, width, height, WEST);
          break;
      }

      trail.push_back(maze[locate(curX, curY, width)]);
    }
    else {
      trail.pop_back();

      if(!trail.empty()) {
        curY=trail.back().getRow();
        curX=trail.back().getColumn();
      }
    }
  }

  int r, c;
  for (c=0; c<width; c++) {
    if (c == 0) cout << " _";
    else cout << "__";
  }
  cout << '\n';
  for (r=0; r<height; r++) {
    for (c=0; c<width; c++) {
      cout << maze[c+r*width];
    }
    cout << "|\n";
  }
}
