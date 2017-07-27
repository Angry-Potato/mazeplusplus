#include "tiled_maze_factory.h"
#include "tiled_grid_factory.h"
#include "cell.h"
#include "mazegen.h"
#include "../tile.h"
#include <vector>
#include <stdlib.h>
#include <algorithm>

using std::vector;

void TiledMazeFactory::generate(int cellsWide, int cellsTall, int* tileData, int tilesPerCellX, int tilesPerCellY) const {
  TiledGridFactory tiledGridFactory;
  tiledGridFactory.generate(cellsWide, cellsTall, tileData, tilesPerCellX, tilesPerCellY);

  Mazegen mazeGen;
  Cell cells[cellsWide*cellsTall];
  mazeGen.generate(cellsWide, cellsTall, cells);

  mapMazeCellsToGridTiles(cells, cellsWide, cellsTall, tileData, tilesPerCellX, tilesPerCellY);
  tidyJunctions(cellsWide, cellsTall, tileData, tilesPerCellX, tilesPerCellY);
  placeSpawnAndFinish(cellsWide, cellsTall, tileData, tilesPerCellX, tilesPerCellY);
}

void TiledMazeFactory::mapMazeCellsToGridTiles(Cell* cells, int cellsWide, int cellsTall, int* tileData, int tilesPerCellX, int tilesPerCellY) const {
  int tilesWide = TiledGridFactory::tileCountForCellDimension(cellsWide, tilesPerCellX);
  for (int y = 0; y < cellsTall; y++) {
    for (int x = 0; x < cellsWide; x++) {
      if (x < cellsWide-1 && (cells[Mazegen::locate(x, y, cellsWide)].getWalls() & Mazegen::EAST) != Mazegen::EAST) {
        for (int ty = 1; ty < tilesPerCellY-1; ty++) {
          tileData[TiledGridFactory::locateTile(tilesPerCellX-1, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY)] = Tile::FREE;
        }
      }
      if (y < cellsTall-1 && (cells[Mazegen::locate(x, y, cellsWide)].getWalls() & Mazegen::SOUTH) != Mazegen::SOUTH) {
        for (int tx = 1; tx < tilesPerCellX-1; tx++) {
          tileData[TiledGridFactory::locateTile(tx, tilesPerCellY-1, x, y, tilesWide, tilesPerCellX, tilesPerCellY)] = Tile::FREE;
        }
      }
    }
  }
}

void TiledMazeFactory::placeSpawnAndFinish(int cellsWide, int cellsTall, int* tileData, int tilesPerCellX, int tilesPerCellY) const {
  int tilesWide = TiledGridFactory::tileCountForCellDimension(cellsWide, tilesPerCellX);
  int topLeft = TiledGridFactory::locateTile(1, 1, 0, 0, tilesWide, tilesPerCellX, tilesPerCellY);
  int topRight = TiledGridFactory::locateTile(tilesPerCellX-2, 1, cellsWide-1, 0, tilesWide, tilesPerCellX, tilesPerCellY);
  int bottomLeft = TiledGridFactory::locateTile(1, tilesPerCellY-2, 0, cellsTall-1, tilesWide, tilesPerCellX, tilesPerCellY);
  int bottomRight = TiledGridFactory::locateTile(tilesPerCellX-2, tilesPerCellY-2, cellsWide-1, cellsTall-1, tilesWide, tilesPerCellX, tilesPerCellY);

  vector<int> corners;
  corners.push_back(topLeft);
  corners.push_back(topRight);
  corners.push_back(bottomLeft);
  corners.push_back(bottomRight);
  int randCorner = corners[rand() % corners.size()];
  tileData[randCorner] = Tile::PLAYER_SPAWN;
  corners.erase(std::remove(corners.begin(), corners.end(), randCorner), corners.end());
  randCorner = corners[rand() % corners.size()];
  tileData[randCorner] = Tile::FINISH;
}

