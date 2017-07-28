#ifndef GUI_H
#define GUI_H

#include "libtcod.hpp"

class Gui {
public :
  enum MenuItemCode {
    NONE,
    NEW_GAME,
    CONTINUE,
    EXIT
  };

  struct MenuItem {
    MenuItemCode code;
    const char *label;
  };

  ~Gui();
  void clear();
  void addItem(MenuItemCode code, const char *label);
  MenuItemCode pick();
  protected :
  TCODList<MenuItem *> items;
};
#endif
