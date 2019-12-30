/* battlePhase.cpp */

#include <iostream>
#include <string>
#include <vector>

#include "baseClasses.h"

using std::cout;
using std::endl;

#define WRONG_INPUT   0
#define CORRECT_INPUT 1

#define ATTACK 0
#define DEFEND 1

size_t ptsDiff;

static void battle(Player *player, std::vector<Personality *> * attArmy, Player *enemy, Province *prov, std::vector<Personality *> * defArmy);
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
  return nullptr; // control is not supposed to reach here, ever :_)
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

static size_t calcTotalATK(std::vector<Personality *> * battleArmy)
{
  size_t totalATK = 0;

  for (auto *i : *battleArmy) // sum ATK of all personalities -> sum ATK of all their flollowers + items
  {
    std::vector <Follower *> * followers = i->getFollowers();
    std::vector <Item *>     * items = i->getItems();

    totalATK += i->getATK(); // base personality ATK

    for (auto *j : *followers) totalATK += j->getATK(); // get followers ATK
    for (auto *j : *items)     totalATK += j->getATK(); // get items ATK
  }

  return totalATK;
}

/* ========================================================================= */

static size_t calcTotalDEF(std::vector<Personality *> * battleArmy)
{
  size_t totalDEF = 0;

  for (auto *i : *battleArmy) // sum DEF of all personalities -> sum DEF of all their flollowers + items
  {
    std::vector <Follower *> * followers = i->getFollowers();
    std::vector <Item *>     * items = i->getItems();

    totalDEF += i->getDEF(); // base personality DEF

    for (auto *j : *followers) totalDEF += j->getDEF(); // get followers DEF
    for (auto *j : *items)     totalDEF += j->getDEF(); // get items DEF
  }

  return totalDEF;
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

  // std::string attName = player->getUserName();
  // std::string defName = enemy ->getUserName();

  Province *prov = chooseProvince(enemy);

  std::vector<Personality *> * attArmy = new (std::vector<Personality *>); //TODO: delete this
  chooseArmy(player, attArmy);

  cout << "Player \'" << enemy->getUserName() 
       << "\' shall pick their DEFENSE!" << endl;

  std::vector<Personality *> * defArmy = new (std::vector<Personality *>); //TODO: delete this
  chooseArmy(enemy, defArmy);

  /* Battle */
  battle(player, attArmy, enemy, prov, defArmy);
}

/* ========================================================================= */

static void provinceDestroyed(Player *player, std::vector<Personality *> * attArmy, Player *enemy, Province *prov, std::vector<Personality *> * defArmy)
{
  const std::string& attName = player->getUserName();
  const std::string& defName = enemy ->getUserName();

  cout << "Attacker " << attName << " demolishes " << defName 
       << " \'s defence!" << endl;

  for (auto *i : *defArmy) i->die(); // todo: cleanup dead from their vectors
  cout << "Defender's army is destroyed." << endl;

  prov->setBroken();
  enemy->decreaseProvinceNum();
  cout << "Province destroyed. Remaining provinces for player \'" 
       << defName << "\' : " << enemy->getProvincesNum() << endl;

  if (enemy->getProvincesNum() == 0)
  {
    cout << ">Player \'" << defName 
         << "\' is out of the game! Better luck next time. =) " << endl;
  }

  for (auto *i : *attArmy) i->setTapped(); // Tap attackers so they can't be used again for the round
}
/* ========================================================================= */

static void draw(Player *player, std::vector<Personality *> * attArmy, Player *enemy, std::vector<Personality *> * defArmy)
{
  cout << "Battle between \'" << player->getUserName() << "\' and \'" 
       << enemy->getUserName() << " ends as a draw! Both armies are destroyed!" 
       << endl;

  for (auto *i : *attArmy) i->die();
  for (auto *i : *defArmy) i->die();  
}
/* ========================================================================= */

static void verifyCasualties(std::vector<Personality *> * battleArmy, int side)
{
  for (auto *i : * battleArmy)
  {
    if (i->getATK() >= ptsDiff) 
      i->die();
    else
    {
      std::vector <Follower *> *followers = i->getFollowers();
      for (auto *j : *followers)
        if (j->getATK() >= ptsDiff) // delete followers
          j->detach(); // should do that
    }
  }

  for (auto *i : * battleArmy) i->setTapped(); // Tap defenders so they can't be used again for the round
    
  for (auto *i : * battleArmy) // decrease Item durability
  {
    std::vector <Item *> *items = i->getItems();
    
    for (auto *j : *items) 
    {
      j->decreaseDurability(); // todo: cleanup if 0
      if (j->getDurability() == 0) j->detach(); // should enable that
    }
  }

  if (side == ATTACK)
  {
    for (auto *i : *battleArmy) //decrease personalities honor
    {   
      i->decreaseHonor();
      if (i->getHonor() == 0) i->kys(); // just kys
    }
  }
}
/* ========================================================================= */

static void attackerWins(Player *player, std::vector<Personality *> * attArmy, Player *enemy, std::vector<Personality *> * defArmy)
{
  const std::string& attName = player->getUserName();
  const std::string& defName = enemy ->getUserName();

  cout << "Attacker " << attName << " destroys " << defName 
       << " \'s army, but is unable to break the province!" << endl;

  for (auto *i : *defArmy) i->die(); // todo: cleanup dead from their vectors
  cout << "Defender's army is destroyed." << endl;

  //size_t ptsDiff = attPoints - defPoints;

  cout << "Attacker's army has experienced heavy casualties." << endl; 
  verifyCasualties(attArmy, ATTACK);
}
/* ========================================================================= */

static void defenderWins(Player *player, std::vector<Personality *> * attArmy, Player *enemy, std::vector<Personality *> * defArmy)
{
  const std::string& attName = player->getUserName();
  const std::string& defName = enemy ->getUserName();

  cout << "Defender " << defName << "holds his ground against " << attName 
       << " \'s army!" << endl;

  for (auto *i : *attArmy) i->die(); // todo: cleanup dead from their vectors
  cout << "Attacker's army is destroyed." << endl;

  // size_t ptsDiff = attPoints - defPoints;

  cout << "Defender's army has experienced heavy casualties." << endl; 
  verifyCasualties(attArmy, DEFEND);
}
/* ========================================================================= */

static void battle(Player *player, std::vector<Personality *> * attArmy, Player *enemy, Province *prov, std::vector<Personality *> * defArmy)
{
  size_t attPoints = calcTotalATK(attArmy);
  size_t defPoints = calcTotalDEF(defArmy);// + enemy->getStrongHold()->getInitDEF(); // todo: verify @lists

  cout << "Attacker's ARMY strength is: " << attPoints << endl;
  cout << "Defender's ARMY strength is: " << defPoints << endl;

  ptsDiff = attPoints - defPoints;

  if (attPoints > defPoints + enemy->getStrongHold()->getInitDEF()) //ATK wins / DEF gets destroyed
    provinceDestroyed(player, attArmy, enemy, prov, defArmy);
  
  else if (attPoints == defPoints) // draw
    draw(player, attArmy, enemy, defArmy);

  else if (attPoints > defPoints)
    attackerWins(player, attArmy, enemy, defArmy);

  else if (attPoints < defPoints)
    defenderWins(player, attArmy, enemy, defArmy);

  player->cleanup();
  enemy ->cleanup();
}

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