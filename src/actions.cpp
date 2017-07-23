#include <map>
#include "actions.h"
#include "player.h"
#include "movement.h"
#include "point.h"
using namespace std;

struct ActionMap{
    static map<int, Point> create_map()
        {
          map<int, Point> m;
          m[NONE] = Point(0, 0);
          m[MOVE_UP] = Point(0, -1);
          m[MOVE_DOWN] = Point(0, 1);
          m[MOVE_LEFT] = Point(-1, 0);
          m[MOVE_RIGHT] = Point(1, 0);
          return m;
        }
    static map<int, Point> actions;
};

map<int, Point> ActionMap::actions = ActionMap::create_map();

void Actions::perform(Action action, Player* player) const {
  Movement mover;
  Point movement = ActionMap::actions[(int)action];
  mover.move(&(player->position), &movement);
}
