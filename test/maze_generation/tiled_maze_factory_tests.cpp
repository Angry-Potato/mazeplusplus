#include "../doctest.h"
#include "../../src/maze_generation/tiled_maze_factory.h"

TEST_SUITE("TiledMazeFactory") {
  TEST_CASE("tileCountForMazeOfSize returns correct count") {
    TiledMazeFactory sut;

    CHECK(sut.tileCountForMazeOfSize(1, 1) == 9);
    CHECK(sut.tileCountForMazeOfSize(1, 2) == 15);
    CHECK(sut.tileCountForMazeOfSize(2, 2) == 25);
    CHECK(sut.tileCountForMazeOfSize(2, 3) == 35);
    CHECK(sut.tileCountForMazeOfSize(3, 3) == 49);
  }
  TEST_CASE("locateTile returns correct location") {
    TiledMazeFactory sut;
    int tilesWide = 7;
    int tilesPerCellX = 3;
    int tilesPerCellY = 3;

    CHECK(sut.locateTile(0, 0, 0, 0, tilesWide, tilesPerCellX, tilesPerCellY) == 0);
    CHECK(sut.locateTile(1, 0, 0, 0, tilesWide, tilesPerCellX, tilesPerCellY) == 1);
    CHECK(sut.locateTile(2, 0, 0, 0, tilesWide, tilesPerCellX, tilesPerCellY) == 2);
    CHECK(sut.locateTile(0, 0, 1, 0, tilesWide, tilesPerCellX, tilesPerCellY) == 2);
    CHECK(sut.locateTile(1, 0, 1, 0, tilesWide, tilesPerCellX, tilesPerCellY) == 3);
    CHECK(sut.locateTile(2, 0, 1, 0, tilesWide, tilesPerCellX, tilesPerCellY) == 4);
    CHECK(sut.locateTile(0, 0, 2, 0, tilesWide, tilesPerCellX, tilesPerCellY) == 4);
  }
}

// ((tpx-1)*cellx+tx) + (((tpy-1)*celly+ty)*tilesWide)
