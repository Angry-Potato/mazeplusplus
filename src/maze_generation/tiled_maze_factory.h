#ifndef TILED_MAZE_FACTORY_H
#define TILED_MAZE_FACTORY_H

class TiledMazeFactory {
public :
  inline int tileCountForCellDimension(int dimension) const {
    return ((dimension * 3 ) - (dimension - 1));
  };
  inline int tileCountForMazeOfSize(int width, int height) const {
    return tileCountForCellDimension(width)*tileCountForCellDimension(height);
  };
  inline int locateTile(int tileX, int tileY, int cellX, int cellY, int mazeWidthInTiles, int tilesPerCellX, int tilesPerCellY) const {
    return ((tilesPerCellX-1)*cellX+tileX) + (((tilesPerCellY-1)*cellY+tileY)*mazeWidthInTiles);
  };
  inline bool isEdgeTile(int tileX, int tileY, int tilesPerCellX, int tilesPerCellY) const {
    return (tileX % (tilesPerCellX-1) == 0) || (tileY % (tilesPerCellY-1) == 0);
  };

  void generate(int width, int height, int* tileData);
};
#endif
