#include "../doctest.h"
#include "../../src/maze_generation/tiled_maze_factory.h"
#include "../../src/tile.h"

TEST_SUITE("TiledMazeFactory") {
  TEST_CASE("tileCountForMazeOfSize returns correct count") {
    TiledMazeFactory sut;

    CHECK(sut.tileCountForMazeOfSize(1, 1, 3, 3) == 9);
    CHECK(sut.tileCountForMazeOfSize(1, 1, 3, 6) == 18);
    CHECK(sut.tileCountForMazeOfSize(1, 2, 3, 3) == 15);
    CHECK(sut.tileCountForMazeOfSize(2, 2, 7, 3) == 65);
    CHECK(sut.tileCountForMazeOfSize(2, 3, 3, 3) == 35);
    CHECK(sut.tileCountForMazeOfSize(3, 3, 3, 3) == 49);
  }
  TEST_CASE("isCornerTile returns true for corner tiles") {
    TiledMazeFactory sut;

    CHECK(sut.isCornerTile(0, 0, 3, 3) == true);
    CHECK(sut.isCornerTile(0, 5, 3, 6) == true);
    CHECK(sut.isCornerTile(2, 2, 3, 3) == true);
    CHECK(sut.isCornerTile(6, 0, 7, 3) == true);
    CHECK(sut.isCornerTile(4, 2, 3, 3) == true);
    CHECK(sut.isCornerTile(2, 6, 3, 3) == true);
  }
  TEST_CASE("isCornerTile returns false for not corner tiles") {
    TiledMazeFactory sut;

    CHECK(sut.isCornerTile(0, 1, 3, 3) == false);
    CHECK(sut.isCornerTile(2, 6, 3, 6) == false);
    CHECK(sut.isCornerTile(7, 2, 3, 3) == false);
    CHECK(sut.isCornerTile(6, 1, 7, 3) == false);
    CHECK(sut.isCornerTile(4, 53, 3, 3) == false);
    CHECK(sut.isCornerTile(22, 17, 3, 3) == false);
  }
  TEST_CASE("isEdgeTile returns true for edge tiles") {
    TiledMazeFactory sut;

    CHECK(sut.isEdgeTile(0, 3) == true);
    CHECK(sut.isEdgeTile(5, 6) == true);
    CHECK(sut.isEdgeTile(2, 3) == true);
    CHECK(sut.isEdgeTile(0, 3) == true);
    CHECK(sut.isEdgeTile(2, 3) == true);
    CHECK(sut.isEdgeTile(6, 3) == true);
  }
  TEST_CASE("isEdgeTile returns false for not edge tiles") {
    TiledMazeFactory sut;

    CHECK(sut.isEdgeTile(1, 3) == false);
    CHECK(sut.isEdgeTile(3, 3) == false);
    CHECK(sut.isEdgeTile(7, 3) == false);
    CHECK(sut.isEdgeTile(14, 7) == false);
    CHECK(sut.isEdgeTile(42, 30) == false);
    CHECK(sut.isEdgeTile(22, 4) == false);
  }
  TEST_CASE("locateTile returns correct location") {
    TiledMazeFactory sut;
    int tilesWide = 7;
    int tilesPerCellX = 3;
    int tilesPerCellY = 3;

    CHECK(sut.locateTile(0, 0, 0, 0, tilesWide, tilesPerCellX, tilesPerCellY) == 0);
    CHECK(sut.locateTile(1, 0, 0, 0, tilesWide, tilesPerCellX, tilesPerCellY) == 1);
    CHECK(sut.locateTile(2, 0, 0, 0, tilesWide, tilesPerCellX, tilesPerCellY) == 2);
    CHECK(sut.locateTile(0, 1, 0, 0, tilesWide, tilesPerCellX, tilesPerCellY) == 7);
    CHECK(sut.locateTile(0, 2, 0, 0, tilesWide, tilesPerCellX, tilesPerCellY) == 14);
    CHECK(sut.locateTile(0, 0, 0, 1, tilesWide, tilesPerCellX, tilesPerCellY) == 14);
    CHECK(sut.locateTile(0, 0, 1, 0, tilesWide, tilesPerCellX, tilesPerCellY) == 2);
    CHECK(sut.locateTile(1, 0, 1, 0, tilesWide, tilesPerCellX, tilesPerCellY) == 3);
    CHECK(sut.locateTile(2, 0, 1, 0, tilesWide, tilesPerCellX, tilesPerCellY) == 4);
    CHECK(sut.locateTile(0, 0, 2, 0, tilesWide, tilesPerCellX, tilesPerCellY) == 4);
    CHECK(sut.locateTile(0, 0, 1, 1, tilesWide, tilesPerCellX, tilesPerCellY) == 16);
    CHECK(sut.locateTile(2, 2, 0, 0, tilesWide, tilesPerCellX, tilesPerCellY) == 16);
  }
  TEST_CASE("spawnFreeTiles sets all tiles to FREE") {
    TiledMazeFactory sut;
    int cellsWide = 5;
    int cellsTall = 5;
    int tilesPerCellX = 6;
    int tilesPerCellY = 6;
    int tileCount = sut.tileCountForMazeOfSize(cellsWide, cellsTall, tilesPerCellX, tilesPerCellY);
    int tileData[tileCount];

    sut.spawnFreeTiles(cellsWide, cellsTall, tileData, tilesPerCellX, tilesPerCellY);

    for (int i = 0; i < tileCount; i++) {
      CHECK(tileData[i] == (int)Tile::FREE);
    }
  }
  TEST_CASE("spawnWalls sets all edge tiles to walls") {
    TiledMazeFactory sut;
    int cellsWide = 5;
    int cellsTall = 5;
    int tilesPerCellX = 6;
    int tilesPerCellY = 6;
    int tileCount = sut.tileCountForMazeOfSize(cellsWide, cellsTall, tilesPerCellX, tilesPerCellY);
    int tilesWide = sut.tileCountForCellDimension(cellsWide, tilesPerCellX);
    int tileData[tileCount];

    sut.spawnWalls(cellsWide, cellsTall, tileData, tilesPerCellX, tilesPerCellY);

    for (int y = 0; y < cellsTall; y++) {
      for (int x = 0; x < cellsWide; x++) {
        for (int ty = 0; ty < tilesPerCellY; ty++) {
          for (int tx = 0; tx < tilesPerCellX; tx++) {
            if (sut.isEdgeTile(tx, tilesPerCellX)) {
              CHECK(tileData[sut.locateTile(tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY)] == Tile::VERTICAL_WALL);
            }
            else if (sut.isEdgeTile(ty, tilesPerCellY)) {
              CHECK(tileData[sut.locateTile(tx, ty, x, y, tilesWide, tilesPerCellX, tilesPerCellY)] == Tile::HORIZONTAL_WALL);
            }
          }
        }
      }
    }
  }
  TEST_CASE("spawnOuterCorners sets all outer corners") {
    TiledMazeFactory sut;
    int cellsWide = 5;
    int cellsTall = 5;
    int tilesPerCellX = 6;
    int tilesPerCellY = 6;
    int tileCount = sut.tileCountForMazeOfSize(cellsWide, cellsTall, tilesPerCellX, tilesPerCellY);
    int tilesWide = sut.tileCountForCellDimension(cellsWide, tilesPerCellX);
    int tileData[tileCount];

    sut.spawnOuterCorners(cellsWide, cellsTall, tileData, tilesPerCellX, tilesPerCellY);

    CHECK(tileData[sut.locateTile(0, 0, 0, 0, tilesWide, tilesPerCellX, tilesPerCellY)] == Tile::TOP_LEFT_CORNER);
    CHECK(tileData[sut.locateTile(tilesPerCellX-1, 0, cellsWide-1, 0, tilesWide, tilesPerCellX, tilesPerCellY)] == Tile::TOP_RIGHT_CORNER);
    CHECK(tileData[sut.locateTile(0, tilesPerCellY-1, 0, cellsTall-1, tilesWide, tilesPerCellX, tilesPerCellY)] == Tile::BOTTOM_LEFT_CORNER);
    CHECK(tileData[sut.locateTile(tilesPerCellX-1, tilesPerCellY-1, cellsWide-1, cellsTall-1, tilesWide, tilesPerCellX, tilesPerCellY)] == Tile::BOTTOM_RIGHT_CORNER);
  }
}
