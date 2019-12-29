/* battlePhase.cpp */

#include <iostream>
#include <string>

#include "baseClasses.h"

using std::cout;
using std::endl;

#define WRONG_INPUT   0
#define CORRECT_INPUT 1

/* ========================================================================= */

static Player * chooseEnemy(std::vector<Player *> * players)
{
  Player *enemy;
  for (int status = WRONG_INPUT; status != CORRECT_INPUT; )
  {
    for (auto *i : *players)
    {
      if (i->getProvincesNum() != 0)    //if player still in the game
        cout << i->getUserName() << endl;
    }
    cout << "> Your pick: ";

    std::string enemyName;
    std::getline(std::cin, enemyName);
    cout << enemyName << endl;

    for (auto *i : *players)  // kinda retarded, should do faster if I please
    {
      if (i->getProvincesNum() == 0) continue;

      if (i->getUserName() == enemyName)
      {
        enemy = i;
        status = CORRECT_INPUT;
        break; 
      }
    }

    if (status == WRONG_INPUT)
      cout << "Wrong enemy chosen. Please, try again. (Your choice: \'" 
           << enemyName << "\' )" << endl; 
  }

  return enemy;
}

/* ========================================================================= */

void Game::battlePhase(Player *player)
{
  cout << "Battle phase begins!" << endl;
  cout << "Choose an enemy! Available enemies are:" << endl;

  Player *enemy = chooseEnemy(players);

  /* choose province */
  /* choose from army */

  /* GIVE CONTROL TO THE DEFENDER */
  /* choose from army to defend */

  /* Battle */
}