#include "mazegen.h"
#include "cell.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

using std::cout;
using std::vector;

enum DIR { NORTH, SOUTH, EAST, WEST };

void Mazegen::prepMaze(Cell* cells, int width, int height) {
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      cells[x+y*width].setVisited(false);
      cells[x+y*width].setPosition(y, x);
      cells[x+y*width].setWalls(Cell::WALL_ALL);
    }
  }
}

void Mazegen::gen(int width, int height) {
  srand(time(NULL));

  Cell maze[height][width];

  for(int row = 0; row < height; row++) {
    for(int col = 0; col < width; col++) {
      maze[row][col].setVisited(false);
      maze[row][col].setPosition(row, col);
      maze[row][col].setWalls(Cell::WALL_ALL);
    }
  }

  int curX = rand() % height;
  int curY = rand() % width;

  vector<Cell> trail;
  vector<DIR> availableDirs;
  trail.push_back(maze[curX][curY]);

  while(trail.empty()==false) {
    availableDirs.clear();

    if(curY)
      if(maze[curX][curY-1].getWalls()==Cell::WALL_ALL)
        availableDirs.push_back(WEST);
    if(curY<width-1)
      if(maze[curX][curY+1].getWalls()==Cell::WALL_ALL)
        availableDirs.push_back(EAST);
    if(curX)
      if(maze[curX-1][curY].getWalls()==Cell::WALL_ALL)
        availableDirs.push_back(NORTH);
    if(curX<height-1)
      if(maze[curX+1][curY].getWalls()==Cell::WALL_ALL)
        availableDirs.push_back(SOUTH);

    if(availableDirs.empty()==false) {
      maze[curX][curY].setVisited(true);
      switch(availableDirs[rand() % availableDirs.size()]) {
        case 0:
          maze[curX][curY].removeWall(Cell::WALL_NORTH);
          maze[--curX][curY].removeWall(Cell::WALL_SOUTH);
          break;
        case 1:
          maze[curX][curY].removeWall(Cell::WALL_SOUTH);
          maze[++curX][curY].removeWall(Cell::WALL_NORTH);
          break;
        case 2:
          maze[curX][curY].removeWall(Cell::WALL_EAST);
          maze[curX][++curY].removeWall(Cell::WALL_WEST);
          break;
        case 3:
          maze[curX][curY].removeWall(Cell::WALL_WEST);
          maze[curX][--curY].removeWall(Cell::WALL_EAST);
          break;
      }

      trail.push_back(maze[curX][curY]);
    }
    else {
      trail.pop_back();

      if(trail.empty()==false) {
        curX=trail.back().getRow();
        curY=trail.back().getColumn();
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
      cout << maze[r][c];
    }
    cout << "|\n";
  }
}
