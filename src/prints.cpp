/* prints.cpp */

#include <iostream>

#include "basicHeader.hpp"

// Colours
#define BLK  30
#define RED  31
#define GRN  32
#define YEL  33
#define BLU  34
#define MAG  35
#define CYN  36
#define WHT  37

// Styles
#define BOLD  1 
#define ITLC  3
#define FILL  7
#define UNDR  4

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
  printF("| " , 0 , GRN); cout << "Name: " << name << endl;
  printF("| " , 0 , GRN); cout << "Cost:   " << cost << endl;
  printF("| " , 0 , GRN); cout << "Tapped: " << (isTapped ? "YES" : "NO") << endl;  
}
/* ========================================================================= */

void GreenCard::print() const
{
  printF ("/=======  GREEN CARD  =======\\" , 1 ,GRN);
  
  this->Card::print();
  
  printF ("| " , 0 , GRN); cout << "ATK Bonus: " << attackBonus << endl;
  printF ("| " , 0 , GRN); cout << "DEF Bonus: " << defenceBonus << endl;
  printF ("| " , 0 , GRN); cout << "Min Honor: " << minHonor << endl;
  printF ("| " , 0 , GRN); cout << "Card Text: " << cardText << endl;
  printF ("| " , 0 , GRN); cout << "Effect Bonus: " << effectBonus << endl;
  printF ("| " , 0 , GRN); cout << "Effect Cost : " <<effectCost  << endl;
}
/* ========================================================================= */

void Follower::print() const
{
  this->GreenCard::print();
  printF ("\\____________________________/" , 1 , GRN);
  cout << endl;
}
/* ========================================================================= */

void Item::print() const
{
  this->GreenCard::print();
  printF("| " , 0 , GRN); cout << "Durability: " << durability << endl;
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
  cout << "\nPrinting statistics for player: " << getUserName() << endl;
  cout << "=======   BEGINNING OF STATS  =======" << endl;
  cout << "\nHonor: " << honor << endl; // might remove this
  cout << "\nActive provinces: " << activeProvinces << endl;

  if (activeProvinces == 0)
  {
    cout << "======= !END OF STATS! =======" << endl;
    cout << "\nPlayer: " << getUserName() << " is out of the game!" << endl;
  }

  cout << "\nCards remaining on Fate deck (Greencards): " 
       << fateDeck->size() << endl;
  cout << "\nCards remaining on Dynasty deck (Blackcards): " 
       << dynastyDeck->size() << endl;
  cout << "\nPrinting hand: " << endl;
  printHand();
  cout << "\nPrinting provinces: " << endl;
  printProvinces();
  cout << "\nPrinting army: " << endl;
  printArmy();
  cout << "\nPrinting holdings: " << endl;
  printHoldings();
  cout << "======= !END OF STATS! =======" << endl;
}

/* ========================================================================= */

void Game::printGameStatistics() const
{
  cout << " Printing global game statistics!" << endl;
  cout << "=========  BEGINNING OF GLOBAL STATS  =========" << endl;
  // could also print the current round
  for (auto i : *players)
    i->printStatistics();

  cout << "========= !END OF GLOBAL STATS! =========" << endl;
}
/* ========================================================================= */