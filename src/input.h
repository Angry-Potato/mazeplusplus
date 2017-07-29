#ifndef INPUT_H
#define INPUT_H

class Input {
public :
  void gameMode();
  void menuMode();
  int fetchInput(int* inputs);
  int player1Input(int vk, char c);
  int player2Input(int vk, char c);
};
#endif
