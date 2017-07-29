// #include "doctest.h"
// #include "../src/player.h"
// #include "../src/actions.h"
//
// TEST_SUITE("Actions") {
//   TEST_CASE("MOVE_UP moves the player up") {
//     Actions sut;
//     Actions::Action move_up = Actions::MOVE_UP;
//     int initialX = 0;
//     int initialY = 0;
//     Player* players = new Player[1];
//     players[0].position->X = initialX;
//     players[0].position->Y = initialY;
//     sut.perform(move_up, players, 1);
//
//     CHECK(players[0].position->X == initialX);
//     CHECK(players[0].position->Y < initialY);
//   }
//   TEST_CASE("MOVE_DOWN moves the player down") {
//     Actions sut;
//     Actions::Action move_down = Actions::MOVE_DOWN;
//     int initialX = 0;
//     int initialY = 0;
//     Player* players = new Player[1];
//     players[0].position->X = initialX;
//     players[0].position->Y = initialY;
//     sut.perform(move_down, players, 1);
//
//     CHECK(players[0].position->X == initialX);
//     CHECK(players[0].position->Y > initialY);
//   }
//   TEST_CASE("MOVE_LEFT moves the player left") {
//     Actions sut;
//     Actions::Action move_left = Actions::MOVE_LEFT;
//     int initialX = 0;
//     int initialY = 0;
//     Player* players = new Player[1];
//     players[0].position->X = initialX;
//     players[0].position->Y = initialY;
//     sut.perform(move_left, players, 1);
//
//     CHECK(players[0].position->X < initialX);
//     CHECK(players[0].position->Y == initialY);
//   }
//   TEST_CASE("MOVE_RIGHT moves the player right") {
//     Actions sut;
//     Actions::Action move_right = Actions::MOVE_RIGHT;
//     int initialX = 0;
//     int initialY = 0;
//     Player* players = new Player[1];
//     players[0].position->X = initialX;
//     players[0].position->Y = initialY;
//     sut.perform(move_right, players, 1);
//
//     CHECK(players[0].position->X > initialX);
//     CHECK(players[0].position->Y == initialY);
//   }
// }
