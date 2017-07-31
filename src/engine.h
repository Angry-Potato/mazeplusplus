#ifndef ENGINE_H
#define ENGINE_H

class IDisplay;
class IGui;
class Maze;
class Player;
class IInput;
class Engine {
public :
  enum State {
    MAIN_MENU,
    INITIALISING_GAME,
    RUNNING_GAME,
    FINISH,
    PAUSE_MENU,
    EXIT
  };
  enum MazeSize {
    MS_5x5,
    MS_10x10,
    MS_20x20,
    MS_40x20,
    MS_50x50,
    MS_100x50,
    MS_100x100
  };
  enum CellSize {
    CS_3x3,
    CS_3x5,
    CS_5x3,
    CS_4x4,
    CS_5x5
  };
  int state;
  int cellsTall;
  int cellsWide;
  int tilesPerCellX;
  int tilesPerCellY;
  Maze* maze;
  Engine();
  ~Engine();
  int run(int gameWindowWidth, int gameWindowHeight, const char* title, IDisplay* view, IGui* gui, IInput* input);
  void addPlayer(Player* players, int id);
  int winnerFound(Player* players, Maze* maze, int playerCountChoice);
  int mainMenu(IGui* gui);
  int finishMenu(IGui* gui, int winnerId);
  int pauseMenu(IGui* gui);
  int playerCount(IGui* gui);
  int mazeSize(IGui* gui);
  void setMazeSizeByChoice(int mazeSize);
  int cellSize(IGui* gui);
  void setCellSizeByChoice(int cellSize);
  void createMaze(int cellsWide, int cellsTall, int tilesPerCellX, int tilesPerCellY);
};
#endif
