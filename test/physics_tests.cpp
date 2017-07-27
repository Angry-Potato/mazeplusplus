#include "doctest.h"
#include "../src/physics.h"
#include "../src/point.h"
#include "../src/maze.h"
#include "../src/maze_generation/tiled_grid_factory.h"

TEST_SUITE("Physics") {
  TEST_CASE("isCollision detects collisions") {
    Physics sut;
    int cellsWide = 2;
    int cellsTall = 2;
    int tilesPerCellX = 3;
    int tilesPerCellY = 3;
    int tileCount = TiledGridFactory::tileCountForMazeOfSize(cellsWide, cellsTall, tilesPerCellX, tilesPerCellY);
    int tilesWide = TiledGridFactory::tileCountForCellDimension(cellsWide, tilesPerCellX);
    int tilesTall = TiledGridFactory::tileCountForCellDimension(cellsTall, tilesPerCellY);
    int tileData[tileCount];
    TiledGridFactory tiledGridFactory;
    tiledGridFactory.generate(cellsWide, cellsTall, tileData, tilesPerCellX, tilesPerCellY);
    Maze maze(tileData, tilesWide, tilesTall);

    Point playerPos(1, 1);
    Point movement(1, 0);
    CHECK(sut.isCollision(&playerPos, &movement, &maze) == true);
    CHECK(playerPos.X == 1);
    CHECK(playerPos.Y == 1);
    CHECK(movement.X == 1);
    CHECK(movement.Y == 0);
    movement.X = 0;
    movement.Y = 1;
    CHECK(sut.isCollision(&playerPos, &movement, &maze) == true);
    movement.X = 1;
    movement.Y = 1;
    CHECK(sut.isCollision(&playerPos, &movement, &maze) == true);
    movement.X = 3;
    movement.Y = 3;
    CHECK(sut.isCollision(&playerPos, &movement, &maze) == true);
    movement.X = -1;
    movement.Y = -1;
    CHECK(sut.isCollision(&playerPos, &movement, &maze) == true);
  }
  TEST_CASE("isCollision detects misses") {
    Physics sut;
    int cellsWide = 2;
    int cellsTall = 2;
    int tilesPerCellX = 6;
    int tilesPerCellY = 6;
    int tileCount = TiledGridFactory::tileCountForMazeOfSize(cellsWide, cellsTall, tilesPerCellX, tilesPerCellY);
    int tilesWide = TiledGridFactory::tileCountForCellDimension(cellsWide, tilesPerCellX);
    int tilesTall = TiledGridFactory::tileCountForCellDimension(cellsTall, tilesPerCellY);
    int tileData[tileCount];
    TiledGridFactory tiledGridFactory;
    tiledGridFactory.generate(cellsWide, cellsTall, tileData, tilesPerCellX, tilesPerCellY);
    Maze maze(tileData, tilesWide, tilesTall);

    Point playerPos(1, 1);
    Point movement(1, 0);
    CHECK(sut.isCollision(&playerPos, &movement, &maze) == false);
    CHECK(playerPos.X == 1);
    CHECK(playerPos.Y == 1);
    CHECK(movement.X == 1);
    CHECK(movement.Y == 0);
    movement.X = 0;
    movement.Y = 1;
    CHECK(sut.isCollision(&playerPos, &movement, &maze) == false);
    movement.X = 1;
    movement.Y = 1;
    CHECK(sut.isCollision(&playerPos, &movement, &maze) == false);
    movement.X = 3;
    movement.Y = 3;
    CHECK(sut.isCollision(&playerPos, &movement, &maze) == false);
    playerPos.X = 3;
    playerPos.Y = 3;
    movement.X = -1;
    movement.Y = -1;
    CHECK(sut.isCollision(&playerPos, &movement, &maze) == false);
  }
}
