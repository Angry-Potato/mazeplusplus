#include "player_view.h"
#include "libtcod.hpp"

int PlayerView::characterCode(int playerId) {
  switch (playerId) {
    case 1: return 1;
    case 2: return 2;
    default: return 0;
  }
}

TCODColor PlayerView::colour(int playerId) {
  switch (playerId) {
    case 1: return TCODColor::lightBlue;
    case 2: return TCODColor::lightGreen;
    default: return TCODColor::white;
  }
}
