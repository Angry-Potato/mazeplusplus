#ifndef ACTIONS_H
#define ACTIONS_H

enum Action {
  NONE,
  MOVE_UP,
  MOVE_DOWN,
  MOVE_LEFT,
  MOVE_RIGHT,
  EXIT
};

class Player;
class Actions {
public :
  void perform(Action action, Player* player) const;
};
#endif
