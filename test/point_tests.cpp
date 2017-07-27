#include "doctest.h"
#include "../src/point.h"

TEST_SUITE("Point") {
  TEST_CASE("defaults to 0,0") {
    Point sut;

    CHECK(sut.X == 0);
    CHECK(sut.Y == 0);
  }
  TEST_CASE("addition of points behaves as expected") {
    Point p1(2, 2);
    Point p2(1, 4);
    Point p3 = p1 + p2;

    CHECK(p1.X == 2);
    CHECK(p1.Y == 2);
    CHECK(p2.X == 1);
    CHECK(p2.Y == 4);
    CHECK(p3.X == 3);
    CHECK(p3.Y == 6);
  }
  TEST_CASE("subtraction of points behaves as expected") {
    Point p1(5, 2);
    Point p2(7, 1);
    Point p3 = p1 - p2;

    CHECK(p1.X == 5);
    CHECK(p1.Y == 2);
    CHECK(p2.X == 7);
    CHECK(p2.Y == 1);
    CHECK(p3.X == -2);
    CHECK(p3.Y == 1);
  }
}
