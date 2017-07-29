#include "gui.h"
#include "libtcod.hpp"

Gui::~Gui() {
  clear();
}

void Gui::clear() {
  items.clearAndDelete();
  TCODConsole::root->clear();
  TCODConsole::flush();
}

void Gui::addItem(int id, const char *label, bool selectable) {
  MenuItem *item=new MenuItem();
  item->id=id;
  item->label=label;
  item->selectable=selectable;
  items.push(item);
}

int Gui::pick() {
  // static TCODImage img("menu_background1.png");
  int selectedItem = 0;
  while (!TCODConsole::isWindowClosed()) {
    // img.blit2x(TCODConsole::root,0,0);
    int currentItem = 0;
    for (MenuItem **it = items.begin(); it != items.end(); it++) {
      if (!items.get(currentItem)->selectable) {
        TCODConsole::root->setDefaultForeground(TCODColor::white);
      }
      else if (currentItem == selectedItem) {
        TCODConsole::root->setDefaultForeground(TCODColor::lighterOrange);
      }
      else {
        TCODConsole::root->setDefaultForeground(TCODColor::lightGrey);
      }
      TCODConsole::root->print(10,10+currentItem*3,(*it)->label);
      currentItem++;
    }
    TCODConsole::flush();

    // check key presses
    TCOD_key_t key;
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL);
    switch (key.vk) {
      case TCODK_UP :
        selectedItem--;
        if (selectedItem < 0) {
          selectedItem=items.size()-1;
        }
      break;
      case TCODK_DOWN :
        selectedItem = (selectedItem + 1) % items.size();
      break;
      case TCODK_ENTER :
        return items.get(selectedItem)->id;
      default : break;
    }
  }
  return -1;
}
