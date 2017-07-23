enum Action {
  NONE,
  MOVE_UP,
  MOVE_DOWN,
  MOVE_LEFT,
  MOVE_RIGHT,
  EXIT
};

class Input {
public :
  Action fetchInput();
};
