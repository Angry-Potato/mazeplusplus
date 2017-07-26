#include "console/console_display.h"
#include "input.h"
#include "player.h"
#include "actions.h"
#include "maze.h"
#include "maze_generation/cell.h"
#include "maze_generation/mazegen.h"
#include "maze_generation/tiled_grid_factory.h"

#include <iostream>

using std::cout;

int main() {
  const char* title = "MazePlusPlus by Liam Humphreys";
  int gameWindowWidth = 200;
  int gameWindowHeight = 150;
  Player player(1, 1, 1);
  Actions actions;
  ConsoleDisplay view;
  Input input;
  Action action;
  view.openGameWindow(gameWindowWidth, gameWindowHeight, title);

  Mazegen genner;
  int width = 14;
  int height = 14;
  Cell cells[width*height];
  genner.generate(width, height, cells);

  int r, c;
  for (c=0; c<width; c++) {
    if (c == 0) cout << " _";
    else cout << "__";
  }
  cout << '\n';
  for (r=0; r<height; r++) {
    for (c=0; c<width; c++) {
      cout << cells[c+r*width];
    }
    cout << "|\n";
  }

  TiledGridFactory tgf;
  int tilesPerCellX = 5;
  int tilesPerCellY = 5;
  int tileCount = tgf.tileCountForMazeOfSize(width, height, tilesPerCellX, tilesPerCellY);
  int tilesWide = tgf.tileCountForCellDimension(width, tilesPerCellX);
  int tilesTall = tgf.tileCountForCellDimension(height, tilesPerCellY);
  int tileData[tileCount];
  tgf.generate(width, height, tileData, tilesPerCellX, tilesPerCellY);
  Maze maze(tileData, tilesWide, tilesTall);




  int originX = (gameWindowWidth / 2) - (maze.width / 2);
  int originY = (gameWindowHeight / 2) - (maze.height / 2);
  do {
    action = input.fetchInput();
    actions.perform(action, &player);
    view.beginRenderLoop();
    for (int x=0; x < maze.width; x++) {
      for (int y=0; y < maze.height; y++) {
        view.renderTile(maze.tile(x, y), x + originX, y + originY);
      }
    }
    view.renderPlayer(player.id, player.position->X + originX, player.position->Y + originY);
    view.endRenderLoop();
  } while (action != EXIT && !view.isClosed());

  return 0;
}
