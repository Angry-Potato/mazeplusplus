#ifndef TILED_MAZE_FACTORY_H
#define TILED_MAZE_FACTORY_H

class TiledMazeFactory {
public :
  inline int tileCountForCellDimension(int dimension, int tilesPerCell) const {
    return ((dimension * tilesPerCell ) - (dimension - 1));
  };
  inline int tileCountForMazeOfSize(int width, int height, int tilesPerCellX, int tilesPerCellY) const {
    return tileCountForCellDimension(width, tilesPerCellX)*tileCountForCellDimension(height, tilesPerCellY);
  };
  inline int locateTile(int tileX, int tileY, int cellX, int cellY, int mazeWidthInTiles, int tilesPerCellX, int tilesPerCellY) const {
    return ((tilesPerCellX-1)*cellX+tileX) + (((tilesPerCellY-1)*cellY+tileY)*mazeWidthInTiles);
  };
  inline int isCornerTile(int tileX, int tileY, int tilesPerCellX, int tilesPerCellY) const {
    return isEdgeTile(tileX, tilesPerCellX) && isEdgeTile(tileY, tilesPerCellY);
  };
  inline int isOuterCornerTile(int tx, int ty, int x, int y, int tilesPerCellX, int tilesPerCellY, int cellsWide, int cellsTall) const {
    return  (tx == 0 && ty == 0 && x == 0 && y == 0) ||
            (tx == 0 && ty == tilesPerCellY-1 && x == 0 && y == cellsTall-1) ||
            (tx == tilesPerCellX-1 && ty == 0 && x == cellsWide-1 && y == 0) ||
            (tx == tilesPerCellX-1 && ty == tilesPerCellY-1 && x == cellsWide-1 && y == cellsTall-1);
  };
  inline bool isEdgeTile(int coordinateOnAxis, int tilesPerCellAlongSameAxis) const {
    return coordinateOnAxis % (tilesPerCellAlongSameAxis-1) == 0;
  };
  inline bool isOuterEdgeTile(int tileCoordinateOnAxis, int cellCoordinateOnAxis, int tilesPerCellInDimension, int mazeDimensionInCells) const {
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
