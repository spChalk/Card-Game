/* battlePhase.cpp */

#include <iostream>
#include <list>
#include <string>

#include "basicHeader.hpp"

using std::cout;
using std::endl;

namespace // namespace_start
{

#define WRONG_INPUT   0
#define CORRECT_INPUT 1

#define ATTACK 0
#define DEFEND 1

int32_t ptsDiff;
  
PlayerPtr player;
PlayerPtr enemy;
  
ArmyPtr attArmy;
ArmyPtr defArmy;

const std::string *attName;
const std::string *defName;

PlayerPtr   chooseEnemy(PlayerPtr, PlayerListPtr players);
ProvincePtr chooseProvince(PlayerPtr player);

int chooseAction(void);

int32_t calcTotalATK(ArmyPtr battleArmy);
int32_t calcTotalDEF(ArmyPtr battleArmy);

void chooseArmy(PlayerPtr player, ArmyPtr battleArmy);
void provinceDestroyed(ProvincePtr prov);
void draw();
void verifyCasualties(ArmyPtr battleArmy, int side);
void attackerWins();
void defenderWins();
void battle(ProvincePtr);
void provincesCleanup(PlayerPtr);

/* ========================================================================= */

PlayerPtr chooseEnemy(PlayerPtr current, PlayerListPtr players)
{
  printF("Choose an enemy! Available enemies are:" , 1 , RED , BOLD);

  PlayerPtr enemy;
  for (int status = WRONG_INPUT; status != CORRECT_INPUT; )
  {
    for (auto i : *players)
    {
      if (i == current) continue;
      
      if (i->getProvincesNum() != 0)    //if player still in the game
        cout << i->getUserName() << endl;
    }
    printF("> Your pick: " , 0 , RED , BOLD);

    std::string enemyName;
    std::getline(std::cin, enemyName);
    cout << enemyName << endl;

    for (auto i: *players)  // kinda retarded, should do faster if I please
    {
      if (i->getProvincesNum() == 0 || i == current) continue;

      if (i->getUserName() == enemyName)
      {
        enemy = i;
        status = CORRECT_INPUT;
        break; 
      }
    }

    if (status == WRONG_INPUT) {
      printF("Wrong enemy chosen. Please, try again. (Your choice: \'" , 0 , MAG , BOLD); 
      cout << enemyName << "\' )" << endl;
    } 
  }

  return enemy;
}

/* ========================================================================= */

int chooseAction(void)
{
  cout << player->getUserName();
  printF(" , do you want to Attack (ATK) or Defend (DEF)?" , 1 , RED , BOLD);
  printF("> Your answer: " , 1 , BLU , BOLD);

  std::string answer;

  while (true)
  {
    std::getline(std::cin, answer);
    cout << answer << endl;

    if (answer == "ATK" || answer == "DEF" || answer == "atk" || answer == "def")
      break;
  
    printF ("Wrong input given. Available options are \"ATK\" and \"DEF\".\n  Input given: " , 0 , MAG , BOLD);
    cout << answer;
    printF (". Please, try again.\n> Your answer:" , 0 , BLU , BOLD);
  }

  return ((answer == "ATK" || answer == "atk") ? ATTACK : DEFEND);
}

/* ========================================================================= */

ProvincePtr chooseProvince(PlayerPtr player)
{
  printF ("Choose a province to attack! Available provinces are:" , 1 , RED , BOLD);
  player->printProvinces();

  std::string answer;
  int32_t prov;

  while (true)
  {
    printF ("Make your selection based in the order of appearance. \n \
    Your input should be an integer in range " , 0 , MAG , BOLD);
    cout << "[1," << player->getProvincesNum() << "]."; 
    printF ("\n> Choose province number: " , 0 , MAG , BOLD );
    
    std::getline(std::cin, answer);
    cout << answer << endl;

    prov = std::stoi(answer);

    for (auto c : answer)     /* Validate the input given by the user */
      if (c > '9' || c < '0')
        prov = -1;

    if (prov > 0 && prov <= player->getProvincesNum()) 
      break;
  
    printF ("Wrong input given. Please, try again." , 1 , MAG , BOLD);
  }
  
  uint16_t counter = 0;
  for (auto i : *(player->getProvinces()))
  {
    if (i->checkBroken() == true) continue;
    if (++counter == prov) return i;
  }
  return nullptr; // control is not supposed to reach here, ever :_)
}

/* ========================================================================= */

void chooseArmy(PlayerPtr player, ArmyPtr battleArmy)
{ // todo: maybe add some better printing if player has no army
  cout << player->getUserName();
  printF (" , time to choose Personalities from your army to Battle!" , 1 , RED , BOLD);
  
  printF ("Printing player's \"" , 0 , MAG , BOLD);
  cout << player->getUserName();
  printF ("\" available army!" , 1 , MAG , BOLD);
  player->printAvailableArmy();

  cout << player->getUserName();
  printF (" , type 'Y' (YES) or '<any other key>' (NO) after each card's \
appearance, to recruit the Personality for the Battle!" , 1 , MAG , BOLD);
  printF ("Press ENTER to continue . . ." , 1);
  std::cin.clear();
  std::cin.sync();
  std::cin.get();

  for (auto i : *(player->getArmy()))
  {
    if (i->checkTapped() == true) continue;

    i->print();
    printF ("\nRecruit? ", 1 , RED , BOLD);
    printF ("> Your answer: " , 0 , BLU , BOLD);
    std::string answer;
    std::getline(std::cin, answer);
    cout << answer << endl;

    if ((answer == "Y") || (answer == "y")) 
      battleArmy->push_back(i);
  }
}

/* ========================================================================= */

int32_t calcTotalATK(ArmyPtr battleArmy)
{
  int32_t totalATK = 0;

  for (std::shared_ptr< Personality > i : *battleArmy) // sum ATK of all personalities -> sum ATK of all their flollowers + items
  {
    FollowerListPtr followers = i->getFollowers();
    ItemListPtr     items = i->getItems();

    totalATK += i->getATK(); // base personality ATK

    for (auto j : *followers) totalATK += j->getATK(); // get followers ATK
    for (auto j : *items)     totalATK += j->getATK(); // get items ATK
  }

  return totalATK;
}

/* ========================================================================= */

int32_t calcTotalDEF(ArmyPtr battleArmy)
{
  int32_t totalDEF = 0;

  for (auto i : *battleArmy) // sum DEF of all personalities -> sum DEF of all their flollowers + items
  {
    FollowerListPtr followers = i->getFollowers();
    ItemListPtr     items = i->getItems();

    totalDEF += i->getDEF(); // base personality DEF

    for (auto j : *followers) totalDEF += j->getDEF(); // get followers DEF
    for (auto j : *items)     totalDEF += j->getDEF(); // get items DEF
  }

  return totalDEF;
}

/* ========================================================================= */

void provinceDestroyed(ProvincePtr prov)
{
  printF ("Attacker " , 0 , RED , BOLD);
  cout << *attName;
  printF (" demolishes " , 0 , RED , BOLD);
  cout << *defName; 
  printF (" \'s defence!" , 1 , RED , BOLD);

  for (auto i : *defArmy) i->die(); // todo: cleanup dead from their lists
  printF ("Defender's army is destroyed." , 1 , RED , BOLD);

  prov->setBroken();
  enemy->decreaseProvinceNum();
  printF ("Province destroyed. Remaining provinces for player \'" , 0 , RED , BOLD); 
  cout << *defName ;
  printF ("\' : " , 0 , RED , BOLD) ;
  cout << enemy->getProvincesNum() << endl;

  provincesCleanup(enemy);

  if (enemy->getProvincesNum() == 0)
  {
    printF (">Player \'" , 0 , MAG , BOLD);
    cout << *defName; 
    printF ("\' is out of the game! Better luck next time. =)" , 1 , MAG , BOLD);
  }

  for (auto i : *attArmy) i->setTapped(); // Tap attackers so they can't be used again for the round
}

/* ========================================================================= */

void provincesCleanup(PlayerPtr player)
{
  ProvinceListPtr prov = player->getProvinces();

  for (auto it = prov->begin(); it != prov->end(); )
  {
    if ((*it)->checkBroken() == true)
      it = prov->erase(it);
    else
      ++it;
  }
}
/* ========================================================================= */

void draw()
{
  printF ("Battle between \'" , 0 , RED , BOLD);
  cout << *attName;
  printF ("\' and \'" , 0 , RED , BOLD); 
  cout << *defName;
  printF (" ends as a draw! Both armies are destroyed!" , 1 , RED , BOLD);

  for (auto i : *attArmy) i->die();
  for (auto i : *defArmy) i->die();  
}
/* ========================================================================= */

void verifyCasualties(ArmyPtr battleArmy, int side)
{
  for (auto i : *battleArmy)
  {
    if (i->getATK() >= ptsDiff) 
      i->die();
    else
    {
      FollowerListPtr followers = i->getFollowers();
      for (auto j : *followers)
        if (j->getATK() >= ptsDiff) // delete followers
          j->detach(); // should do that
    }
  }

  for (auto i : *battleArmy) i->setTapped(); // Tap defenders so they can't be used again for the round
    
  for (auto i : *battleArmy) // decrease Item durability
  {
    ItemListPtr items = i->getItems();
    
    for (auto j : *items) 
    {
      j->decreaseDurability(); // todo: cleanup if 0
      if (j->getDurability() == 0) j->detach(); // should enable that
    }
  }

  if (side == ATTACK)
  {
    for (auto i : *battleArmy) //decrease personalities honor
    {   
      i->decreaseHonor();
      if (i->getHonor() == 0) i->kys(); // just kys
    }
  }
}
/* ========================================================================= */

void attackerWins()
{
  printF ("Attacker " , 0 , RED , BOLD);
  cout << *attName;
  printF (" destroys " , 0 , RED , BOLD);
  cout << *defName; 
  printF (" \'s army, but is unable to break the province!" , 1 , RED , BOLD);

  for (auto i : *defArmy) i->die(); // todo: cleanup dead from their lists
  printF ("Defender's army is destroyed." , 1 , RED , BOLD);

  printF ("Attacker's army has experienced heavy casualties." , 1 , RED , BOLD); 
  verifyCasualties(attArmy, ATTACK);
}
/* ========================================================================= */

void defenderWins()
{
  printF ("Defender " , 0 , RED , BOLD);
  cout << *defName;
  printF ("holds his ground against " , 1 , RED , BOLD);
  cout << *attName; 
  printF (" \'s army!" , 1 , RED , BOLD);

  for (auto i : *attArmy) i->die(); // todo: cleanup dead from their lists
  printF ("Attacker's army is destroyed." , 1 , RED , BOLD);

  printF ("Defender's army has experienced heavy casualties." , 1 , RED , BOLD); 
  verifyCasualties(attArmy, DEFEND);
}
/* ========================================================================= */

void battle(ProvincePtr prov)
{
  int32_t attPoints = calcTotalATK(attArmy);
  int32_t defPoints = calcTotalDEF(defArmy);// + enemy->getStrongHold()->getInitDEF(); // todo: verify @lists

  printF ("Attacker's ARMY strength is: " , 1 , MAG , BOLD);
  cout << attPoints << endl;
  printF ("Defender's ARMY strength is: " , 1 , MAG , BOLD);
  cout << defPoints << endl;

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

void Game::battlePhase(PlayerPtr player)
{
  printF ("Battle phase begins!" , 1 , RED , FILL);
  printF ("Press ENTER to continue . . ." , 1);
  std::cin.clear();
  std::cin.sync();
  std::cin.get();

  ::player = player;

  int action = chooseAction();

  if (action == DEFEND)
  {
    printF ("Player \"" , 0 , RED , BOLD);
    cout << player->getUserName(); 
    printF ("\" chose to DEFEND this round!" , 1 , RED , BOLD);
    return;
  }
  // action == ATTACK
  enemy = chooseEnemy(player, players);

  attName = &player->getUserName();
  defName = &enemy ->getUserName();

  ProvincePtr prov = chooseProvince(enemy);

  attArmy = std::make_shared< std::list <std::shared_ptr< Personality>>>(); //TODO: delete this
  chooseArmy(player, attArmy);

  printF ("Player \'" , 0 , RED , BOLD);
  cout << *defName; 
  printF ("\' shall pick their DEFENSE!" , 1 , RED , BOLD);

  defArmy = std::make_shared< std::list <std::shared_ptr< Personality>>>(); //TODO: delete this
  chooseArmy(enemy, defArmy);

  /* Battle */
  battle(prov);

  // delete attArmy;
  // delete defArmy;
}
/* ========================================================================= */
