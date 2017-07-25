#include "console/console_display.h"
#include "input.h"
#include "player.h"
#include "actions.h"
#include "levels.h"
#include "maze.h"
#include "maze_generation/mazegen.h"

int main() {
  const char* title = "MazePlusPlus by Liam Humphreys";
  int gameWindowWidth = 200;
  int gameWindowHeight = 150;
  Player player(1, 1, 1);
  Actions actions;
  ConsoleDisplay view;
  Input input;
  Action action;
  Maze maze(Levels::one, 10, 10);
  view.openGameWindow(gameWindowWidth, gameWindowHeight, title);
  Mazegen genner;
  genner.gen(10, 10);

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
