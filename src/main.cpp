#include <iostream>
#include "console/console_display.h"
#include "console/gui.h"
#include "console/keyboard_input.h"
#include "engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  srand(time(NULL));
  const char* title = "MazePlusPlus by Liam Humphreys";
  int gameWindowWidth = 200;
  int gameWindowHeight = 150;

  IDisplay* view = new ConsoleDisplay();
  IGui* gui = new Gui();
  IInput* input = new KeyboardInput();
  Engine engine;
  engine.run(gameWindowWidth, gameWindowHeight, title, view, gui, input);
  delete view;
  delete gui;
  delete input;
  return 0;
}
