/* gamePublic.cpp */
// [Χάρης] Note: σου προτείνω να γράψεις εδώ τα public functions
// της κλάσης Game και ξεχωριστά τα phases σου αλλά ό,τι 
// θες γενικά
#include <cstddef> //size_t
#include <iostream>

#include "baseClasses.h"

#define NO_WINNER 0

/* ========================================================================= */

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
  std::cout << "Player \'" << winner->getUserName() 
            << "\' just won the game!" << std::endl;
}

/* ========================================================================= */

/* Checks whether we have a winner                  *
 * Returns his place in the vector counting from 1  *
 * If no winner is found, returns 0                 */
size_t Game::checkWinningCondition(void)
{
  bool playersWithProvinces = 0;
  size_t pos;
  size_t ctr = 1;

  for (auto i : *players) // if it doesn't work, it's this cr p
  {                       // cuz idk what i'm doing, auto is lazy af
    auto provinces = i->getProvinces();
    if (provinces->size() != 0)     /* If the player still has prov */
    { 
      if (playersWithProvinces == 1)  
        return NO_WINNER;    /* We already found another player with prov */
      else
      {
        playersWithProvinces = 1;
        pos = ctr;     /* Keep his position in the vector */
      }
    }
    ++ctr;
  }
  return pos;
}

/* ========================================================================= */