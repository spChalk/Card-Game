#ifndef GAME_0
#define GAME_0

#include "basicHeader.hpp"

/* ========================================================================= */

class Game
{
  PlayerListPtr players;
 
  size_t checkWinningCondition();

  void startingPhase (PlayerPtr);
  void equipmentPhase(PlayerPtr);
  void battlePhase   (PlayerPtr);
  void economyPhase  (PlayerPtr);
  void finalPhase    (PlayerPtr);

public:

  Game(size_t numPlayers );

  void initGameBoard( PlayerListPtr players , 
                      size_t numPlayers );
  
  void printGameStatistics() const;
  void gameplay();
};
/* ========================================================================= */

#endif