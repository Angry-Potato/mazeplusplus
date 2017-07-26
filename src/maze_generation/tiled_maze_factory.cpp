#include "tiled_maze_factory.h"
#include "cell.h"
#include "mazegen.h"
#include "../tile.h"

void TiledMazeFactory::generate(int cellsWide, int cellsTall, int* tileData, int tilesPerCellX, int tilesPerCellY) {
  Mazegen mazeGen;
  Cell cells[cellsWide*cellsTall];
  mazeGen.generate(cellsWide, cellsTall, cells);
  int tilesWide = tileCountForCellDimension(cellsWide, tilesPerCellX);

  for (int y = 0; y < cellsTall; y++) {
    for (int x = 0; x < cellsWide; x++) {
      Cell* cell = &(cells[x+y*cellsWide]);

      for (int ty = 0; ty < tilesPerCellY; ty++) {
        for (int tx = 0; tx < tilesPerCellX; tx++) {
          int tileLoc = locateTile(tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY);

          if (!isEdgeTile(tx, ty, tilesPerCellX, tilesPerCellY)) {
            tileData[tileLoc] = Tile::FREE;
          }
          else {
            if (x == 0 && y == 0 && tx == 0 && ty == 0) {
              tileData[tileLoc] = Tile::TOP_LEFT_CORNER;
            }
            else if (x == cellsWide-1 && y == 0 && tx == tilesPerCellX-1 && ty == 0) {
              tileData[tileLoc] = Tile::TOP_RIGHT_CORNER;
            }
            else if (x == 0 && y == cellsTall-1 && tx == 0 && ty == tilesPerCellY-1) {
              tileData[tileLoc] = Tile::BOTTOM_LEFT_CORNER;
            }
            else if (x == cellsWide-1 && y == cellsTall-1 && tx == tilesPerCellX-1 && ty == tilesPerCellY-1) {
              tileData[tileLoc] = Tile::BOTTOM_RIGHT_CORNER;
            }
            else {
              tileData[tileLoc] = Tile::FREE;
            }
          }
        }
      }
    }
  }
}
