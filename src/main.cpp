#include "libtcod.hpp"

void openGameWindow(int width, int height, const char* title) {
  TCODConsole::initRoot(width, height, title, false);
}

int main() {
  const char* title = "MazePlusPlus by Liam Humphreys";
  int gameWindowWidth = 100;
  int gameWindowHeight = 74;
  int playerX = gameWindowWidth / 2;
  int playerY = gameWindowHeight / 2;
  bool escape = false;

  openGameWindow(gameWindowWidth, gameWindowHeight, title);

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
    TCODConsole::root->clear();
    TCODConsole::root->putChar(playerX, playerY, 'a');
    TCODConsole::flush();
  } while (!escape && !TCODConsole::isWindowClosed());

  return 0;
}
