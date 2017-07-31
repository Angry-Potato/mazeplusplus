#include "keyboard_input.h"
#include "../actions.h"
#include "libtcod.hpp"

void KeyboardInput::gameMode() {
  TCODConsole::setKeyboardRepeat(1, 100);
}
void KeyboardInput::menuMode() {
  TCODConsole::setKeyboardRepeat(200, 100);
}

int KeyboardInput::fetchInput(int* inputs) {
  TCOD_key_t key;
  TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);

  inputs[0] = player1Input(key.vk, key.c);
  inputs[1] = player2Input(key.vk, key.c);
  switch(key.vk) {
    case TCODK_F1:
      return Actions::PAUSE;
    case TCODK_ESCAPE:
      return Actions::EXIT;
    default:
      return Actions::NONE;
  }
  return Actions::NONE;
};

int KeyboardInput::player1Input(int vk, char c) {
  switch(vk) {
    case TCODK_UP:
      return Actions::MOVE_UP;
    case TCODK_DOWN:
      return Actions::MOVE_DOWN;
    case TCODK_LEFT:
      return Actions::MOVE_LEFT;
    case TCODK_RIGHT:
      return Actions::MOVE_RIGHT;
    case TCODK_F1:
      return Actions::PAUSE;
    case TCODK_ESCAPE:
      return Actions::EXIT;
    default:
      return Actions::NONE;
  }
}

int KeyboardInput::player2Input(int vk, char c) {
  switch(vk) {
    case TCODK_CHAR:
      switch (c) {
        case 'w':
          return Actions::MOVE_UP;
        case 's':
          return Actions::MOVE_DOWN;
        case 'a':
          return Actions::MOVE_LEFT;
        case 'd':
          return Actions::MOVE_RIGHT;
        default:
          return Actions::NONE;
      }
    case TCODK_F1:
      return Actions::PAUSE;
    case TCODK_ESCAPE:
      return Actions::EXIT;
    default:
      return Actions::NONE;
  }
}
