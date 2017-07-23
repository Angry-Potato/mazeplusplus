#include "libtcod.hpp"
#include "console_display.h"
#include "player_view.h"

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
  TCODConsole::root->putChar(x, y, PlayerView::forId(id));
}

void ConsoleDisplay::endRenderLoop() {
  TCODConsole::flush();
}
