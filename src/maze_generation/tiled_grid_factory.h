#ifndef TILED_GRID_FACTORY_H
#define TILED_GRID_FACTORY_H

class TiledGridFactory {
public :
  static inline int tileCountForCellDimension(int dimension, int tilesPerCell) {
    return ((dimension * tilesPerCell ) - (dimension - 1));
  };
  static inline int tileCountForMazeOfSize(int width, int height, int tilesPerCellX, int tilesPerCellY) {
    return tileCountForCellDimension(width, tilesPerCellX)*tileCountForCellDimension(height, tilesPerCellY);
  };
  static inline int locateTile(int tileX, int tileY, int cellX, int cellY, int mazeWidthInTiles, int tilesPerCellX, int tilesPerCellY) {
    return ((tilesPerCellX-1)*cellX+tileX) + (((tilesPerCellY-1)*cellY+tileY)*mazeWidthInTiles);
  };
  static inline int isCornerTile(int tileX, int tileY, int tilesPerCellX, int tilesPerCellY) {
    return isEdgeTile(tileX, tilesPerCellX) && isEdgeTile(tileY, tilesPerCellY);
  };
  static inline int isOuterCornerTile(int tx, int ty, int x, int y, int tilesPerCellX, int tilesPerCellY, int cellsWide, int cellsTall) {
    return  (tx == 0 && ty == 0 && x == 0 && y == 0) ||
            (tx == 0 && ty == tilesPerCellY-1 && x == 0 && y == cellsTall-1) ||
            (tx == tilesPerCellX-1 && ty == 0 && x == cellsWide-1 && y == 0) ||
            (tx == tilesPerCellX-1 && ty == tilesPerCellY-1 && x == cellsWide-1 && y == cellsTall-1);
  };
  static inline bool isEdgeTile(int coordinateOnAxis, int tilesPerCellAlongSameAxis) {
    return coordinateOnAxis % (tilesPerCellAlongSameAxis-1) == 0;
  };
  static inline bool isOuterEdgeTile(int tileCoordinateOnAxis, int cellCoordinateOnAxis, int tilesPerCellInDimension, int mazeDimensionInCells) {
    return  (tileCoordinateOnAxis == 0 && cellCoordinateOnAxis == 0) ||
            (tileCoordinateOnAxis == tilesPerCellInDimension-1 && cellCoordinateOnAxis == mazeDimensionInCells-1);
  };

  void generate(int width, int height, int* tileData, int tilesPerCellX, int tilesPerCellY) const;
  void spawnFreeTiles(int width, int height, int* tileData, int tilesPerCellX, int tilesPerCellY) const;
  void spawnWalls(int width, int height, int* tileData, int tilesPerCellX, int tilesPerCellY) const;
  void spawnJunctions(int width, int height, int* tileData, int tilesPerCellX, int tilesPerCellY) const;
  void spawnOuterCorners(int width, int height, int* tileData, int tilesPerCellX, int tilesPerCellY) const;
};
#endif
