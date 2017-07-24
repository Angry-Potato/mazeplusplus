#ifndef CONSOLE_DISPLAY_H
#define CONSOLE_DISPLAY_H

#include "../tile.h"

class ConsoleDisplay {
public :
  bool isClosed() const;
  void openGameWindow(int width, int height, const char* title);
  void beginRenderLoop();
  void renderPlayer(int id, int x, int y);
  void renderTile(TileType type, int x, int y);
  void endRenderLoop();
};
#endif
