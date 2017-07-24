#include "console/console_display.h"
#include "input.h"
#include "player.h"
#include "actions.h"
#include "levels.h"
#include "maze.h"

int main() {
  const char* title = "MazePlusPlus by Liam Humphreys";
  int gameWindowWidth = 100;
  int gameWindowHeight = 74;
  int playerX = gameWindowWidth / 2;
  int playerY = gameWindowHeight / 2;
  Player player(1, playerX, playerY);
  Actions actions;
  ConsoleDisplay view;
  Input input;
  Action action;
  Maze maze(Levels::one, 5, 5);
  view.openGameWindow(gameWindowWidth, gameWindowHeight, title);

  do {
    action = input.fetchInput();
    actions.perform(action, &player);
    view.beginRenderLoop();
    view.render(player.id, player.position->X, player.position->Y);

    for (int x=0; x < maze.width; x++) {
      for (int y=0; y < maze.height; y++) {
        view.renderTile(maze.tile(x, y), x, y);
      }
    }
    view.endRenderLoop();
  } while (action != EXIT && !view.isClosed());

  return 0;
}
