#include "console/console_display.h"
#include "input.h"
#include "player.h"
#include "actions.h"

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
  view.openGameWindow(gameWindowWidth, gameWindowHeight, title);

  do {
    action = input.fetchInput();
    actions.perform(action, &player);
    view.beginRenderLoop();
    view.render(player.id, player.position->X, player.position->Y);
    view.endRenderLoop();
  } while (action != EXIT && !view.isClosed());

  return 0;
}
