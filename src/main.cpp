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
#include "engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  srand (time(NULL));
  const char* title = "MazePlusPlus by Liam Humphreys";
  int gameWindowWidth = 200;
  int gameWindowHeight = 150;

  IDisplay* view = new ConsoleDisplay();
  IGui* gui = new Gui();
  Engine engine;
  engine.run(gameWindowWidth, gameWindowHeight, title, view, gui);
  delete view;
  delete gui;
  // Physics physics;
  // int originX = (gameWindowWidth / 2) - (maze.width / 2);
  // int originY = (gameWindowHeight / 2) - (maze.height / 2);
  // Point origin(originX, originY);
  // do {
  //   if (WinState::hasWon(&player, &maze)) {
  //     std::cout << "winner!";
  //   }
  //   action = (Actions::Action)input.fetchInput();
  //   actions.perform(action, &player);
  //   physics.updatePlayer(&player, &maze);
  //   view.render(players, &maze, playerCount, &origin);
  // } while (action != Actions::EXIT && !view.isClosed());

  return 0;
}
