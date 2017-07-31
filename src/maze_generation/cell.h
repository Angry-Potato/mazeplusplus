#ifndef __CELL_H_
#define __CELL_H_

class Cell {
private:
    int walls;
    void init(const int y, const int x, const int walls);
public:
    int Y;
    int X;
    enum WALL { WALL_NORTH = 0x0008, WALL_EAST = 0x0004,
        WALL_SOUTH  = 0x0002, WALL_WEST = 0x0001,
        WALL_ALL = 0x000f, WALL_NONE = 0x0000 };
    Cell();
    Cell(const int y, const int x);
    Cell(const int y, const int x, const int stat);
    void removeWall(const int w);
    int getWalls() const;
    void setWalls(const int w);
    void setPosition(const int y, const int x);
    inline bool hasWall(const int dir) const {
      return (walls & dir) == dir;
    };
};

#endif
