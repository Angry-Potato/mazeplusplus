#include "../doctest.h"
#include "../../src/maze_generation/mazegen.h"
#include "../../src/maze_generation/cell.h"
#include <algorithm>
#include <vector>

TEST_SUITE("Mazegen") {
  TEST_CASE("prepMaze sets all cells position correctly") {
    Mazegen sut;
    int width = 10;
    int height = 10;
    Cell cells[width*height];

    sut.prepMaze(cells, width, height);

    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        CHECK(cells[x+y*width].X == x);
        CHECK(cells[x+y*width].Y == y);
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

    CHECK(topLeft->X == sut.cellNeighbour(cells, width, height, bottomLeft->X, bottomLeft->Y, Mazegen::NORTH)->X);
    CHECK(topLeft->Y == sut.cellNeighbour(cells, width, height, bottomLeft->X, bottomLeft->Y, Mazegen::NORTH)->Y);
    CHECK(bottomLeft->X == sut.cellNeighbour(cells, width, height, topLeft->X, topLeft->Y, Mazegen::SOUTH)->X);
    CHECK(bottomLeft->Y == sut.cellNeighbour(cells, width, height, topLeft->X, topLeft->Y, Mazegen::SOUTH)->Y);
    CHECK(topRight->X == sut.cellNeighbour(cells, width, height, topLeft->X, topLeft->Y, Mazegen::EAST)->X);
    CHECK(topRight->Y == sut.cellNeighbour(cells, width, height, topLeft->X, topLeft->Y, Mazegen::EAST)->Y);
    CHECK(topLeft->X == sut.cellNeighbour(cells, width, height, topRight->X, topRight->Y, Mazegen::WEST)->X);
    CHECK(topLeft->Y == sut.cellNeighbour(cells, width, height, topRight->X, topRight->Y, Mazegen::WEST)->Y);
  }
  TEST_CASE("cellNeighbour returns NULL when out of bounds") {
    Mazegen sut;
    int width = 1;
    int height = 1;
    Cell cells[width*height];
    sut.prepMaze(cells, width, height);

    Cell* cell = &(cells[0]);

    CHECK(sut.cellNeighbour(cells, width, height, cell->X, cell->Y, Mazegen::NORTH) == (Cell*)NULL);
    CHECK(sut.cellNeighbour(cells, width, height, cell->X, cell->Y, Mazegen::SOUTH) == (Cell*)NULL);
    CHECK(sut.cellNeighbour(cells, width, height, cell->X, cell->Y, Mazegen::EAST) == (Cell*)NULL);
    CHECK(sut.cellNeighbour(cells, width, height, cell->X, cell->Y, Mazegen::WEST) == (Cell*)NULL);
  }
  TEST_CASE("isDirAvailable returns false when out of bounds") {
    Mazegen sut;
    int width = 1;
    int height = 1;
    Cell cells[width*height];
    sut.prepMaze(cells, width, height);

    Cell* cell = &(cells[0]);

    CHECK(sut.isDirAvailable(cells, width, height, cell->X, cell->Y, Mazegen::NORTH) == false);
    CHECK(sut.isDirAvailable(cells, width, height, cell->X, cell->Y, Mazegen::SOUTH) == false);
    CHECK(sut.isDirAvailable(cells, width, height, cell->X, cell->Y, Mazegen::EAST) == false);
    CHECK(sut.isDirAvailable(cells, width, height, cell->X, cell->Y, Mazegen::WEST) == false);
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

    CHECK(sut.isDirAvailable(cells, width, height, bottomLeft->X, bottomLeft->Y, Mazegen::NORTH) == true);
    CHECK(sut.isDirAvailable(cells, width, height, topLeft->X, topLeft->Y, Mazegen::SOUTH) == true);
    CHECK(sut.isDirAvailable(cells, width, height, topLeft->X, topLeft->Y, Mazegen::EAST) == true);
    CHECK(sut.isDirAvailable(cells, width, height, topRight->X, topRight->Y, Mazegen::WEST) == true);
  }
  TEST_CASE("isDirAvailable returns false when dir not available") {
    Mazegen sut;
    int width = 2;
    int height = 2;
    Cell cells[width*height];
    sut.prepMaze(cells, width, height);

    Cell* topLeft = &(cells[0]);
    Cell* topRight = &(cells[1]);
    Cell* bottomLeft = &(cells[2]);
    Cell* bottomRight = &(cells[3]);

    sut.forgePath(cells, bottomLeft->X, bottomLeft->Y, width, height, Mazegen::NORTH);
    sut.forgePath(cells, bottomRight->X, bottomRight->Y, width, height, Mazegen::NORTH);

    CHECK(sut.isDirAvailable(cells, width, height, bottomLeft->X, bottomLeft->Y, Mazegen::NORTH) == false);
    CHECK(sut.isDirAvailable(cells, width, height, topLeft->X, topLeft->Y, Mazegen::SOUTH) == false);
    CHECK(sut.isDirAvailable(cells, width, height, topLeft->X, topLeft->Y, Mazegen::EAST) == false);
    CHECK(sut.isDirAvailable(cells, width, height, topRight->X, topRight->Y, Mazegen::WEST) == false);
  }
  TEST_CASE("forgePath removes correct walls from both cells in vertical forge") {
    Mazegen sut;
    int width = 1;
    int height = 2;
    Cell cells[width*height];
    sut.prepMaze(cells, width, height);

    Cell* topLeft = &(cells[0]);
    Cell* bottomLeft = &(cells[1]);

    sut.forgePath(cells, bottomLeft->X, bottomLeft->Y, width, height, Mazegen::NORTH);
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

    sut.forgePath(cells, topLeft->X, topLeft->Y, width, height, Mazegen::EAST);
    CHECK((topLeft->getWalls() & Mazegen::NORTH) == Mazegen::NORTH);
    CHECK((topLeft->getWalls() & Mazegen::SOUTH) == Mazegen::SOUTH);
    CHECK((topLeft->getWalls() & Mazegen::EAST) != Mazegen::EAST);
    CHECK((topLeft->getWalls() & Mazegen::WEST) == Mazegen::WEST);
    CHECK((topRight->getWalls() & Mazegen::SOUTH) == Mazegen::SOUTH);
    CHECK((topRight->getWalls() & Mazegen::NORTH) == Mazegen::NORTH);
    CHECK((topRight->getWalls() & Mazegen::EAST) == Mazegen::EAST);
    CHECK((topRight->getWalls() & Mazegen::WEST) != Mazegen::WEST);
  }
  TEST_CASE("setAvailableDirs sets correct directions as available") {
    Mazegen sut;
    int width = 2;
    int height = 2;
    Cell cells[width*height];
    sut.prepMaze(cells, width, height);

    Cell* topLeft = &(cells[0]);
    Cell* topRight = &(cells[1]);
    Cell* bottomLeft = &(cells[2]);
    Cell* bottomRight = &(cells[3]);

    sut.forgePath(cells, topLeft->X, topLeft->Y, width, height, Mazegen::EAST);

    std::vector<Mazegen::DIR> availableDirs;
    sut.setAvailableDirs(availableDirs, cells, topLeft->X, topLeft->Y, width, height);

    CHECK((std::find(availableDirs.begin(), availableDirs.end(), Mazegen::EAST) != availableDirs.end()) != true);
    CHECK((std::find(availableDirs.begin(), availableDirs.end(), Mazegen::SOUTH) != availableDirs.end()) == true);
  }
}
