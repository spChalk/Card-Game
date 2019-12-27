/* gamePublic.cpp */
// [Χάρης] Note: σου προτείνω να γράψεις εδώ τα public functions
// της κλάσης Game και ξεχωριστά τα phases σου αλλά ό,τι 
// θες γενικά
#include <iostream>

#include "baseClasses.h"

#define NO_WINNER 0

/* Plays the game. Terminates only when there's a winner *
 * TODO: Maybe add some violent termination feature ?    */
void Game::gameplay(void)
{
  size_t gameStatus = NO_WINNER;

  while(gameStatus == NO_WINNER)
  {
    for (auto i : *players) // c-like != python...
    {
      startingPhase(i);
      equipmentPhase(i);
      battlePhase(i);

      if (gameStatus = checkWinningCondition())
        break;

      economyPhase(i);
      finalPhase(i);
    }
  }

  Player *winner = players->at(gameStatus-1);
  std::cout << "Player \'" << winner->getName() 
            << "\' just won the game!" << std::endl;
}