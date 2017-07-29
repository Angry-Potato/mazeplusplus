#ifndef GUI_H
#define GUI_H

#include "libtcod.hpp"
#include "../igui.h"

class Gui : public IGui {
public :
  struct MenuItem {
    int id;
    const char *label;
    bool selectable;
  };

  ~Gui();
  void clear();
  void addItem(int id, const char *label, bool selectable = true);
  int pick();
  protected :
  TCODList<MenuItem *> items;
};
#endif
