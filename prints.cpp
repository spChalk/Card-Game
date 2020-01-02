/* prints.cpp */

#include <iostream>

#include "baseClasses.h"

#define RST "\033[0m"
#define BLK "\033[30m"  /* Black */
#define RED "\033[31m"  /* Red */
#define GRN "\033[32m"  /* Green */
#define YEL "\033[33m"  /* Yellow */
#define BLU "\033[34m"  /* Blue */
#define MAG "\033[35m"  /* Magenta */
#define CYN "\033[36m"  /* Cyan */
#define WHT "\033[37m"  /* White */

using std::cout;
using std::endl;

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
  cout << GRN << "======  GREEN CARD  ======" << RST << endl;
  this->Card::print();
  
  cout << "ATK Bonus: " << name << endl;
  cout << "DEF Bonus: " << cost << endl;
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
  cout << GRN << "====== !GREEN CARD! ======" << RST << endl;
}
/* ========================================================================= */

void Item::print() const
{
  this->GreenCard::print();
  cout << "Durability: " << durability << endl;
  cout << GRN << "====== !GREEN CARD! ======" << RST << endl;
}
/* ========================================================================= */

void BlackCard::print() const // TODO: fix color
{
  cout << RED << "======  BLACK CARD  ======" << RST << endl;
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

  cout << YEL << "==  FOLLOWERS  == " << RST << endl;
  for (auto *i : *followers)
    i->print();
  cout << YEL << "== !FOLLOWERS! == " << RST << endl;

  cout << YEL << "==  ITEMS  == " << RST << endl;
  for (auto *i : *items)
    i->print();
  cout << YEL << "== !ITEMS! == " << RST << endl;

  cout << RED << "====== !BLACK CARD! ======" << RST << endl;
}

/* ========================================================================= */

void Holding::print() const
{
  this->BlackCard::print();

  cout << "Harvest value: " << harvestValue << endl;

  cout << RED << "====== !BLACK CARD! ======" << RST << endl;
}

/* ========================================================================= */

void Mine::print() const
{
  this->BlackCard::print();
  cout << "Harvest value: " << harvestValue << endl;

  if (upperHolding)
  {
    cout << CYN << "==  UpperHolding  ==" << RST << endl;
    upperHolding->print();
    cout << CYN << "== !UpperHolding! ==" << RST << endl;
  }

  cout << RED << "====== !BLACK CARD! ======" << RST << endl;
}

/* ========================================================================= */

void GoldMine::print() const
{
  this->BlackCard::print();
  cout << "Harvest value: " << harvestValue << endl;

  if (upperHolding)
  {
    cout << CYN << "==  UpperHolding  ==" << RST << endl;
    upperHolding->print();
    cout << CYN << "== !UpperHolding! ==" << RST << endl;
  }

  if (subHolding)
  {
    cout << CYN << "==  subHolding  ==" << RST << endl;
    subHolding->print();
    cout << CYN << "== !subHolding! ==" << RST << endl;
  }

  cout << RED << "====== !BLACK CARD! ======" << RST << endl;
}
/* ========================================================================= */

void CrystalMine::print() const
{
  this->BlackCard::print();
  cout << "Harvest value: " << harvestValue << endl;

  if (subHolding)
  {
    cout << CYN << "==  subHolding  ==" << RST << endl;
    subHolding->print();
    cout << CYN << "== !subHolding! ==" << RST << endl;
  }

  cout << RED << "====== !BLACK CARD! ======" << RST << endl;
}
/* ========================================================================= */

void StrongHold::print() const
{
  this->BlackCard::print();
  cout << "Harvest value: " << harvestValue << endl;

  cout << "Starting Honor: " << initHonor << endl;
  cout << "Starting DEF  : " << initDefence << endl;  

  cout << RED << "====== !BLACK CARD! ======" << RST << endl;
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
  cout << BLU << "=======  PLAYER  =======" << RST << endl;
  cout << "User : " << userName << endl;
  cout << "Honor: " << honor << endl;
  cout << "Active Provinces: " << activeProvinces << endl;

  //probz shouldnt do that here // printHand();
  cout << MAG << "=====  HOLDINGS  =====" << RST << endl;
  printHoldings();
  cout << MAG << "===== !HOLDINGS! =====" << RST << endl;

  cout << MAG << "=====  ARMY  =====" << RST << endl;
  printArmy();
  cout << MAG << "===== !ARMY! =====" << RST << endl;

  cout << BLU << "======= !PLAYER! =======" << RST << endl;
}
/* ========================================================================= */

void Player::printHoldings() const
{
  strongHold->print();

  for (auto *i : *holdings) i->print();
}
/* ========================================================================= */

void Player::printArmy() const
{
  if (army->size() == 0) 
    cout << "No army!" << endl;
  else
    for (auto *i : *army) i->print();
}
/* ========================================================================= */

void Player::printAvailableArmy() const
{
  if (army->size() == 0) 
    cout << "No army!" << endl;
  else
    for (auto *i : *army)
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
    for (auto *i : *hand) i->print();
}

/* ========================================================================= */

void Player::printProvinces() const {
  for (auto *i : *provinces) i->print();
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
    return;
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
  for (auto *i : *players)
    i->printStatistics();

  cout << "========= !END OF GLOBAL STATS! =========" << endl;
}