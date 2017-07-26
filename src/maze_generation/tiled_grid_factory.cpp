#include "tiled_grid_factory.h"
#include "cell.h"
#include "mazegen.h"
#include "../tile.h"

void TiledGridFactory::generate(int cellsWide, int cellsTall, int* tileData, int tilesPerCellX, int tilesPerCellY) const {
  Mazegen mazeGen;
  Cell cells[cellsWide*cellsTall];
  mazeGen.generate(cellsWide, cellsTall, cells);
    // Cell* cell = &(cells[x+y*cellsWide]);
  spawnFreeTiles(cellsWide, cellsTall, tileData, tilesPerCellX, tilesPerCellY);
  spawnWalls(cellsWide, cellsTall, tileData, tilesPerCellX, tilesPerCellY);
  spawnJunctions(cellsWide, cellsTall, tileData, tilesPerCellX, tilesPerCellY);
  spawnOuterCorners(cellsWide, cellsTall, tileData, tilesPerCellX, tilesPerCellY);
}

void TiledGridFactory::spawnFreeTiles(int cellsWide, int cellsTall, int* tileData, int tilesPerCellX, int tilesPerCellY) const {
  int tilesWide = tileCountForCellDimension(cellsWide, tilesPerCellX);
  for (int y = 0; y < cellsTall; y++) {
    for (int x = 0; x < cellsWide; x++) {
      for (int ty = 0; ty < tilesPerCellY; ty++) {
        for (int tx = 0; tx < tilesPerCellX; tx++) {
          tileData[locateTile(tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY)] = Tile::FREE;
        }
      }
    }
  }
}

void TiledGridFactory::spawnWalls(int cellsWide, int cellsTall, int* tileData, int tilesPerCellX, int tilesPerCellY) const {
  int tilesWide = tileCountForCellDimension(cellsWide, tilesPerCellX);
  for (int y = 0; y < cellsTall; y++) {
    for (int x = 0; x < cellsWide; x++) {
      for (int ty = 0; ty < tilesPerCellY; ty++) {
        for (int tx = 0; tx < tilesPerCellX; tx++) {
          if (isEdgeTile(tx, tilesPerCellX)) {
            tileData[locateTile(tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY)] = Tile::VERTICAL_WALL;
          }
          else if (isEdgeTile(ty, tilesPerCellY)) {
            tileData[locateTile(tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY)] = Tile::HORIZONTAL_WALL;
          }
        }
      }
    }
  }
}

void TiledGridFactory::spawnJunctions(int cellsWide, int cellsTall, int* tileData, int tilesPerCellX, int tilesPerCellY) const {
  int tilesWide = tileCountForCellDimension(cellsWide, tilesPerCellX);
  for (int y = 0; y < cellsTall; y++) {
    for (int x = 0; x < cellsWide; x++) {
      for (int ty = 0; ty < tilesPerCellY; ty++) {
        for (int tx = 0; tx < tilesPerCellX; tx++) {
          if (isOuterCornerTile(tx, ty, x, y, tilesPerCellX, tilesPerCellY, cellsWide, cellsTall)) {
            continue;
          }
          if (isCornerTile(tx, ty, tilesPerCellX, tilesPerCellY)) {
            if (isOuterEdgeTile(tx, x, tilesPerCellX, cellsWide)) {
              tileData[locateTile(tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY)] = tx == 0 ? Tile::RIGHT_T_JUNCTION : Tile::LEFT_T_JUNCTION;
            }
            else if (isOuterEdgeTile(ty, y, tilesPerCellY, cellsTall)) {
              tileData[locateTile(tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY)] = ty == 0 ? Tile::T_JUNCTION : Tile::INVERTED_T_JUNCTION;
            }
            else {
              tileData[locateTile(tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY)] = Tile::CROSSROADS;
            }
          }
        }
      }
    }
  }
}

void TiledGridFactory::spawnOuterCorners(int cellsWide, int cellsTall, int* tileData, int tilesPerCellX, int tilesPerCellY) const {
  int tilesWide = tileCountForCellDimension(cellsWide, tilesPerCellX);
  tileData[locateTile(0, 0, 0, 0, tilesWide, tilesPerCellX, tilesPerCellY)] = Tile::TOP_LEFT_CORNER;
  tileData[locateTile(tilesPerCellX-1, 0, cellsWide-1, 0, tilesWide, tilesPerCellX, tilesPerCellY)] = Tile::TOP_RIGHT_CORNER;
  tileData[locateTile(0, tilesPerCellY-1, 0, cellsTall-1, tilesWide, tilesPerCellX, tilesPerCellY)] = Tile::BOTTOM_LEFT_CORNER;
  tileData[locateTile(tilesPerCellX-1, tilesPerCellY-1, cellsWide-1, cellsTall-1, tilesWide, tilesPerCellX, tilesPerCellY)] = Tile::BOTTOM_RIGHT_CORNER;
}
