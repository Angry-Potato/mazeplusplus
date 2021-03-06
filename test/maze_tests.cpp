#include "doctest.h"
#include "../src/point.h"
#include "../src/maze.h"

TEST_SUITE("Maze") {
  TEST_CASE("can initialise with array of free tiles") {
    const int tileData[] = {
      0, 0, 0, 0, 0
    };
    Maze sut(tileData, 5, 1);

    CHECK(sut.isFree(0,0) == true);
  }
  TEST_CASE("marks tiles as not free correctly") {
    const int tileData[] = {
      1, 1, 1, 1, 1,
      1, 0, 0, 0, 1,
      1, 1, 1, 1, 1
    };
    Maze sut(tileData, 5, 3);

    CHECK(sut.isFree(0,0) == false);
    CHECK(sut.isFree(1,1) == true);
    CHECK(sut.isFree(3,2) == false);
  }
}
