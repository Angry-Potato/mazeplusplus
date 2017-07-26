#ifndef TILED_MAZE_FACTORY_H
#define TILED_MAZE_FACTORY_H

class Cell;
class TiledMazeFactory {
public :
  void generate(int cellsWide, int cellsTall, int* tileData, int tilesPerCellX, int tilesPerCellY) const;
  void mapMazeCellsToGridTiles(Cell* cells, int cellsWide, int cellsTall, int* tileData, int tilesPerCellX, int tilesPerCellY) const;
};
#endif
