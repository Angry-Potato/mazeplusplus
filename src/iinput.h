#ifndef IINPUT_H
#define IINPUT_H

class IInput {
public :
  virtual void gameMode() = 0;
  virtual void menuMode() = 0;
  virtual int fetchInput(int* inputs) = 0;
  virtual ~IInput() { };
};
#endif
