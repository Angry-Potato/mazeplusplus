#ifndef PLAYER_VIEW_H
#define PLAYER_VIEW_H

class TCODColor;
class PlayerView {
public :
  static int characterCode(int playerId);
  static TCODColor colour(int playerId);
};
#endif
