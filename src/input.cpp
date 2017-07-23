#include "libtcod.hpp"
#include "input.h"

Action Input::fetchInput() {
  TCOD_key_t key;
  TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
  switch(key.vk) {
    case TCODK_UP:
      return MOVE_UP;
    case TCODK_DOWN:
      return MOVE_DOWN;
    case TCODK_LEFT:
      return MOVE_LEFT;
    case TCODK_RIGHT:
      return MOVE_RIGHT;
    case TCODK_ESCAPE:
      return EXIT;
    default:
      return NONE;
  }
};
