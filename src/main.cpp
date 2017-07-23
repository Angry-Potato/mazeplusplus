#include "console_view.h"

int main() {
  const char* title = "MazePlusPlus by Liam Humphreys";
  int gameWindowWidth = 100;
  int gameWindowHeight = 74;
  int playerX = gameWindowWidth / 2;
  int playerY = gameWindowHeight / 2;
  bool escape = false;
  ConsoleView view;

  view.openGameWindow(gameWindowWidth, gameWindowHeight, title);

  do {
    TCOD_key_t key;
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
    switch(key.vk) {
      case TCODK_UP:
        playerY--;
        break;
      case TCODK_DOWN:
        playerY++;
        break;
      case TCODK_LEFT:
        playerX--;
        break;
      case TCODK_RIGHT:
        playerX++;
        break;
      case TCODK_ESCAPE:
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
