#include "engine.h"
#include "player.h"
#include "idisplay.h"
#include "igui.h"
#include "maze.h"
#include "maze_generation/tiled_maze_factory.h"
#include "maze_generation/tiled_grid_factory.h"
#include "physics.h"
#include "actions.h"
#include "input.h"
#include "win_state.h"
#include <iostream>
#include <sstream>

Engine::Engine() {
  state = MAIN_MENU;
  cellsWide = 0;
  cellsTall = 0;
  tilesPerCellX = 3;
  tilesPerCellY = 3;
}

Engine::~Engine() {
  delete maze;
}

void Engine::addPlayer(Player* players, int id) {
  Point spawn = maze->playerSpawnTile();
  std::cout << spawn.X << ", " << spawn.Y << std::endl;
  players[id-1].id = id;
  players[id-1].setPosition(spawn);
}

int Engine::mainMenu(IGui* gui) {
  gui->clear();
  gui->addItem(0, "New game");
  gui->addItem(1, "Exit");
  return gui->pick();
}

int Engine::finishMenu(IGui* gui, int winnerId) {
  std::stringstream victorString;
  victorString << "Player " << winnerId << " Wins!!";
  gui->clear();
  gui->addItem(0, victorString.str().c_str(), false);
  gui->addItem(1, "New game");
  gui->addItem(2, "Exit");
  return gui->pick();
}

int Engine::pauseMenu(IGui* gui) {
  gui->clear();
  gui->addItem(-1, "PAUSED", false);
  gui->addItem(1, "Resume");
  gui->addItem(2, "New game");
  gui->addItem(3, "Add player");
  gui->addItem(4, "Exit");
  return gui->pick();
}

int Engine::playerCount(IGui* gui) {
  gui->clear();
  gui->addItem(0, "Choose number of players: ", false);
  gui->addItem(1, "  One");
  gui->addItem(2, "  Two");
  return gui->pick();
}

int Engine::mazeSize(IGui* gui) {
  gui->clear();
  gui->addItem(-1, "Choose maze size: ", false);
  gui->addItem(MS_5x5, "  5x5");
  gui->addItem(MS_10x10, "  10x10");
  gui->addItem(MS_20x20, "  20x20");
  gui->addItem(MS_40x20, "  40x20");
  gui->addItem(MS_50x50, "  50x50");
  gui->addItem(MS_100x50, "  100x50");
  gui->addItem(MS_100x100, "  100x100");
  return gui->pick();
}

void Engine::setMazeSizeByChoice(int mazeSize) {
  switch (mazeSize) {
    case MS_5x5:
      cellsWide = 5;
      cellsTall = 5;
      break;
    case MS_10x10:
      cellsWide = 10;
      cellsTall = 10;
      break;
    case MS_20x20:
      cellsWide = 20;
      cellsTall = 20;
      break;
    case MS_40x20:
      cellsWide = 40;
      cellsTall = 20;
      break;
    case MS_50x50:
      cellsWide = 50;
      cellsTall = 50;
      break;
    case MS_100x50:
      cellsWide = 100;
      cellsTall = 50;
      break;
    case MS_100x100:
      cellsWide = 100;
      cellsTall = 100;
      break;
    default:
      cellsWide = 20;
      cellsTall = 20;
      break;
  }
}

int Engine::cellSize(IGui* gui) {
  gui->clear();
  gui->addItem(-1, "Choose maze size: ", false);
  gui->addItem(CS_3x3, "  3x3");
  gui->addItem(CS_3x5, "  3x5");
  gui->addItem(CS_5x3, "  5x3");
  gui->addItem(CS_4x4, "  4x4");
  gui->addItem(CS_5x5, "  5x5");
  return gui->pick();
}

void Engine::setCellSizeByChoice(int cellSize) {
  switch (cellSize) {
    case CS_3x3:
      tilesPerCellX = 3;
      tilesPerCellY = 3;
      break;
    case CS_3x5:
      tilesPerCellX = 3;
      tilesPerCellY = 5;
      break;
    case CS_5x3:
      tilesPerCellX = 5;
      tilesPerCellY = 3;
      break;
    case CS_4x4:
      tilesPerCellX = 4;
      tilesPerCellY = 4;
      break;
    case CS_5x5:
      tilesPerCellX = 5;
      tilesPerCellY = 5;
      break;
    default:
      tilesPerCellX = 3;
      tilesPerCellY = 3;
      break;
  }
}

