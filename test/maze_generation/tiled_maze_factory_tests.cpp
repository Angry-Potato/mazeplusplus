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
}
