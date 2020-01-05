#ifndef GAME_0
#define GAME_0

#include "baseClasses.h"
//==========================================|| G A M E ||==========================================

class Game
{
  PlayerListPtr players;
 
  size_t checkWinningCondition();

  void startingPhase (PlayerPtr );
  void equipmentPhase(PlayerPtr );
  void battlePhase   (PlayerPtr );
  void economyPhase  (PlayerPtr );
  void finalPhase    (PlayerPtr );

public:

  Game(size_t numPlayers, size_t maxGreenCards, size_t maxBlackCards, size_t maxHand /*might need more, you're up*/);

  void initGameBoard(PlayerListPtr players , size_t numPlayers , size_t maxGreenCards , size_t maxBlackCards , size_t maxHand);
  void printGameStatistics() const;
  void gameplay();
};

#endif