void Engine::createMaze(int cellsWide, int cellsTall, int tilesPerCellX, int tilesPerCellY) {
  int tileCount = TiledGridFactory::tileCountForMazeOfSize(cellsWide, cellsTall, tilesPerCellX, tilesPerCellY);
  int tilesWide = TiledGridFactory::tileCountForCellDimension(cellsWide, tilesPerCellX);
  int tilesTall = TiledGridFactory::tileCountForCellDimension(cellsTall, tilesPerCellY);
  int tileData[tileCount];
  TiledMazeFactory tmf;
  tmf.generate(cellsWide, cellsTall, tileData, tilesPerCellX, tilesPerCellY);
  maze = new Maze(tileData, tilesWide, tilesTall);
}

int Engine::winnerFound(Player* players, Maze* maze, int playerCountChoice) {
  for (int i = 0; i < playerCountChoice; i++) {
    if (WinState::hasWon(&(players[i]), &(*maze))) {
      return players[i].id;
    }
  }
  return -1;
}

int Engine::run(int gameWindowWidth, int gameWindowHeight, const char* title, IDisplay* view, IGui* gui) {
  Player players[2];
  view->openGameWindow(gameWindowWidth, gameWindowHeight, title);
  Point origin;
  Physics physics;
  int action = 0;
  Actions actions;
  Input input;
  int inputs[2];
  int playerCountChoice = 1;
  input.menuMode();
  while (true) {
    switch ((State)state) {
      case MAIN_MENU: {
        int mainMenuChoice = mainMenu(gui);
        if (mainMenuChoice == 1) {
          return 0;
        }
        state = INITIALISING_GAME;
        break;
      }
      case INITIALISING_GAME: {
        playerCountChoice = playerCount(gui);
        int mazeSizeChoice = mazeSize(gui);
        setMazeSizeByChoice(mazeSizeChoice);
        int cellSizeChoice = cellSize(gui);
        setCellSizeByChoice(cellSizeChoice);
        createMaze(cellsWide, cellsTall, tilesPerCellX, tilesPerCellY);
        if (playerCountChoice == 1) {
          addPlayer(players, 1);
        }
        else {
          addPlayer(players, 1);
          addPlayer(players, 2);
        }
        std::cout << "player1pos: " << players[0].position->X << ", " << players[0].position->Y << std::endl;
        std::cout << "player2pos: " << players[1].position->X << ", " << players[1].position->Y << std::endl;
        input.gameMode();
        state = RUNNING_GAME;
        break;
      }
      case RUNNING_GAME: {
        origin.X = (gameWindowWidth / 2) - (maze->width / 2);
        origin.Y = (gameWindowHeight / 2) - (maze->height / 2);
        action = input.fetchInput(inputs);
        for (int i = 0; i < playerCountChoice; i++) {
          actions.perform((Actions::Action)inputs[i], &(players[i]));
        }
        physics.updatePlayer(players, maze, playerCountChoice);
        view->render(players, playerCountChoice, maze, &origin);
        if (action == Actions::PAUSE) {
          input.menuMode();
          state = PAUSE_MENU;
        }
        if (winnerFound(players, maze, playerCountChoice) != -1) {
          input.menuMode();
          state = FINISH;
        }
        if (action == Actions::EXIT || view->isClosed()) {
          input.menuMode();
          state = EXIT;
        }
        break;
      }
      case FINISH: {
        int winnerId = winnerFound(players, maze, playerCountChoice);
        int finishMenuChoice = finishMenu(gui, winnerId);
        if (finishMenuChoice == 1) {
          state = INITIALISING_GAME;
        }
        else if (finishMenuChoice == 2) {
          state = EXIT;
        }
        break;
      }
      case PAUSE_MENU: {
        int pauseMenuChoice = pauseMenu(gui);
        if (pauseMenuChoice == 1) {
          input.gameMode();
          state = RUNNING_GAME;
        }
        else if (pauseMenuChoice == 2) {
          input.menuMode();
          state = INITIALISING_GAME;
        }
        else if (pauseMenuChoice == 3) {
          if (playerCountChoice < 2) {
            playerCountChoice++;
            addPlayer(players, 2);
            input.gameMode();
            state = RUNNING_GAME;
          }
        }
        else {
          input.menuMode();
          state = EXIT;
        }
        break;
      }
      case EXIT: {
        return 0;
        break;
      }
      default: return 0;
    }
  }
}
