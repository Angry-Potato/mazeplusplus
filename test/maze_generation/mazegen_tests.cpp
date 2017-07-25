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
  TEST_CASE("cellNeighbour gets the correct cell") {
    Mazegen sut;
    int width = 2;
    int height = 2;
    Cell cells[width*height];
    sut.prepMaze(cells, width, height);

    Cell* topLeft = &(cells[0]);
    Cell* topRight = &(cells[1]);
    Cell* bottomLeft = &(cells[2]);
    Cell* bottomRight = &(cells[3]);

    CHECK(topLeft->getColumn() == sut.cellNeighbour(cells, width, height, bottomLeft->getColumn(), bottomLeft->getRow(), Mazegen::NORTH)->getColumn());
    CHECK(topLeft->getRow() == sut.cellNeighbour(cells, width, height, bottomLeft->getColumn(), bottomLeft->getRow(), Mazegen::NORTH)->getRow());
    CHECK(bottomLeft->getColumn() == sut.cellNeighbour(cells, width, height, topLeft->getColumn(), topLeft->getRow(), Mazegen::SOUTH)->getColumn());
    CHECK(bottomLeft->getRow() == sut.cellNeighbour(cells, width, height, topLeft->getColumn(), topLeft->getRow(), Mazegen::SOUTH)->getRow());
    CHECK(topRight->getColumn() == sut.cellNeighbour(cells, width, height, topLeft->getColumn(), topLeft->getRow(), Mazegen::EAST)->getColumn());
    CHECK(topRight->getRow() == sut.cellNeighbour(cells, width, height, topLeft->getColumn(), topLeft->getRow(), Mazegen::EAST)->getRow());
    CHECK(topLeft->getColumn() == sut.cellNeighbour(cells, width, height, topRight->getColumn(), topRight->getRow(), Mazegen::WEST)->getColumn());
    CHECK(topLeft->getRow() == sut.cellNeighbour(cells, width, height, topRight->getColumn(), topRight->getRow(), Mazegen::WEST)->getRow());
  }
  TEST_CASE("cellNeighbour returns NULL when out of bounds") {
    Mazegen sut;
    int width = 1;
    int height = 1;
    Cell cells[width*height];
    sut.prepMaze(cells, width, height);

    Cell* cell = &(cells[0]);

    CHECK(sut.cellNeighbour(cells, width, height, cell->getColumn(), cell->getRow(), Mazegen::NORTH) == (Cell*)NULL);
    CHECK(sut.cellNeighbour(cells, width, height, cell->getColumn(), cell->getRow(), Mazegen::SOUTH) == (Cell*)NULL);
    CHECK(sut.cellNeighbour(cells, width, height, cell->getColumn(), cell->getRow(), Mazegen::EAST) == (Cell*)NULL);
    CHECK(sut.cellNeighbour(cells, width, height, cell->getColumn(), cell->getRow(), Mazegen::WEST) == (Cell*)NULL);
  }
  TEST_CASE("isDirAvailable returns false when out of bounds") {
    Mazegen sut;
    int width = 1;
    int height = 1;
    Cell cells[width*height];
    sut.prepMaze(cells, width, height);

    Cell* cell = &(cells[0]);

    CHECK(sut.isDirAvailable(cells, width, height, cell->getColumn(), cell->getRow(), Mazegen::NORTH) == false);
    CHECK(sut.isDirAvailable(cells, width, height, cell->getColumn(), cell->getRow(), Mazegen::SOUTH) == false);
    CHECK(sut.isDirAvailable(cells, width, height, cell->getColumn(), cell->getRow(), Mazegen::EAST) == false);
    CHECK(sut.isDirAvailable(cells, width, height, cell->getColumn(), cell->getRow(), Mazegen::WEST) == false);
  }
  TEST_CASE("isDirAvailable returns true when dir available") {
    Mazegen sut;
    int width = 2;
    int height = 2;
    Cell cells[width*height];
    sut.prepMaze(cells, width, height);

    Cell* topLeft = &(cells[0]);
    Cell* topRight = &(cells[1]);
    Cell* bottomLeft = &(cells[2]);
    Cell* bottomRight = &(cells[3]);

    CHECK(sut.isDirAvailable(cells, width, height, bottomLeft->getColumn(), bottomLeft->getRow(), Mazegen::NORTH) == true);
    CHECK(sut.isDirAvailable(cells, width, height, topLeft->getColumn(), topLeft->getRow(), Mazegen::SOUTH) == true);
    CHECK(sut.isDirAvailable(cells, width, height, topLeft->getColumn(), topLeft->getRow(), Mazegen::EAST) == true);
    CHECK(sut.isDirAvailable(cells, width, height, topRight->getColumn(), topRight->getRow(), Mazegen::WEST) == true);
  }
  TEST_CASE("forgePath removes correct walls from both cells in vertical forge") {
    Mazegen sut;
    int width = 1;
    int height = 2;
    Cell cells[width*height];
    sut.prepMaze(cells, width, height);

    Cell* topLeft = &(cells[0]);
    Cell* bottomLeft = &(cells[1]);

    sut.forgePath(cells, bottomLeft->getColumn(), bottomLeft->getRow(), width, height, Mazegen::NORTH);
    CHECK((bottomLeft->getWalls() & Mazegen::NORTH) != Mazegen::NORTH);
    CHECK((bottomLeft->getWalls() & Mazegen::SOUTH) == Mazegen::SOUTH);
    CHECK((bottomLeft->getWalls() & Mazegen::EAST) == Mazegen::EAST);
    CHECK((bottomLeft->getWalls() & Mazegen::WEST) == Mazegen::WEST);
    CHECK((topLeft->getWalls() & Mazegen::SOUTH) != Mazegen::SOUTH);
    CHECK((topLeft->getWalls() & Mazegen::NORTH) == Mazegen::NORTH);
    CHECK((topLeft->getWalls() & Mazegen::EAST) == Mazegen::EAST);
    CHECK((topLeft->getWalls() & Mazegen::WEST) == Mazegen::WEST);
  }
  TEST_CASE("forgePath removes correct walls from both cells in horizontal forge") {
    Mazegen sut;
    int width = 2;
    int height = 1;
    Cell cells[width*height];
    sut.prepMaze(cells, width, height);

    Cell* topLeft = &(cells[0]);
    Cell* topRight = &(cells[1]);

    sut.forgePath(cells, topLeft->getColumn(), topLeft->getRow(), width, height, Mazegen::EAST);
    CHECK((topLeft->getWalls() & Mazegen::NORTH) == Mazegen::NORTH);
    CHECK((topLeft->getWalls() & Mazegen::SOUTH) == Mazegen::SOUTH);
    CHECK((topLeft->getWalls() & Mazegen::EAST) != Mazegen::EAST);
    CHECK((topLeft->getWalls() & Mazegen::WEST) == Mazegen::WEST);
    CHECK((topRight->getWalls() & Mazegen::SOUTH) == Mazegen::SOUTH);
    CHECK((topRight->getWalls() & Mazegen::NORTH) == Mazegen::NORTH);
    CHECK((topRight->getWalls() & Mazegen::EAST) == Mazegen::EAST);
    CHECK((topRight->getWalls() & Mazegen::WEST) != Mazegen::WEST);
  }
}
