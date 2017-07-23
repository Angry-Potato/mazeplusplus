#include "player_view.h"

int PlayerView::forId(int id) {
  switch (id) {
    case 1: return 1;
    case 2: return 2;
    default: return 0;
  }
}
