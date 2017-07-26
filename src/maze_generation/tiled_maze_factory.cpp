#include "tiled_maze_factory.h"
#include "tiled_grid_factory.h"
#include "cell.h"
#include "mazegen.h"
#include "../tile.h"

void TiledMazeFactory::generate(int cellsWide, int cellsTall, int* tileData, int tilesPerCellX, int tilesPerCellY) const {
  TiledGridFactory tiledGridFactory;
  tiledGridFactory.generate(cellsWide, cellsTall, tileData, tilesPerCellX, tilesPerCellY);

  Mazegen mazeGen;
  Cell cells[cellsWide*cellsTall];
  mazeGen.generate(cellsWide, cellsTall, cells);

  mapMazeCellsToGridTiles(cells, cellsWide, cellsTall, tileData, tilesPerCellX, tilesPerCellY);
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