int TiledMazeFactory::tileNorth(int* tileData, int tx, int ty, int x, int y, int tilesWide, int tilesPerCellX, int tilesPerCellY) const {
  return tileData[TiledGridFactory::locateTile(tx, ty-1, x, y, tilesWide, tilesPerCellX, tilesPerCellY)];
}
int TiledMazeFactory::tileSouth(int* tileData, int tx, int ty, int x, int y, int tilesWide, int tilesPerCellX, int tilesPerCellY) const {
  return tileData[TiledGridFactory::locateTile(tx, ty+1, x, y, tilesWide, tilesPerCellX, tilesPerCellY)];
}
int TiledMazeFactory::tileEast(int* tileData, int tx, int ty, int x, int y, int tilesWide, int tilesPerCellX, int tilesPerCellY) const {
  return tileData[TiledGridFactory::locateTile(tx+1, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY)];
}
int TiledMazeFactory::tileWest(int* tileData, int tx, int ty, int x, int y, int tilesWide, int tilesPerCellX, int tilesPerCellY) const {
  return tileData[TiledGridFactory::locateTile(tx-1, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY)];
}

bool TiledMazeFactory::isTopLeftCorner(int* tileData, int tx, int ty, int x, int y, int tilesWide, int cellsWide, int cellsTall, int tilesPerCellX, int tilesPerCellY) const {
  return  !TiledGridFactory::isOuterEdgeTile(tx, x, tilesPerCellX, cellsWide) &&
          !TiledGridFactory::isOuterEdgeTile(ty, y, tilesPerCellY, cellsTall) &&
          TiledGridFactory::isCornerTile(tx, ty, tilesPerCellX, tilesPerCellY) &&
          tileNorth(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) == Tile::FREE &&
          tileSouth(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) != Tile::FREE &&
          tileWest(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) == Tile::FREE &&
          tileEast(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) != Tile::FREE;
}

bool TiledMazeFactory::isTopRightCorner(int* tileData, int tx, int ty, int x, int y, int tilesWide, int cellsWide, int cellsTall, int tilesPerCellX, int tilesPerCellY) const {
  return  !TiledGridFactory::isOuterEdgeTile(tx, x, tilesPerCellX, cellsWide) &&
          !TiledGridFactory::isOuterEdgeTile(ty, y, tilesPerCellY, cellsTall) &&
          TiledGridFactory::isCornerTile(tx, ty, tilesPerCellX, tilesPerCellY) &&
          tileNorth(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) == Tile::FREE &&
          tileSouth(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) != Tile::FREE &&
          tileWest(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) != Tile::FREE &&
          tileEast(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) == Tile::FREE;
}

bool TiledMazeFactory::isBottomLeftCorner(int* tileData, int tx, int ty, int x, int y, int tilesWide, int cellsWide, int cellsTall, int tilesPerCellX, int tilesPerCellY) const {
  return  !TiledGridFactory::isOuterEdgeTile(tx, x, tilesPerCellX, cellsWide) &&
          !TiledGridFactory::isOuterEdgeTile(ty, y, tilesPerCellY, cellsTall) &&
          TiledGridFactory::isCornerTile(tx, ty, tilesPerCellX, tilesPerCellY) &&
          tileNorth(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) != Tile::FREE &&
          tileSouth(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) == Tile::FREE &&
          tileWest(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) == Tile::FREE &&
          tileEast(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) != Tile::FREE;
}

bool TiledMazeFactory::isBottomRightCorner(int* tileData, int tx, int ty, int x, int y, int tilesWide, int cellsWide, int cellsTall, int tilesPerCellX, int tilesPerCellY) const {
  return  !TiledGridFactory::isOuterEdgeTile(tx, x, tilesPerCellX, cellsWide) &&
          !TiledGridFactory::isOuterEdgeTile(ty, y, tilesPerCellY, cellsTall) &&
          TiledGridFactory::isCornerTile(tx, ty, tilesPerCellX, tilesPerCellY) &&
          tileNorth(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) != Tile::FREE &&
          tileSouth(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) == Tile::FREE &&
          tileWest(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) != Tile::FREE &&
          tileEast(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) == Tile::FREE;
}

bool TiledMazeFactory::isCrossRoads(int* tileData, int tx, int ty, int x, int y, int tilesWide, int cellsWide, int cellsTall, int tilesPerCellX, int tilesPerCellY) const {
  return  !TiledGridFactory::isOuterEdgeTile(tx, x, tilesPerCellX, cellsWide) &&
          !TiledGridFactory::isOuterEdgeTile(ty, y, tilesPerCellY, cellsTall) &&
          TiledGridFactory::isCornerTile(tx, ty, tilesPerCellX, tilesPerCellY) &&
          tileNorth(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) == Tile::FREE &&
          tileSouth(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) == Tile::FREE &&
          tileWest(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) == Tile::FREE &&
          tileEast(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) == Tile::FREE;
}

