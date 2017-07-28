#ifndef IDISPLAY_H
#define IDISPLAY_H

class Player;
class Maze;
class Point;
class IDisplay {
public:
  virtual void openGameWindow(int width, int height, const char* title) = 0;
  virtual void render(Player* players, Maze* maze, int playerCount, Point* origin) = 0;
  virtual bool isClosed() const = 0;
};
#endif
