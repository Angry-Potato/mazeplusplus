#include "libtcod.hpp"
#include "console_display.h"
#include "player_view.h"
#include "tile_view.h"
#include "../point.h"
#include "../player.h"
#include "../maze.h"

void ConsoleDisplay::render(Player* players, Maze* maze, int playerCount, Point* origin) {
  beginRenderLoop();
  for (int x=0; x < maze->width; x++) {
    for (int y=0; y < maze->height; y++) {
      renderTile(maze->tile(x, y), x + origin->X, y + origin->Y);
    }
  }

  for (int i = 0; i < playerCount; i++) {
    renderPlayer(players[i].id, players[i].position->X + origin->X, players[i].position->Y + origin->Y);
  }
  endRenderLoop();
}

void ConsoleDisplay::openGameWindow(int width, int height, const char* title) {
  TCODConsole::initRoot(width, height, title, false);
}

bool ConsoleDisplay::isClosed() const {
  return TCODConsole::isWindowClosed();
}

void ConsoleDisplay::beginRenderLoop() {
  TCODConsole::root->clear();
}

void ConsoleDisplay::renderPlayer(int id, int x, int y) {
  TCODConsole::root->setChar(x, y, PlayerView::characterCode(id));
  TCODConsole::root->setCharForeground(x, y, PlayerView::colour(id));
}

void ConsoleDisplay::renderTile(int type, int x, int y) {
  TCODConsole::root->setChar(x, y, TileView::characterCode(type));
  TCODConsole::root->setCharForeground(x, y, TileView::colour(type));
}

void ConsoleDisplay::endRenderLoop() {
  TCODConsole::flush();
}
