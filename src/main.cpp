#include "console_view.h"
#include "input.h"
#include "libtcod.hpp"
int main() {
  const char* title = "MazePlusPlus by Liam Humphreys";
  int gameWindowWidth = 100;
  int gameWindowHeight = 74;
  int playerX = gameWindowWidth / 2;
  int playerY = gameWindowHeight / 2;
  bool escape = false;
  ConsoleView view;
  Input input;

  view.openGameWindow(gameWindowWidth, gameWindowHeight, title);

  do {
    Action action = input.fetchInput();
    switch(action) {
      case MOVE_UP:
        playerY--;
        break;
      case MOVE_DOWN:
        playerY++;
        break;
      case MOVE_LEFT:
        playerX--;
        break;
      case MOVE_RIGHT:
        playerX++;
        break;
      case EXIT:
        escape = true;
        break;
      default:break;
    }
    view.beginRenderLoop();
    TCODConsole::root->putChar(playerX, playerY, 'a');
    view.endRenderLoop();
  } while (!escape && !view.isClosed());

  return 0;
}
