#ifndef TILED_MAZE_FACTORY_H
#define TILED_MAZE_FACTORY_H

class TiledMazeFactory {
public :
  inline int tileCountForMazeOfSize(int width, int height) {
    return ((width * 3 ) - (width - 1))*((height * 3 ) - (height - 1));
  };

  void generate(int width, int height, int* tileData);
};
#endif
