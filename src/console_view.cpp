#include "libtcod.hpp"
#include "console_view.h"

void ConsoleView::openGameWindow(int width, int height, const char* title) {
  TCODConsole::initRoot(width, height, title, false);
}

bool ConsoleView::isClosed() const {
  return TCODConsole::isWindowClosed();
}

void ConsoleView::beginRenderLoop() {
  TCODConsole::root->clear();
}

void ConsoleView::render() {

}

void ConsoleView::endRenderLoop() {
  TCODConsole::flush();
}
