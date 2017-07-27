#include "input.h"
#include "actions.h"
#include "libtcod.hpp"

int Input::fetchInput() {
  TCOD_key_t key;
  TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
  switch(key.vk) {
    case TCODK_UP:
      return Actions::MOVE_UP;
    case TCODK_DOWN:
      return Actions::MOVE_DOWN;
    case TCODK_LEFT:
      return Actions::MOVE_LEFT;
    case TCODK_RIGHT:
      return Actions::MOVE_RIGHT;
    case TCODK_ESCAPE:
      return Actions::EXIT;
    default:
      return Actions::NONE;
  }
};
