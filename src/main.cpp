#include <iostream>
#include "console/console_display.h"
#include "console/gui.h"
#include "input.h"
#include "player.h"
#include "actions.h"
#include "maze.h"
#include "physics.h"
#include "maze_generation/cell.h"
#include "maze_generation/mazegen.h"
#include "maze_generation/tiled_grid_factory.h"
#include "maze_generation/tiled_maze_factory.h"
#include "win_state.h"

int main() {
  const char* title = "MazePlusPlus by Liam Humphreys";
  int gameWindowWidth = 200;
  int gameWindowHeight = 150;
  Player player(1, 1, 1);
  int playerCount = 1;
  Player players[playerCount];
  players[0] = player;

  Actions actions;
  ConsoleDisplay view;
  Input input;
  Actions::Action action;
  view.openGameWindow(gameWindowWidth, gameWindowHeight, title);

  Gui gui;
  gui.clear();
	gui.addItem(Gui::NEW_GAME,"New game");
	gui.addItem(Gui::EXIT,"Exit");
	Gui::MenuItemCode menuItem=gui.pick();
	if ( menuItem == Gui::EXIT || menuItem == Gui::NONE ) {
		// Exit or window closed
		return 0;
  }

  int width = 15;
  int height = 15;
  int tilesPerCellX = 3;
  int tilesPerCellY = 3;
  int tileCount = TiledGridFactory::tileCountForMazeOfSize(width, height, tilesPerCellX, tilesPerCellY);
  int tilesWide = TiledGridFactory::tileCountForCellDimension(width, tilesPerCellX);
  int tilesTall = TiledGridFactory::tileCountForCellDimension(height, tilesPerCellY);
  int tileData[tileCount];
  TiledMazeFactory tmf;
  tmf.generate(width, height, tileData, tilesPerCellX, tilesPerCellY);
  Maze maze(tileData, tilesWide, tilesTall);
  Physics physics;
  int originX = (gameWindowWidth / 2) - (maze.width / 2);
  int originY = (gameWindowHeight / 2) - (maze.height / 2);
  Point origin(originX, originY);
  do {
    if (WinState::hasWon(&player, &maze)) {
      std::cout << "winner!";
    }
    action = (Actions::Action)input.fetchInput();
    actions.perform(action, &player);
    physics.updatePlayer(&player, &maze);
    view.render(players, &maze, playerCount, &origin);
  } while (action != Actions::EXIT && !view.isClosed());

  return 0;
}
