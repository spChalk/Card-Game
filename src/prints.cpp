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
  printF("| " , 0 , MAG); cout << "Name: " << name << endl;
  printF("| " , 0 , MAG); cout << "Cost:   " << cost << endl;
  printF("| " , 0 , MAG); cout << "Tapped: " << (isTapped ? "YES" : "NO") << endl;  
}
/* ========================================================================= */

void GreenCard::print() const
{
  printF ("/=======  GREEN CARD  =======\\" , 1 ,GRN);
  // [Harry] added the MAG lines cuz greencards dont care about being tapped
  printF("| " , 0 , MAG); cout << "Name: " << name << endl;
  printF("| " , 0 , MAG); cout << "Cost:   " << cost << endl;
  printF ("| " , 0 , GRN); cout << "ATK Bonus: " << attackBonus << endl;
  printF ("| " , 0 , GRN); cout << "DEF Bonus: " << defenceBonus << endl;
  printF ("| " , 0 , GRN); cout << "Min Honor: " << minHonor << endl;
  printF ("| " , 0 , GRN); cout << "Effect Bonus: " << effectBonus << endl;
  printF ("| " , 0 , GRN); cout << "Effect Cost : " <<effectCost  << endl;
}
/* ========================================================================= */

void Follower::print() const
{
  this->GreenCard::print();
  printF ("| " , 0 , GRN); cout << "Card Text: " << cardText << endl;
  printF ("\\____________________________/" , 1 , GRN);
  cout << endl;
}
/* ========================================================================= */

void Item::print() const
{
  this->GreenCard::print();
  printF("| " , 0 , GRN); cout << "Durability: " << durability << endl;
  printF ("| " , 0 , GRN); cout << "Card Text: " << cardText << endl;
  printF ("\\____________________________/" , 1 , GRN);
  cout << endl;
}
/* ========================================================================= */

void BlackCard::print() const // TODO: fix color
{
  printF ("/=======  BLACK CARD  =======\\" , 1 , RED);
  this->Card::print();

  printF ("| " , 0 , RED); cout << "Revealed: " << (isRevealed ? "YES" : "NO") << endl;
}
/* ========================================================================= */

void Personality::print() const
{
  this->BlackCard::print();

  printF ("| " , 0 , RED); cout << "ATK:   " << attack  << endl;
  printF ("| " , 0 , RED); cout << "DEF:   " << defence << endl;
  printF ("| " , 0 , RED); cout << "Honor: " << honor   << endl;

  printF ("==  FOLLOWERS  == " , 0 , YEL); cout << endl;
  for (auto i : *followers)
    i->print();
  printF ("== !FOLLOWERS! == " , 0 , YEL); cout << endl;

  printF ("==  ITEMS  == " , 0 , YEL); cout << endl;
  for (auto i : *items)
    i->print();
  printF ("== !ITEMS! == " , 0 , YEL); cout << endl;

  printF ("\\____________________________/" , 1 ,RED); 
  cout << endl;
}

/* ========================================================================= */

void Holding::print() const
{
  this->BlackCard::print();

  printF("| " , 0 , RED); cout << "Harvest value: " << harvestValue << endl;

  printF ("\\____________________________/" , 1 , RED);
  cout << endl; 
}

/* ========================================================================= */

void Mine::print() const
{
  this->BlackCard::print();
  printF("| " , 0 , RED); cout << "Harvest value: " << harvestValue << endl;

  if (upperHolding)
  {
    printF ("==  UpperHolding  ==" , 0 , CYN); cout << endl;
    upperHolding->print();
    printF ("== !UpperHolding! ==" , 0 , CYN); cout << endl;
  }

  printF ("\\____________________________/" , 1 , RED);
  cout << endl;
}

/* ========================================================================= */

void GoldMine::print() const
{
  this->BlackCard::print();
  printF("| " , 0 , RED); cout << "Harvest value: " << harvestValue << endl;

  if (upperHolding)
  {
    printF ("==  UpperHolding  ==" , 0 , CYN);
    upperHolding->print();
    printF ("== !UpperHolding! ==" , 0 , CYN);
  }

  if (subHolding)
  {
    printF ("==  subHolding  ==" , 0 , CYN);
    subHolding->print();
    printF ("== !subHolding! ==" , 0 , CYN);
  }

  printF ("\\____________________________/" , 1 , RED);
  cout << endl;
}
/* ========================================================================= */

void CrystalMine::print() const
{
  this->BlackCard::print();
  printF("| " , 0 , RED); cout << "Harvest value: " << harvestValue << endl;

  if (subHolding)
  {
    printF ("==  subHolding  ==" , 0 , CYN);
    subHolding->print();
    printF ("== !subHolding! ==" , 0 , CYN);
  }

  printF ("\\____________________________/" , 1 , RED);
  cout << endl;
}
/* ========================================================================= */

void StrongHold::print() const
{
  this->BlackCard::print();
  printF("| " , 0 , RED); cout << "Harvest value: " << harvestValue << endl;

  printF("| " , 0 , RED); cout << "Starting Honor: " << initHonor << endl;
  printF("| " , 0 , RED); cout << "Starting DEF  : " << initDefence << endl;  

  printF ("\\____________________________/" , 1 , RED);
  cout << endl;
}
/* ========================================================================= */

void Province::print() const
{
  if (isBroken == true)
    cout << "!! Broken Province !!" << endl;
  else if (card->checkRevealed() == false)
    cout << "!! Hidden Province !!" << endl;
  else
    card->print();
}
/* ========================================================================= */

void Player::print() const
{
  printF ("|=======  PLAYER  =======|" , 1 , BLU);
  cout << "User : " << userName << endl;
  cout << "Honor: " << honor << endl;
  cout << "Active Provinces: " << activeProvinces << endl;

  //probz shouldnt do that here // printHand();
  printF ("=====  HOLDINGS  =====" , 1 , MAG);
  printHoldings();
  printF ("===== !HOLDINGS! =====" , 1 , MAG); cout << endl;

  printF ("=====  ARMY  =====" , 1 , MAG);
  printArmy();
  printF ("===== !ARMY! =====" , 1 , MAG); cout << endl;

  printF ("======= !PLAYER! =======" , 1 , BLU); cout << endl;
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