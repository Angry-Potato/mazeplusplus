#ifndef IGUI_H
#define IGUI_H

class IGui {
public :
  virtual void clear() = 0;
  virtual void addItem(int id, const char *label, bool selectable = true) = 0;
  virtual int pick() = 0;
  virtual ~IGui() { };
};
#endif
