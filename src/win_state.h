#ifndef WIN_STATE_H
#define WIN_STATE_H

class WinState {
public :
  static inline bool hasWon(Player* player, Maze* maze) {
    return *(player->position) == maze->finishTile();
  }
};
#endif
