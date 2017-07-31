#ifndef KEYBOARD_INPUT_H
#define KEYBOARD_INPUT_H

#include "../iinput.h"

class KeyboardInput : public IInput {
public :
  void gameMode();
  void menuMode();
  int fetchInput(int* inputs);
  int player1Input(int vk, char c);
  int player2Input(int vk, char c);
};
#endif
