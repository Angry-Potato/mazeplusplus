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
      cells[x+y*width].setPosition(y, x);
      cells[x+y*width].setWalls(Cell::WALL_ALL);
    }
  }
}

Cell* Mazegen::cellNeighbour(Cell* cells, int width, int height, int x, int y, int dir) {
  switch (dir) {
    case NORTH: return y > 0        ? &(cells[x+(y-1)*width]) : NULL;
    case SOUTH: return y < height-1 ? &(cells[x+(y+1)*width]) : NULL;
    case EAST:  return x < width-1  ? &(cells[(x+1)+y*width]) : NULL;
    case WEST:  return x > 0        ? &(cells[(x-1)+y*width]) : NULL;
    default:    return NULL;
  }
}

void Mazegen::gen(int width, int height) {
  srand(time(NULL));

  Cell maze[height*width];
  vector<Cell> trail;
  vector<DIR> availableDirs;

  prepMaze(maze, width, height);

  int curY = rand() % height;
  int curX = rand() % width;

  trail.push_back(maze[curX+curY*width]);

  while(trail.empty()==false) {
    availableDirs.clear();


    if(curX > 0 && cellNeighbour(maze, width, height, curX, curY, WEST)->getWalls()==Cell::WALL_ALL)
      availableDirs.push_back(WEST);
    if(curX<width-1 && cellNeighbour(maze, width, height, curX, curY, EAST)->getWalls()==Cell::WALL_ALL)
      availableDirs.push_back(EAST);
    if(curY > 0 && cellNeighbour(maze, width, height, curX, curY, NORTH)->getWalls()==Cell::WALL_ALL)
      availableDirs.push_back(NORTH);
    if(curY<height-1 && cellNeighbour(maze, width, height, curX, curY, SOUTH)->getWalls()==Cell::WALL_ALL)
      availableDirs.push_back(SOUTH);

    if(availableDirs.empty()==false) {
      switch(availableDirs[rand() % availableDirs.size()]) {
        case 0:
          maze[curX+curY*width].removeWall(Cell::WALL_NORTH);
          maze[curX+(--curY)*width].removeWall(Cell::WALL_SOUTH);
          break;
        case 1:
          maze[curX+curY*width].removeWall(Cell::WALL_SOUTH);
          maze[curX+(++curY)*width].removeWall(Cell::WALL_NORTH);
          break;
        case 2:
          maze[curX+curY*width].removeWall(Cell::WALL_EAST);
          maze[(++curX)+curY*width].removeWall(Cell::WALL_WEST);
          break;
        case 3:
          maze[curX+curY*width].removeWall(Cell::WALL_WEST);
          maze[(--curX)+curY*width].removeWall(Cell::WALL_EAST);
          break;
      }

      trail.push_back(maze[curX+curY*width]);
    }
    else {
      trail.pop_back();

      if(trail.empty()==false) {
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