bool TiledMazeFactory::isTJunction(int* tileData, int tx, int ty, int x, int y, int tilesWide, int cellsWide, int cellsTall, int tilesPerCellX, int tilesPerCellY) const {
  return  !TiledGridFactory::isOuterEdgeTile(tx, x, tilesPerCellX, cellsWide) &&
          TiledGridFactory::isCornerTile(tx, ty, tilesPerCellX, tilesPerCellY) &&
          (ty != tilesPerCellY-1 && y != cellsTall-1) &&
          ((ty == 0 && y == 0) ||
            tileNorth(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) == Tile::FREE) &&
          tileSouth(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) != Tile::FREE &&
          tileWest(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) != Tile::FREE &&
          tileEast(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) != Tile::FREE;
}

bool TiledMazeFactory::isInvertedTJunction(int* tileData, int tx, int ty, int x, int y, int tilesWide, int cellsWide, int cellsTall, int tilesPerCellX, int tilesPerCellY) const {
  return  !TiledGridFactory::isOuterEdgeTile(tx, x, tilesPerCellX, cellsWide) &&
          TiledGridFactory::isCornerTile(tx, ty, tilesPerCellX, tilesPerCellY) &&
          (ty != 0 && y != 0) &&
          ((ty == tilesPerCellY-1 && y == cellsTall-1) ||
            tileSouth(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) == Tile::FREE) &&
          tileNorth(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) != Tile::FREE &&
          tileWest(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) != Tile::FREE &&
          tileEast(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) != Tile::FREE;
}

bool TiledMazeFactory::isLeftTJunction(int* tileData, int tx, int ty, int x, int y, int tilesWide, int cellsWide, int cellsTall, int tilesPerCellX, int tilesPerCellY) const {
  return  !TiledGridFactory::isOuterEdgeTile(ty, y, tilesPerCellY, cellsTall) &&
          TiledGridFactory::isCornerTile(tx, ty, tilesPerCellX, tilesPerCellY) &&
          (tx != 0 && x != 0) &&
          ((tx == tilesPerCellX-1 && x == cellsWide-1) ||
            tileEast(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) == Tile::FREE) &&
          tileNorth(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) != Tile::FREE &&
          tileWest(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) != Tile::FREE &&
          tileSouth(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) != Tile::FREE;
}

bool TiledMazeFactory::isRightTJunction(int* tileData, int tx, int ty, int x, int y, int tilesWide, int cellsWide, int cellsTall, int tilesPerCellX, int tilesPerCellY) const {
  return  !TiledGridFactory::isOuterEdgeTile(ty, y, tilesPerCellY, cellsTall) &&
          TiledGridFactory::isCornerTile(tx, ty, tilesPerCellX, tilesPerCellY) &&
          (tx != tilesPerCellX-1 && x != cellsWide-1) &&
          ((tx == 0 && x == 0) ||
            tileWest(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) == Tile::FREE) &&
          tileSouth(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) != Tile::FREE &&
          tileNorth(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) != Tile::FREE &&
          tileEast(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) != Tile::FREE;
}

bool TiledMazeFactory::isVerticalWall(int* tileData, int tx, int ty, int x, int y, int tilesWide, int cellsWide, int cellsTall, int tilesPerCellX, int tilesPerCellY) const {
  return  !TiledGridFactory::isOuterEdgeTile(ty, y, tilesPerCellY, cellsTall) &&
          TiledGridFactory::isEdgeTile(tx, tilesPerCellX) &&
          ((tileNorth(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) != Tile::FREE &&
            tileSouth(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) != Tile::FREE) ||
            tileNorth(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) !=
            tileSouth(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY)) &&
          ((tx == 0 && x == 0) ||
            tileWest(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) == Tile::FREE) &&
          ((tx == tilesPerCellX-1 && x == cellsWide-1) ||
            tileEast(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) == Tile::FREE);
}

