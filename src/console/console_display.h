#ifndef CONSOLE_DISPLAY_H
#define CONSOLE_DISPLAY_H

#include "../idisplay.h"

class Player;
class ConsoleDisplay : public IDisplay {
public :
  void render(Player* players, Maze* maze, int playerCount, Point* origin);
  bool isClosed() const;
  void openGameWindow(int width, int height, const char* title);
  void beginRenderLoop();
  void renderPlayer(int id, int x, int y);
  void renderTile(int type, int x, int y);
  void endRenderLoop();
};
#endif
