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

/* Pick an enemy to Attack */
PlayerPtr chooseEnemy(PlayerPtr current, PlayerListPtr players)
{
  printF("Choose an enemy! Available enemies are:" , 1 , RED , BOLD);

  PlayerPtr enemy;
  for (int status = WRONG_INPUT; status != CORRECT_INPUT; )
  {
    for (auto i : *players)
    {
      if (i->getProvincesNum() == 0 || i == current) 
        continue;       /* Skip himself & players that are out of the game */
      
      cout << i->getUserName() << endl;
    }

    printF("> Your pick: " , 0 , RED , BOLD);

    std::string enemyName;
    std::getline(std::cin, enemyName);
    cout << enemyName << endl;

    for (auto i: *players)  /* Verify that the enemy selection is valid */
    {
      if (i->getProvincesNum() == 0 || i == current) 
        continue;

      if (i->getUserName() == enemyName)
      {
        enemy = i;
        status = CORRECT_INPUT;   /* Valid */
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

int chooseAction(void)      /* Choose whether to Attack of Defend */
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

  return (answer == "ATK" || answer == "atk") 
        ? ATTACK 
        : DEFEND;
}

/* ========================================================================= */

/* Wrap std::stoi because it may throw an exception */
int32_t stoiWrapper(const std::string& str, int32_t* p_value, std::size_t* pos = 0, int base = 10)
{
  try {
    *p_value = std::stoi(str, pos, base);
    return 0;
  }
  catch (const std::invalid_argument& ia){
    return -1;
  }
  catch (const std::out_of_range& oor){
    return -2;
  }
  catch (const std::exception& e){
    return -3;
  }
}

/* Pick a province to Attack */
ProvincePtr chooseProvince(PlayerPtr player)
{
  printF ("Choose a province to attack! Available provinces are:" , 1 , RED , BOLD);
  player->printProvinces();

  std::string answer;
  int32_t prov;

  while (true)    /* Make sure a valid input is given */
  {
    printF ("Make your selection based in the order of appearance. \n \
             Your input should be an integer in range " , 0 , MAG , BOLD);
    cout << "[1," << player->getProvincesNum() << "]."; 
    printF ("\n> Choose province number: " , 0 , MAG , BOLD );
    
    int32_t *res = nullptr;
    do {        /* stoi exception handling */

      std::getline(std::cin, answer);
      cout << endl;
  
    } while (stoiWrapper(answer, res) < 0 
          && printf("> Invalid argument given! Please, give an integer!\n"));

    prov = *res;
    if (prov > 0 && prov <= player->getProvincesNum()) 
      break;
  
    printF ("> Wrong input given. Please, try again." , 1 , MAG , BOLD);
  }

  uint16_t counter = 0;
  for (auto i : *(player->getProvinces()))
  {
    if (i->checkBroken() == true) 
      continue;
    
    if (++counter == prov) 
      return i;     /* Found the province to attack */
  }

  return nullptr;   /* Control will not reach here */
}

/* ========================================================================= */

/* Player gets to gather their army */
void chooseArmy(PlayerPtr player, ArmyPtr battleArmy)
{
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
    if (i->checkTapped() == true)  /* Make sure the card is not tapped */
      continue;

    i->print();
    printF ("\nRecruit? ", 1 , RED , BOLD);
    printF ("> Your answer: " , 0 , BLU , BOLD);
    std::string answer;
    std::getline(std::cin, answer);
    cout << answer << endl;

    if (answer == "Y" || answer == "y") 
      battleArmy->push_back(i);
  }
}

/* ========================================================================= */

int32_t calcTotalATK(ArmyPtr battleArmy)  /* Calculate total attack points */
{
  int32_t totalATK = 0;

  for (auto i : *battleArmy)
  {
    FollowerListPtr followers = i->getFollowers();
    ItemListPtr     items = i->getItems();

    totalATK += i->getATK();

    for (auto j : *followers)
      totalATK += j->getATK();

    for (auto j : *items)
      totalATK += j->getATK();
  }

  return totalATK;
}

/* ========================================================================= */

int32_t calcTotalDEF(ArmyPtr battleArmy)  /* Calculate total defence points */
{
  int32_t totalDEF = 0;

  for (auto i : *battleArmy)
  {
    FollowerListPtr followers = i->getFollowers();
    ItemListPtr     items = i->getItems();

    totalDEF += i->getDEF();

    for (auto j : *followers)
      totalDEF += j->getDEF();

    for (auto j : *items)
      totalDEF += j->getDEF();
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

  for (auto i : *defArmy)   /* Every personality dies */
    i->die();
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

  for (auto i : *attArmy)
    i->setTapped();  /* Tap attackers so they can't be used again for the round */
}

/* ========================================================================= */

/* Remove broken provinces from a player */
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

  for (auto i : *attArmy)
    i->die();
  
  for (auto i : *defArmy)
    i->die();  
}

/* ========================================================================= */

/* Handle casualties depending on the side (Attacker / Defender) */
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
        if (j->getATK() >= ptsDiff)     /* Remove followers */
          j->detach();
    }
  }

  for (auto i : *battleArmy)
    i->setTapped();     /* Tap defenders so they can't be used again for this round */
    
  for (auto i : *battleArmy)          /* Decrease Item durability */
  {
    ItemListPtr items = i->getItems();
    
    for (auto j : *items) 
    {
      j->decreaseDurability();
      if (j->getDurability() == 0)    /* Remove broken Items */
        j->detach();
    }
  }

  if (side == ATTACK)
  {
    for (auto i : *battleArmy)      /* Decrease personalities honor */
    {   
      i->decreaseHonor();
      if (i->getHonor() == 0)       /* Commit suicide */
        i->kys();
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

  for (auto i : *defArmy)     /* Defending army perishes */
    i->die();
  printF ("Defender's army is destroyed." , 1 , RED , BOLD);

  printF ("Attacker's army has experienced heavy casualties." , 1 , RED , BOLD);

  verifyCasualties(attArmy, ATTACK);  /* Handle casualties based on the result */
}
/* ========================================================================= */

void defenderWins()
{
  printF ("Defender " , 0 , RED , BOLD);
  cout << *defName;
  printF ("holds his ground against " , 1 , RED , BOLD);
  cout << *attName; 
  printF (" \'s army!" , 1 , RED , BOLD);

  for (auto i : *attArmy)     /* Attacking army perishes */
    i->die();
  printF ("Attacker's army is destroyed." , 1 , RED , BOLD);

  printF ("Defender's army has experienced heavy casualties." , 1 , RED , BOLD);

  verifyCasualties(attArmy, DEFEND);  /* Handle casualties based on the result */
}
/* ========================================================================= */

void battle(ProvincePtr prov)
{
  int32_t attPoints = calcTotalATK(attArmy);
  int32_t defPoints = calcTotalDEF(defArmy);

  printF ("Attacker's ARMY strength is: " , 1 , MAG , BOLD);
  cout << attPoints << endl;
  printF ("Defender's ARMY strength is: " , 1 , MAG , BOLD);
  cout << defPoints << endl;

  ptsDiff = attPoints - defPoints;

  if (attPoints > defPoints + enemy->getStrongHold()->getInitDEF())
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

  attArmy = std::make_shared< std::list <std::shared_ptr< Personality>>>();
  chooseArmy(player, attArmy);

  printF ("Player \'" , 0 , RED , BOLD);
  cout << *defName; 
  printF ("\' shall pick their DEFENSE!" , 1 , RED , BOLD);

  defArmy = std::make_shared< std::list <std::shared_ptr< Personality>>>();
  chooseArmy(enemy, defArmy);

  battle(prov);   /* Battle */
}

/* ========================================================================= */