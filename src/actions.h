#ifndef ACTIONS_H
#define ACTIONS_H

class Player;
class Actions {
public :
  enum Action {
    NONE,
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT,
    EXIT
  };

  void perform(Action action, Player* player) const;
};
#endif
