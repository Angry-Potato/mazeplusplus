#include "libtcod.hpp"
#include "console_display.h"
#include "player_view.h"
#include "tile_view.h"

void ConsoleDisplay::openGameWindow(int width, int height, const char* title) {
  TCODConsole::initRoot(width, height, title, false);
}

bool ConsoleDisplay::isClosed() const {
  return TCODConsole::isWindowClosed();
}

void ConsoleDisplay::beginRenderLoop() {
  TCODConsole::root->clear();
}

void ConsoleDisplay::render(int id, int x, int y) {
  TCODConsole::root->setChar(x, y, PlayerView::characterCode(id));
  TCODConsole::root->setCharForeground(x, y, PlayerView::colour(id));
}

void ConsoleDisplay::renderTile(TileType type, int x, int y) {
  TCODConsole::root->setChar(x, y, TileView::characterCode(type));
  TCODConsole::root->setCharForeground(x, y, TCODColor::white);
}

void ConsoleDisplay::endRenderLoop() {
  TCODConsole::flush();
}
