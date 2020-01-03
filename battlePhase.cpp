/* battlePhase.cpp */

#include <iostream>
#include <string>
#include <vector>

#include "baseClasses.h"

using std::cout;
using std::endl;

namespace // namespace_start
{

#define WRONG_INPUT   0
#define CORRECT_INPUT 1

#define ATTACK 0
#define DEFEND 1

size_t ptsDiff;
  
std::shared_ptr< Player > player;
std::shared_ptr< Player > enemy;
  
std::shared_ptr< vector <std::shared_ptr< Personality > > > attArmy;
std::shared_ptr< vector <std::shared_ptr< Personality > > > defArmy;

const std::string *attName;
const std::string *defName;

std::shared_ptr< Player > chooseEnemy(std::shared_ptr< Player >, std::shared_ptr< vector < std::shared_ptr <Player > > > players);
std::shared_ptr< Province > chooseProvince(std::shared_ptr< Player > player);

int chooseAction(void);

size_t calcTotalATK(std::shared_ptr< vector <std::shared_ptr< Personality > > > battleArmy);
size_t calcTotalDEF(std::shared_ptr< vector <std::shared_ptr< Personality > > > battleArmy);

void chooseArmy(std::shared_ptr< Player > player, std::shared_ptr< vector <std::shared_ptr< Personality > > > battleArmy);
void provinceDestroyed(std::shared_ptr< Province > prov);
void draw();
void verifyCasualties(std::shared_ptr< vector <std::shared_ptr< Personality > > > battleArmy, int side);
void attackerWins();
void defenderWins();
void battle(std::shared_ptr< Province >);

/* ========================================================================= */

std::shared_ptr< Player > chooseEnemy(std::shared_ptr< Player > current, std::shared_ptr< vector < std::shared_ptr <Player > > > players)
{
  cout << "Choose an enemy! Available enemies are:" << endl;

  std::shared_ptr< Player > enemy;
  for (int status = WRONG_INPUT; status != CORRECT_INPUT; )
  {
    for (std::shared_ptr< Player > i : *players)
    {
      if (i == current) continue;
      
      if (i->getProvincesNum() != 0)    //if player still in the game
        cout << i->getUserName() << endl;
    }
    cout << "> Your pick: ";

    std::string enemyName;
    std::getline(std::cin, enemyName);
    cout << enemyName << endl;

    for (std::shared_ptr< Player > i: *players)  // kinda retarded, should do faster if I please
    {
      if (i->getProvincesNum() == 0 || i == current) continue;

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

int chooseAction(void)
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

std::shared_ptr< Province > chooseProvince(std::shared_ptr< Player > player)
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
  for (std::shared_ptr< Province > i : *(player->getProvinces()))
  {
    if (i->checkBroken() == true) continue;
    if (++counter == prov) return i;
  }
  return nullptr; // control is not supposed to reach here, ever :_)
}

/* ========================================================================= */

void chooseArmy(std::shared_ptr< Player > player, std::shared_ptr< vector <std::shared_ptr< Personality > > > battleArmy)
{ // todo: maybe add some better printing if player has no army
  cout << "Choose Personalities from your army to Battle!" << endl;
  
  cout << "Printing player's \"" << player->getUserName() << "\" available army!" << endl;
  player->printAvailableArmy();

  cout << "Now, type 'Y' (YES) or '<any other key>' (NO) after each card's \
appearance, to recruit the Personality for the Battle!" << endl;

  for (std::shared_ptr< Personality > i : *(player->getArmy()))
  {
    if (i->checkTapped() == true) continue;

    i->print();
    cout << "\nRecruit?\n >Your answer: ";
    std::string answer;
    std::getline(std::cin, answer);
    cout << answer << endl;

    if (answer == "Y") battleArmy->push_back(i);
  }
}

/* ========================================================================= */

size_t calcTotalATK(std::shared_ptr< vector <std::shared_ptr< Personality > > > battleArmy)
{
  size_t totalATK = 0;

  for (std::shared_ptr< Personality > i : *battleArmy) // sum ATK of all personalities -> sum ATK of all their flollowers + items
  {
    std::shared_ptr< vector <std::shared_ptr< Follower > > > followers = i->getFollowers();
    std::shared_ptr< vector <std::shared_ptr< Item > > >     items = i->getItems();

    totalATK += i->getATK(); // base personality ATK

    for (std::shared_ptr< Follower > j : *followers) totalATK += j->getATK(); // get followers ATK
    for (std::shared_ptr< Item > j : *items)     totalATK += j->getATK(); // get items ATK
  }

  return totalATK;
}

/* ========================================================================= */

size_t calcTotalDEF(std::shared_ptr< vector <std::shared_ptr< Personality > > > battleArmy)
{
  size_t totalDEF = 0;

  for (std::shared_ptr< Personality > i : *battleArmy) // sum DEF of all personalities -> sum DEF of all their flollowers + items
  {
    std::shared_ptr< vector <std::shared_ptr< Follower > > > followers = i->getFollowers();
    std::shared_ptr< vector <std::shared_ptr< Item > > >     items = i->getItems();

    totalDEF += i->getDEF(); // base personality DEF

    for (std::shared_ptr< Follower > j : *followers) totalDEF += j->getDEF(); // get followers DEF
    for (std::shared_ptr< Item > j : *items)     totalDEF += j->getDEF(); // get items DEF
  }

  return totalDEF;
}

/* ========================================================================= */

void provinceDestroyed(std::shared_ptr< Province > prov)
{
  cout << "Attacker " << *attName << " demolishes " << *defName 
       << " \'s defence!" << endl;

  for (std::shared_ptr< Personality > i : *defArmy) i->die(); // todo: cleanup dead from their vectors
  cout << "Defender's army is destroyed." << endl;

  prov->setBroken();
  enemy->decreaseProvinceNum();
  cout << "Province destroyed. Remaining provinces for player \'" 
       << *defName << "\' : " << enemy->getProvincesNum() << endl;

  if (enemy->getProvincesNum() == 0)
  {
    cout << ">Player \'" << *defName 
         << "\' is out of the game! Better luck next time. =) " << endl;
  }

  for (std::shared_ptr< Personality > i : *attArmy) i->setTapped(); // Tap attackers so they can't be used again for the round
}
/* ========================================================================= */

void draw()
{
  cout << "Battle between \'" << *attName << "\' and \'" 
       << *defName << " ends as a draw! Both armies are destroyed!" << endl;

  for (std::shared_ptr< Personality > i : *attArmy) i->die();
  for (std::shared_ptr< Personality > i : *defArmy) i->die();  
}
/* ========================================================================= */

void verifyCasualties(std::shared_ptr< vector <std::shared_ptr< Personality > > > battleArmy, int side)
{
  for (std::shared_ptr< Personality > i : * battleArmy)
  {
    if (i->getATK() >= ptsDiff) 
      i->die();
    else
    {
      std::shared_ptr< vector <std::shared_ptr< Follower > > > followers = i->getFollowers();
      for (std::shared_ptr< Follower > j : *followers)
        if (j->getATK() >= ptsDiff) // delete followers
          j->detach(); // should do that
    }
  }

  for (std::shared_ptr< Personality > i : * battleArmy) i->setTapped(); // Tap defenders so they can't be used again for the round
    
  for (std::shared_ptr< Personality > i : * battleArmy) // decrease Item durability
  {
    std::shared_ptr< vector <std::shared_ptr< Item > > > items = i->getItems();
    
    for (std::shared_ptr< Item > j : *items) 
    {
      j->decreaseDurability(); // todo: cleanup if 0
      if (j->getDurability() == 0) j->detach(); // should enable that
    }
  }

  if (side == ATTACK)
  {
    for (std::shared_ptr< Personality > i : *battleArmy) //decrease personalities honor
    {   
      i->decreaseHonor();
      if (i->getHonor() == 0) i->kys(); // just kys
    }
  }
}
/* ========================================================================= */

void attackerWins()
{
  cout << "Attacker " << *attName << " destroys " << *defName 
       << " \'s army, but is unable to break the province!" << endl;

  for (std::shared_ptr< Personality > i : *defArmy) i->die(); // todo: cleanup dead from their vectors
  cout << "Defender's army is destroyed." << endl;

  //size_t ptsDiff = attPoints - defPoints;

  cout << "Attacker's army has experienced heavy casualties." << endl; 
  verifyCasualties(attArmy, ATTACK);
}
/* ========================================================================= */

void defenderWins()
{
  cout << "Defender " << *defName << "holds his ground against " << *attName 
       << " \'s army!" << endl;

  for (std::shared_ptr< Personality > i : *attArmy) i->die(); // todo: cleanup dead from their vectors
  cout << "Attacker's army is destroyed." << endl;

  // size_t ptsDiff = attPoints - defPoints;

  cout << "Defender's army has experienced heavy casualties." << endl; 
  verifyCasualties(attArmy, DEFEND);
}
/* ========================================================================= */

void battle(std::shared_ptr< Province > prov)
{
  size_t attPoints = calcTotalATK(attArmy);
  size_t defPoints = calcTotalDEF(defArmy);// + enemy->getStrongHold()->getInitDEF(); // todo: verify @lists

  cout << "Attacker's ARMY strength is: " << attPoints << endl;
  cout << "Defender's ARMY strength is: " << defPoints << endl;

  ptsDiff = attPoints - defPoints;

  if (attPoints > defPoints + enemy->getStrongHold()->getInitDEF()) //ATK wins / DEF gets destroyed
    provinceDestroyed(prov);
  
  else if (attPoints == defPoints)
    draw();

  else if (attPoints > defPoints)
    attackerWins();

  else if (attPoints < defPoints)
    defenderWins();

  player->cleanup();
  enemy ->cleanup();
}

}; // namespace_end
/* ========================================================================= */

void Personality::cleanup()
{
  for (auto it = followers->begin(); it != followers->end(); /* NOTHING */)
  {
    if ((*it)->isAttached() == false)
      it = followers->erase(it);
    else
      ++it;
  }

  for (auto it = items->begin(); it != items->end(); /* NOTHING */)
  {
    if ((*it)->isAttached() == false)
      it = items->erase(it);
    else
      ++it;
  }
}
/* ========================================================================= */

void Player::cleanup()
{
  for (auto it = army->begin(); it != army->end(); /* NOTHING */)
  {
    if ((*it)->checkIfDead() == true)
      it = army->erase(it);
    else
    {
      (*it)->cleanup(); // erase detached greenCards
      ++it;
    }
  }
}
/* ========================================================================= */

void Game::battlePhase(std::shared_ptr< Player > player)
{
  cout << "Battle phase begins!" << endl;

  int action = chooseAction();

  if (action == DEFEND)
  {
    cout << "Player \"" << player->getUserName() 
         << "\" chose to DEFEND this round!" << endl;
    return;
  }
  // action == ATTACK
  ::player = player;
  enemy = chooseEnemy(player, players);

  attName = &player->getUserName();
  defName = &enemy ->getUserName();

  std::shared_ptr< Province > prov = chooseProvince(enemy);

  attArmy = std::make_shared< vector <std::shared_ptr< Personality > > >(); //TODO: delete this
  chooseArmy(player, attArmy);

  cout << "Player \'" << *defName 
       << "\' shall pick their DEFENSE!" << endl;

  defArmy = std::make_shared< vector <std::shared_ptr< Personality > > >(); //TODO: delete this
  chooseArmy(enemy, defArmy);

  /* Battle */
  battle(prov);

  // delete attArmy;
  // delete defArmy;
}
/* ========================================================================= */