bool TiledMazeFactory::isHorizontalWall(int* tileData, int tx, int ty, int x, int y, int tilesWide, int cellsWide, int cellsTall, int tilesPerCellX, int tilesPerCellY) const {
  return  !TiledGridFactory::isOuterEdgeTile(tx, x, tilesPerCellX, cellsWide) &&
          TiledGridFactory::isEdgeTile(ty, tilesPerCellY) &&
          ((tileWest(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) != Tile::FREE &&
            tileEast(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) != Tile::FREE) ||
            tileWest(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) !=
            tileEast(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY)) &&
          ((ty == 0 && y == 0) ||
            tileNorth(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) == Tile::FREE) &&
          ((ty == tilesPerCellY-1 && y == cellsTall-1) ||
            tileSouth(tileData, tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY) == Tile::FREE);
}

void TiledMazeFactory::tidyJunctions(int cellsWide, int cellsTall, int* tileData, int tilesPerCellX, int tilesPerCellY) const {
  int tilesWide = TiledGridFactory::tileCountForCellDimension(cellsWide, tilesPerCellX);
  for (int y = 0; y < cellsTall; y++) {
    for (int x = 0; x < cellsWide; x++) {
      for (int ty = 0; ty < tilesPerCellY; ty+=tilesPerCellY-1) {
        for (int tx = 0; tx < tilesPerCellX; tx+=tilesPerCellX-1) {
          if (TiledGridFactory::isOuterCornerTile(tx, ty, x, y, tilesPerCellX, tilesPerCellY, cellsWide, cellsTall)) {
            continue;
          }
          if (isCrossRoads(tileData, tx, ty, x, y, tilesWide, cellsWide, cellsTall, tilesPerCellX, tilesPerCellY)) {
            tileData[TiledGridFactory::locateTile(tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY)] = Tile::CROSSROADS;
          }
          else if (isTopLeftCorner(tileData, tx, ty, x, y, tilesWide, cellsWide, cellsTall, tilesPerCellX, tilesPerCellY)) {
            tileData[TiledGridFactory::locateTile(tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY)] = Tile::TOP_LEFT_CORNER;
          }
          else if (isTopRightCorner(tileData, tx, ty, x, y, tilesWide, cellsWide, cellsTall, tilesPerCellX, tilesPerCellY)) {
            tileData[TiledGridFactory::locateTile(tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY)] = Tile::TOP_RIGHT_CORNER;
          }
          else if (isBottomLeftCorner(tileData, tx, ty, x, y, tilesWide, cellsWide, cellsTall, tilesPerCellX, tilesPerCellY)) {
            tileData[TiledGridFactory::locateTile(tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY)] = Tile::BOTTOM_LEFT_CORNER;
          }
          else if (isBottomRightCorner(tileData, tx, ty, x, y, tilesWide, cellsWide, cellsTall, tilesPerCellX, tilesPerCellY)) {
            tileData[TiledGridFactory::locateTile(tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY)] = Tile::BOTTOM_RIGHT_CORNER;
          }
          else if (isTJunction(tileData, tx, ty, x, y, tilesWide, cellsWide, cellsTall, tilesPerCellX, tilesPerCellY)) {
            tileData[TiledGridFactory::locateTile(tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY)] = Tile::T_JUNCTION;
          }
          else if (isInvertedTJunction(tileData, tx, ty, x, y, tilesWide, cellsWide, cellsTall, tilesPerCellX, tilesPerCellY)) {
            tileData[TiledGridFactory::locateTile(tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY)] = Tile::INVERTED_T_JUNCTION;
          }
          else if (isLeftTJunction(tileData, tx, ty, x, y, tilesWide, cellsWide, cellsTall, tilesPerCellX, tilesPerCellY)) {
            tileData[TiledGridFactory::locateTile(tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY)] = Tile::LEFT_T_JUNCTION;
          }
          else if (isRightTJunction(tileData, tx, ty, x, y, tilesWide, cellsWide, cellsTall, tilesPerCellX, tilesPerCellY)) {
            tileData[TiledGridFactory::locateTile(tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY)] = Tile::RIGHT_T_JUNCTION;
          }
          else if (isVerticalWall(tileData, tx, ty, x, y, tilesWide, cellsWide, cellsTall, tilesPerCellX, tilesPerCellY)) {
            tileData[TiledGridFactory::locateTile(tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY)] = Tile::VERTICAL_WALL;
          }
          else if (isHorizontalWall(tileData, tx, ty, x, y, tilesWide, cellsWide, cellsTall, tilesPerCellX, tilesPerCellY)) {
            tileData[TiledGridFactory::locateTile(tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY)] = Tile::HORIZONTAL_WALL;
          }
        }
      }
    }
  }
}
