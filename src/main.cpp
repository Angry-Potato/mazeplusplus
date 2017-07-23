#include "console_view.h"
#include "input.h"
#include "libtcod.hpp"
int main() {
  const char* title = "MazePlusPlus by Liam Humphreys";
  int gameWindowWidth = 100;
  int gameWindowHeight = 74;
  int playerX = gameWindowWidth / 2;
  int playerY = gameWindowHeight / 2;
  ConsoleView view;
  Input input;
  Action action;
  view.openGameWindow(gameWindowWidth, gameWindowHeight, title);

  do {
    action = input.fetchInput();
    view.beginRenderLoop();
    TCODConsole::root->putChar(playerX, playerY, 'a');
    view.endRenderLoop();
    action = NONE;
  } while (action != EXIT && !view.isClosed());

  return 0;
}
