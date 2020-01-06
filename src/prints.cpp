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
void printF (const std::string & s , const size_t & colour , const size_t & format ) {
  std::cout << "\x1B[" << format << ";" << colour << "m" << s << "\x1B[0m" << std::endl;
}

/* ========================================================================= */

void Card::print() const
{
  cout << "Name:   " << name << endl;
  cout << "Cost:   " << cost << endl;
  cout << "Tapped: " << (isTapped ? "YES" : "NO") << endl;  
}
/* ========================================================================= */

void GreenCard::print() const
{
  printF ("======  GREEN CARD  ======" , GRN);
  
  this->Card::print();
  
  cout << "ATK Bonus: " << attackBonus << endl;
  cout << "DEF Bonus: " << defenceBonus << endl;
  cout << "Min Honor: " << minHonor << endl;
  cout << "Card Text: " << cardText << endl;
  cout << "Effect Bonus: " << effectBonus << endl;
  cout << "Effect Cost : " << effectCost  << endl;
  // cout << GRN << "====== !GREEN CARD! ======" << RST << endl;
}
/* ========================================================================= */

void Follower::print() const
{
  this->GreenCard::print();
  printF ("====== !GREEN CARD! ======" , GRN);
}
/* ========================================================================= */

void Item::print() const
{
  this->GreenCard::print();
  cout << "Durability: " << durability << endl;
  printF ("====== !GREEN CARD! ======" , GRN);
}
/* ========================================================================= */

void BlackCard::print() const // TODO: fix color
{
  printF ("======  BLACK CARD  ======" , RED);
  this->Card::print();

  cout << "Revealed: " << (isRevealed ? "YES" : "NO") << endl;
}
/* ========================================================================= */

void Personality::print() const
{
  this->BlackCard::print();

  cout << "ATK:   " << attack  << endl;
  cout << "DEF:   " << defence << endl;
  cout << "Honor: " << honor   << endl;

  printF ("==  FOLLOWERS  == " , YEL);
  for (auto i : *followers)
    i->print();
  printF ("== !FOLLOWERS! == " , YEL);

  printF ("==  ITEMS  == " , YEL);
  for (auto i : *items)
    i->print();
  printF ("== !ITEMS! == " , YEL);

  printF ("====== !BLACK CARD! ======" , RED);
}

/* ========================================================================= */

void Holding::print() const
{
  this->BlackCard::print();

  cout << "Harvest value: " << harvestValue << endl;

  printF ("====== !BLACK CARD! ======" , RED);
}

/* ========================================================================= */

void Mine::print() const
{
  this->BlackCard::print();
  cout << "Harvest value: " << harvestValue << endl;

  if (upperHolding)
  {
    printF ("==  UpperHolding  ==" , CYN);
    upperHolding->print();
    printF ("== !UpperHolding! ==" , CYN);
  }

  printF ("====== !BLACK CARD! ======" , RED);
}

/* ========================================================================= */

void GoldMine::print() const
{
  this->BlackCard::print();
  cout << "Harvest value: " << harvestValue << endl;

  if (upperHolding)
  {
    printF ("==  UpperHolding  ==" , CYN);
    upperHolding->print();
    printF ("== !UpperHolding! ==" , CYN);
  }

  if (subHolding)
  {
    printF ("==  subHolding  ==" , CYN);
    subHolding->print();
    printF ("== !subHolding! ==" , CYN);
  }

  printF ("====== !BLACK CARD! ======" , RED);
}
/* ========================================================================= */

void CrystalMine::print() const
{
  this->BlackCard::print();
  cout << "Harvest value: " << harvestValue << endl;

  if (subHolding)
  {
    printF ("==  subHolding  ==" , CYN);
    subHolding->print();
    printF ("== !subHolding! ==" , CYN);
  }

  printF ("====== !BLACK CARD! ======" , RED);
}
/* ========================================================================= */

void StrongHold::print() const
{
  this->BlackCard::print();
  cout << "Harvest value: " << harvestValue << endl;

  cout << "Starting Honor: " << initHonor << endl;
  cout << "Starting DEF  : " << initDefence << endl;  

  printF ("====== !BLACK CARD! ======" , RED);
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
  printF ("=======  PLAYER  =======" , BLU);
  cout << "User : " << userName << endl;
  cout << "Honor: " << honor << endl;
  cout << "Active Provinces: " << activeProvinces << endl;

  //probz shouldnt do that here // printHand();
  printF ("=====  HOLDINGS  =====" , MAG);
  printHoldings();
  printF ("===== !HOLDINGS! =====" , MAG);

  printF ("=====  ARMY  =====" , MAG);
  printArmy();
  printF ("===== !ARMY! =====" , MAG);

  printF ("======= !PLAYER! =======" , BLU);
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
  if (army->size() == 0) 
    cout << "No army!" << endl;
  else
    for (auto i : *army) i->print();
}
/* ========================================================================= */

void Player::printAvailableArmy() const
{
  if (army->size() == 0) 
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
  if (hand->size() == 0) 
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