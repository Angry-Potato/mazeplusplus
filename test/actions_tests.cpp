#include "doctest.h"
#include "../src/player.h"
#include "../src/actions.h"

TEST_SUITE("Actions") {
  TEST_CASE("MOVE_UP moves the player up") {
    Actions sut;
    Action move_up = MOVE_UP;
    int initialX = 0;
    int initialY = 0;
    Player player(initialX, initialY);

    sut.perform(move_up, &player);

    CHECK(player.position->X == initialX);
    CHECK(player.position->Y < initialY);
  }
  TEST_CASE("MOVE_DOWN moves the player down") {
    Actions sut;
    Action move_down = MOVE_DOWN;
    int initialX = 0;
    int initialY = 0;
    Player player(initialX, initialY);

    sut.perform(move_down, &player);

    CHECK(player.position->X == initialX);
    CHECK(player.position->Y > initialY);
  }
  TEST_CASE("MOVE_LEFT moves the player left") {
    Actions sut;
    Action move_left = MOVE_LEFT;
    int initialX = 0;
    int initialY = 0;
    Player player(initialX, initialY);

    sut.perform(move_left, &player);

    CHECK(player.position->X < initialX);
    CHECK(player.position->Y == initialY);
  }
  TEST_CASE("MOVE_RIGHT moves the player right") {
    Actions sut;
    Action move_right = MOVE_RIGHT;
    int initialX = 0;
    int initialY = 0;
    Player player(initialX, initialY);

    sut.perform(move_right, &player);

    CHECK(player.position->X > initialX);
    CHECK(player.position->Y == initialY);
  }
}