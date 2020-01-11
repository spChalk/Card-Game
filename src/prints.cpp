/* prints.cpp */

#include <iostream>

#include "basicHeader.hpp"

using std::cout;
using std::endl;

/* ========================================================================= */

//  Write formatted output to stdout (args : colour & style)
void printF (const std::string & s , bool printEndl ,const uint16_t & colour , const uint16_t & format ) {
  std::cout << "\x1B[" << format << ";" << colour << "m" << s << "\x1B[0m" << (printEndl ? "\n" : "");
}

/* ========================================================================= */

void Card::print() const
{
  printF("| Name: " , 0 , MAG , BOLD); cout << name << endl;
  printF("| Cost:   " , 0 , MAG , BOLD); cout << cost << endl;
  printF("| Tapped: " , 0 , MAG , BOLD); cout << (isTapped ? "YES" : "NO") << endl;  
}
/* ========================================================================= */

void GreenCard::print() const
{
  printF ("/=======  GREEN CARD  =======\\" , 1 , GRN );
  // [Harry] added the MAG lines cuz greencards dont care about being tapped
  printF("| Name: " , 0 , MAG , BOLD); cout << name << endl;
  printF("| Cost:   " , 0 , MAG , BOLD); cout << cost << endl;
  printF ("| ATK Bonus: " , 0 , GRN , BOLD); cout << attackBonus << endl;
  printF ("| DEF Bonus: " , 0 , GRN , BOLD); cout << defenceBonus << endl;
  printF ("| Min Honor: " , 0 , GRN , BOLD); cout << minHonor << endl;
  printF ("| Effect Bonus: " , 0 , GRN , BOLD); cout << effectBonus << endl;
  printF ("| Effect Cost: " , 0 , GRN , BOLD); cout <<effectCost  << endl;
}
/* ========================================================================= */

void Follower::print() const
{
  this->GreenCard::print();
  printF ("| Card Text: " , 0 , GRN , BOLD); cout << cardText << endl;
  printF ("\\____________________________/" , 1 , GRN );
  cout << endl;
}
/* ========================================================================= */

void Item::print() const
{
  this->GreenCard::print();
  printF("| Durability: " , 0 , GRN , BOLD); cout << durability << endl;
  printF ("| Card Text: " , 0 , GRN , BOLD); cout << cardText << endl;
  printF ("\\____________________________/" , 1 , GRN );
  cout << endl;
}
/* ========================================================================= */

void BlackCard::print() const // TODO: fix color
{
  printF ("/=======  BLACK CARD  =======\\" , 1 , RED);
  this->Card::print();

  printF ("| Revealed: " , 0 , RED , BOLD); cout << (isRevealed ? "YES" : "NO") << endl;
}
/* ========================================================================= */

void Personality::print() const
{
  this->BlackCard::print();

  printF ("| ATK:   " , 0 , RED , BOLD); cout << attack  << endl;
  printF ("| DEF:   ", 0 , RED , BOLD); cout << defence << endl;
  printF ("| Honor: " , 0 , RED , BOLD); cout << honor   << endl;

  printF ("|--  FOLLOWERS  -- " , 0 , YEL); cout << endl;
  for (auto i : *followers)
    i->print();
  printF ("|-- !FOLLOWERS! -- " , 0 , YEL); cout << endl;

  printF ("|--  ITEMS  -- " , 0 , YEL); cout << endl;
  for (auto i : *items)
    i->print();
  printF ("|-- !ITEMS! -- " , 0 , YEL); cout << endl;

  printF ("\\____________________________/" , 1 , RED); 
  cout << endl;
}

/* ========================================================================= */

void Holding::print() const
{
  this->BlackCard::print();

  printF("| Harvest value: " , 0 , RED , BOLD); cout << harvestValue << endl;

  printF ("\\____________________________/" , 1 , RED);
  cout << endl; 
}

/* ========================================================================= */

void Mine::print() const
{
  this->BlackCard::print();
  printF("| Harvest value: " , 0 , RED , BOLD); cout << harvestValue << endl;

  if (upperHolding)
  {
    printF ("|--  UpperHolding  --" , 0 , CYN); cout << endl;
    upperHolding->print();
    printF ("|-- !UpperHolding! --" , 0 , CYN); cout << endl;
  }

  printF ("\\____________________________/" , 1 , RED);
  cout << endl;
}

/* ========================================================================= */

void GoldMine::print() const
{
  this->BlackCard::print();
  printF("| Harvest value: " , 0 , RED , BOLD); cout << harvestValue << endl;

  if (upperHolding)
  {
    printF ("|--  UpperHolding  --" , 0 , CYN);
    upperHolding->print();
    printF ("|-- !UpperHolding! --" , 0 , CYN);
  }

  if (subHolding)
  {
    printF ("|--  subHolding  --" , 0 , CYN);
    subHolding->print();
    printF ("|-- !subHolding! --" , 0 , CYN);
  }

  printF ("\\____________________________/" , 1 , RED);
  cout << endl;
}
/* ========================================================================= */

