#include "doctest.h"
#include "../src/player.h"
#include "../src/actions.h"

TEST_SUITE("Actions") {
  TEST_CASE("MOVE_UP moves the player up") {
    Actions sut;
    Actions::Action move_up = Actions::MOVE_UP;
    int initialX = 0;
    int initialY = 0;
    Player player(initialX, initialY);

    sut.perform(move_up, &player);

    CHECK(player.position->X == initialX);
    CHECK(player.position->Y < initialY);
  }
  TEST_CASE("MOVE_DOWN moves the player down") {
    Actions sut;
    Actions::Action move_down = Actions::MOVE_DOWN;
    int initialX = 0;
    int initialY = 0;
    Player player(initialX, initialY);

    sut.perform(move_down, &player);

    CHECK(player.position->X == initialX);
    CHECK(player.position->Y > initialY);
  }
  TEST_CASE("MOVE_LEFT moves the player left") {
    Actions sut;
    Actions::Action move_left = Actions::MOVE_LEFT;
    int initialX = 0;
    int initialY = 0;
    Player player(initialX, initialY);

    sut.perform(move_left, &player);

    CHECK(player.position->X < initialX);
    CHECK(player.position->Y == initialY);
  }
  TEST_CASE("MOVE_RIGHT moves the player right") {
    Actions sut;
    Actions::Action move_right = Actions::MOVE_RIGHT;
    int initialX = 0;
    int initialY = 0;
    Player player(initialX, initialY);

    sut.perform(move_right, &player);

    CHECK(player.position->X > initialX);
    CHECK(player.position->Y == initialY);
  }
}
