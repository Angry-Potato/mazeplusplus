#include "doctest.h"
#include "../src/point.h"
#include "../src/movement.h"

TEST_SUITE("Movement") {
  Movement sut;
  TEST_CASE("move increments the given point by the given amount") {
    int pointX = 21;
    int pointY = 13;
    Point point(pointX, pointY);
    Point amount(3, 5);

    sut.move(&point, &amount);

    CHECK(point.X == pointX + amount.X);
    CHECK(point.Y == pointY + amount.Y);
  }
}
