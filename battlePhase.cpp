/* battlePhase.cpp */

#include <iostream>
#include <string>

#include "baseClasses.h"

using std::cout;
using std::endl;

#define WRONG_INPUT   0
#define CORRECT_INPUT 1
#define ATTACK 0
#define DEFEND 1

/* ========================================================================= */

static Player * chooseEnemy(std::vector<Player *> * players)
{
  cout << "Choose an enemy! Available enemies are:" << endl;

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

static int chooseAction(void)
{
  cout << "Do you want to Attack (ATK) or Defend (DEF)?" << endl;
  cout << "> Your answer: " << endl;

  std::string answer;

  while (true)
  {
    std::getline(std::cin, answer);
    cout << answer << endl;

    if (answer == "ATK" || answer == "DEF") break;
  
    cout << "Wrong input given. Available options are \"ATK\" and \"DEF\". \
Input given: " << answer << ". Please, try again.\n>Your answer:";

  }

  return (answer == "ATK" ? ATTACK : DEFEND);
}
/* ========================================================================= */

static Province * chooseProvince(Player *player)
{
  cout << "Choose a province to attack! Available provinces are:" << endl;
  player->printProvinces();

  std::string answer;
  size_t prov;

  while (true)
  {
    cout << "Make your selection based in the order of appearance. \
Your input should be an integer in range [1," << player->getProvincesNum() 
         << "].\n> Choose province number: ";
    
    std::getline(std::cin, answer);
    cout << answer << endl;

    prov = std::stoi(answer);
    if (prov > 0 && prov <= player->getProvincesNum()) break;
  
    cout << "Wrong input given. Please, try again." << endl;
  }
  
  size_t counter = 0;
  for (auto *i : *(player->getProvinces()))
  {
    if (i->checkBroken() == true) continue;
    if (++counter == prov) return i;
  }
  return nullptr; // hopefully, control never reaches here :_)
}

/* ========================================================================= */

static void chooseArmy(Player *player, std::vector<Personality *> * battleArmy)
{ // todo: maybe add some better printing if player has no army
  cout << "Choose Personalities from your army to Battle!" << endl;
  
  cout << "Printing player's \"" << player->getUserName() << "\" available army!" << endl;
  player->printAvailableArmy();

  cout << "Now, type 'Y' (YES) or '<any other key>' (NO) after each card's \
appearance, to recruit the Personality for the Battle!" << endl;

  for (auto *i : *(player->getArmy()))
  {
    i->print();
    cout << "\nRecruit?\n >Your answer: ";
    std::string answer;
    std::getline(std::cin, answer);
    cout << answer << endl;

    if (answer == "Y") battleArmy->push_back(i);
  }
}

/* ========================================================================= */

void Game::battlePhase(Player *player)
{
  cout << "Battle phase begins!" << endl;

  int action = chooseAction();

  if (action == DEFEND)
  {
    cout << "Player \"" << player->getUserName() << "\" chose to DEFEND \
this round!" << endl;
    return;
  }

  // action == ATTACK
  Player *enemy = chooseEnemy(players);

  Province *prov = chooseProvince(enemy);

  std::vector<Personality *> * attArmy = new (std::vector<Personality *>); //TODO: delete this
  chooseArmy(player, attArmy);

  cout << "Player \"" << enemy->getUserName() 
       << "\" shall pick their DEFENSE!" << endl;

  std::vector<Personality *> * defArmy = new (std::vector<Personality *>); //TODO: delete this
  chooseArmy(enemy, defArmy);

  /* Battle */
}