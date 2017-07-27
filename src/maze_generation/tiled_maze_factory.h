#ifndef TILED_MAZE_FACTORY_H
#define TILED_MAZE_FACTORY_H

class Cell;
class TiledMazeFactory {
public :
  void generate(int cellsWide, int cellsTall, int* tileData, int tilesPerCellX, int tilesPerCellY) const;
  void mapMazeCellsToGridTiles(Cell* cells, int cellsWide, int cellsTall, int* tileData, int tilesPerCellX, int tilesPerCellY) const;
  void tidyJunctions(int cellsWide, int cellsTall, int* tileData, int tilesPerCellX, int tilesPerCellY) const;
  bool isCrossRoads(int* tileData, int tx, int ty, int x, int y, int tilesWide, int cellsWide, int cellsTall, int tilesPerCellX, int tilesPerCellY) const;
  bool isTopLeftCorner(int* tileData, int tx, int ty, int x, int y, int tilesWide, int cellsWide, int cellsTall, int tilesPerCellX, int tilesPerCellY) const;
  bool isTopRightCorner(int* tileData, int tx, int ty, int x, int y, int tilesWide, int cellsWide, int cellsTall, int tilesPerCellX, int tilesPerCellY) const;
  bool isBottomLeftCorner(int* tileData, int tx, int ty, int x, int y, int tilesWide, int cellsWide, int cellsTall, int tilesPerCellX, int tilesPerCellY) const;
  bool isBottomRightCorner(int* tileData, int tx, int ty, int x, int y, int tilesWide, int cellsWide, int cellsTall, int tilesPerCellX, int tilesPerCellY) const;
  bool isTJunction(int* tileData, int tx, int ty, int x, int y, int tilesWide, int cellsWide, int cellsTall, int tilesPerCellX, int tilesPerCellY) const;
  bool isInvertedTJunction(int* tileData, int tx, int ty, int x, int y, int tilesWide, int cellsWide, int cellsTall, int tilesPerCellX, int tilesPerCellY) const;
  bool isLeftTJunction(int* tileData, int tx, int ty, int x, int y, int tilesWide, int cellsWide, int cellsTall, int tilesPerCellX, int tilesPerCellY) const;
  bool isRightTJunction(int* tileData, int tx, int ty, int x, int y, int tilesWide, int cellsWide, int cellsTall, int tilesPerCellX, int tilesPerCellY) const;
  bool isVerticalWall(int* tileData, int tx, int ty, int x, int y, int tilesWide, int cellsWide, int cellsTall, int tilesPerCellX, int tilesPerCellY) const;
  bool isHorizontalWall(int* tileData, int tx, int ty, int x, int y, int tilesWide, int cellsWide, int cellsTall, int tilesPerCellX, int tilesPerCellY) const;
  int tileNorth(int* tileData, int tx, int ty, int x, int y, int tilesWide, int tilesPerCellX, int tilesPerCellY) const;
  int tileSouth(int* tileData, int tx, int ty, int x, int y, int tilesWide, int tilesPerCellX, int tilesPerCellY) const;
  int tileEast(int* tileData, int tx, int ty, int x, int y, int tilesWide, int tilesPerCellX, int tilesPerCellY) const;
  int tileWest(int* tileData, int tx, int ty, int x, int y, int tilesWide, int tilesPerCellX, int tilesPerCellY) const;
};
#endif