void CrystalMine::print() const
{
  this->BlackCard::print();
  printF("| Harvest value: " , 0 , RED , BOLD); cout << harvestValue << endl;

  if (subHolding)
  {
    printF ("|--  subHolding  --" , 0 , CYN);
    subHolding->print();
    printF ("|-- !subHolding! --" , 0 , CYN);
  }

  printF ("\\____________________________/" , 1 , RED);
  cout << endl;
}
/* ========================================================================= */

void StrongHold::print() const
{
  this->BlackCard::print();
  printF("| Harvest value: " , 0 , RED , BOLD); cout << harvestValue << endl;

  printF("| Starting Honor: " , 0 , RED , BOLD); cout << initHonor << endl;
  printF("| Starting DEF  :" , 0 , RED , BOLD); cout << initDefence << endl;  

  printF ("\\____________________________/" , 1 , RED);
  cout << endl;
}
/* ========================================================================= */

void Province::print() const
{
  if (isBroken == true)
    printF ("!! Broken Province !!" , 1 , RED , BOLD);
  else if (card->checkRevealed() == false)
    printF ("!! Hidden Province !!" , 1 , RED); 
  else
    card->print();
}
/* ========================================================================= */

void Player::print() const
{
  printF ("|=======  PLAYER  =======|" , 1 , BLU , UNDR);
  printF ("| User : " , 0 , BLU , BOLD); 
  cout << userName << endl;
  printF ("| Honor: " , 0 , BLU , BOLD); 
  cout << honor << endl;
  printF ("| Active Provinces: " , 0 , BLU , BOLD); 
  cout << activeProvinces << endl;

  //probz shouldnt do that here // printHand();
  printF ("|-----  HOLDINGS  -----" , 1 , MAG);
  printHoldings();
  printF ("|----- !HOLDINGS! -----" , 1 , MAG); cout << endl;

  printF ("|-----  ARMY  -----" , 1 , MAG);
  printArmy();
  printF ("|----- !ARMY! -----" , 1 , MAG); cout << endl;

  printF ("|======= !PLAYER! =======|" , 1 , BLU , UNDR); cout << endl;
}
/* ========================================================================= */

void Player::printHoldings() const
{
  strongHold->print();

  for (auto i : *holdings) i->print();
}
/* ========================================================================= */

void Player::printArmy() const
{
  if (army->empty() == true) 
    cout << "No army!" << endl;
  else
    for (auto i : *army) i->print();
}
/* ========================================================================= */

void Player::printAvailableArmy() const
{
  if (army->empty() == true) 
    cout << "No army!" << endl;
  else
    for (auto i : *army)
    {  
      if (i->checkTapped() == false) // if untapped
        i->print();
    }
}

/* ========================================================================= */

void Player::printHand() const 
{
  if (hand->empty() == true) 
    cout << "Empty hand!" << endl;
  else
    for (auto i : *hand) i->print();
}

/* ========================================================================= */

void Player::printProvinces() const {
  for (auto i : *provinces) i->print();
}
/* ========================================================================= */

void Player::printArena() const { this->printArmy(); }

/* ========================================================================= */

void Player::printStatistics() const
{
  cout << endl;
  printF("Printing statistics for player: " , 0 , YEL , UNDR); 
  cout << getUserName() << endl;
  printF("=======||   BEGINNING OF STATS  ||=======" , 1 , MAG , BOLD);
  cout << endl; printF("Honor: " , 0 , YEL , UNDR); 
  cout << honor << endl; // might remove this
  cout << endl; printF("Active provinces: " , 0 , YEL , UNDR);
  cout << activeProvinces << endl;

  if (activeProvinces == 0)
  {
    printF("=======||  END OF STATS  ||=======" , 1 , MAG , BOLD);
    cout << endl; printF("Player: " , 0 , WHT ,BOLD); 
    cout << getUserName();
    printF ( " is out of the game!" , 0 , WHT , BOLD); 
    cout << endl;
  }

  cout << endl; printF("Cards remaining on Fate deck (Greencards): " , 0 , GRN , BOLD); 
  cout << fateDeck->size() << endl;
  cout << endl; printF("Cards remaining on Dynasty deck (Blackcards): " , 0 , RED , BOLD); 
  cout << dynastyDeck->size() << endl;
  cout << endl; printF("Printing hand: " , 1 , YEL , UNDR);
  printHand();
  cout << endl; printF("Printing provinces: " , 1 , YEL , UNDR); 
  printProvinces();
  cout << endl; printF("Printing army: " , 1 , YEL , UNDR);
  printArmy();
  cout << endl; printF("Printing holdings: " , 1 , YEL , UNDR);
  printHoldings();
  printF("=======||  END OF STATS  ||=======" , 1 , MAG ,BOLD);
}

/* ========================================================================= */

void Game::printGameStatistics() const
{
  printF ("Printing global game statistics!" , 1 , MAG , UNDR);
  printF("=========||  BEGINNING OF GLOBAL STATS  ||=========" , 1 , MAG , FILL);
  // could also print the current round
  for (auto i : *players)
    i->printStatistics();

  printF("=========||  END OF GLOBAL STATS  ||=========" , 1 , MAG , FILL);
}
/* ========================================================================= */