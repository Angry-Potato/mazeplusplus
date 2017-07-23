#include "console_view.h"
#include "input.h"
#include "player.h"
#include "actions.h"
#include "libtcod.hpp"
int main() {
  const char* title = "MazePlusPlus by Liam Humphreys";
  int gameWindowWidth = 100;
  int gameWindowHeight = 74;
  int playerX = gameWindowWidth / 2;
  int playerY = gameWindowHeight / 2;
  Player player(playerX, playerY);
  Actions actions;
  ConsoleView view;
  Input input;
  Action action;
  view.openGameWindow(gameWindowWidth, gameWindowHeight, title);

  do {
    action = input.fetchInput();
    actions.perform(action, &player);
    view.beginRenderLoop();
    TCODConsole::root->putChar(player.position.X, player.position.Y, 'a');
    view.endRenderLoop();
  } while (action != EXIT && !view.isClosed());

  return 0;
}
