#include "../doctest.h"
#include "../../src/maze_generation/mazegen.h"
#include "../../src/maze_generation/cell.h"

TEST_SUITE("Mazegen") {
  TEST_CASE("prepMaze sets all cells position correctly") {
    Mazegen sut;
    int width = 10;
    int height = 10;
    Cell cells[width*height];

    sut.prepMaze(cells, width, height);

    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        CHECK(cells[x+y*width].getColumn() == x);
        CHECK(cells[x+y*width].getRow() == y);
      }
    }
  }
  TEST_CASE("prepMaze sets all cells to have all walls") {
    Mazegen sut;
    int width = 10;
    int height = 10;
    Cell cells[width*height];

    sut.prepMaze(cells, width, height);

    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        CHECK(cells[x+y*width].getWalls() == Cell::WALL_ALL);
      }
    }
  }
}
