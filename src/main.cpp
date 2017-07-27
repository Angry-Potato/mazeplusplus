#include "console/console_display.h"
#include "input.h"
#include "player.h"
#include "actions.h"
#include "maze.h"
#include "maze_generation/cell.h"
#include "maze_generation/mazegen.h"
#include "maze_generation/tiled_grid_factory.h"
#include "maze_generation/tiled_maze_factory.h"

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

  int width = 25;
  int height = 25;
  int tilesPerCellX = 6;
  int tilesPerCellY = 6;
  int tileCount = TiledGridFactory::tileCountForMazeOfSize(width, height, tilesPerCellX, tilesPerCellY);
  int tilesWide = TiledGridFactory::tileCountForCellDimension(width, tilesPerCellX);
  int tilesTall = TiledGridFactory::tileCountForCellDimension(height, tilesPerCellY);
  int tileData[tileCount];
  TiledMazeFactory tmf;
  tmf.generate(width, height, tileData, tilesPerCellX, tilesPerCellY);
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
