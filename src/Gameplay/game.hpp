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

  Game(size_t numPlayers, size_t maxGreenCards, size_t maxBlackCards, size_t maxHand);

  void initGameBoard( PlayerListPtr players , 
                      size_t numPlayers , 
                      size_t maxGreenCards , 
                      size_t maxBlackCards , 
                      size_t maxHand);
  
  void printGameStatistics() const;
  void gameplay();
};
/* ========================================================================= */

#endif