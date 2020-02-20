/* prints.cpp */

#include <iostream>

#include "basicHeader.hpp"

using std::cout;
using std::endl;

/* ========================================================================= */

/*  Write formatted output to stdout (args : colour & style) */
void printF (const std::string & s , bool printEndl ,const uint16_t & colour , const uint16_t & format ) {
  std::cout << "\x1B[" << format << ";" << colour << "m" << s << "\x1B[0m" << (printEndl ? "\n" : "");
}

/* ========================================================================= */

namespace
{
  /* Booleans for Mine Printing */
  bool printUpper = true;
  bool printSub = true;

  /* Function for space printing */
  void printSpaces (uint16_t spaces) {
    for (uint16_t i = 0 ; i < spaces ; i++)
      cout << " ";
  }

  /* Function for printing card's text */
  void printCardText (const std::string & ct) {
    uint32_t counter = 0;
    for (auto c : ct) {
      cout << c;
      counter++;
      if (counter == 15) { 
        cout <<" ";
        printF ("|" , 1 , GRN , BOLD); 
        printF ("|            " , 0 , GRN , BOLD); 
        counter = 0;
      }
    }
    printSpaces(16 - counter);
    printF ("|" , 1 , GRN , BOLD); 
  }
}

void Card::print() const
{
  printF("| Name: " , 0 , MAG , BOLD); cout << name ;
  printSpaces(21 - name.length()); /* Print CardSize - NameSize spaces */
  printF("|" , 1 , MAG , BOLD);
  printF("| Cost:   " , 0 , MAG , BOLD); cout << cost;
  if (cost < 10) cout << "                  ";
  else cout << "                 ";
  printF("|" , 1 , MAG , BOLD);
  printF("| Tapped: " , 0 , MAG , BOLD); 
  cout << (isTapped ? "YES                " : "NO                 ");
  printF ("|" , 1 , MAG , BOLD);   
}
/* ========================================================================= */

void GreenCard::print() const
{
  printF ("/=======  GREEN CARD  =======\\" , 1 , GRN );
  printF("| Name: " , 0 , MAG , BOLD); cout << name ;
  printSpaces(21 - name.length()); /* Print CardSize - NameSize spaces */
  printF("|" , 1 , MAG , BOLD);
  printF("| Cost:   " , 0 , MAG , BOLD); cout << cost ;
  printSpaces(18);
  printF("|" , 1 , MAG , BOLD);
  printF ("| ATK Bonus: " , 0 , GRN , BOLD); cout << attackBonus;
  printSpaces(15);
  printF("|" , 1 , GRN , BOLD);
  printF ("| DEF Bonus: " , 0 , GRN , BOLD); cout << defenceBonus;
  printSpaces(15);
  printF("|" , 1 , GRN , BOLD);
  printF ("| Min Honor: " , 0 , GRN , BOLD); cout << minHonor;
  printSpaces(15);
  printF("|" , 1 , GRN , BOLD);
  printF ("| Effect Bonus: " , 0 , GRN , BOLD); cout << effectBonus;
  printSpaces(12);
  printF("|" , 1 , GRN , BOLD);
  printF ("| Effect Cost: " , 0 , GRN , BOLD); cout <<effectCost;
  printSpaces(13);
  printF("|" , 1 , GRN , BOLD);
}
/* ========================================================================= */

void Follower::print() const
{
  this->GreenCard::print();
  printF ("| Card Text: " , 0 , GRN , BOLD); 
  
  printCardText(cardText);
  
  printF ("\\____________________________/" , 1 , GRN );
  cout << endl;
}
/* ========================================================================= */

void Item::print() const
{
  this->GreenCard::print();
  printF("| Durability: " , 0 , GRN , BOLD); cout << durability;
  printSpaces(14);
  printF("|" , 1 , GRN , BOLD);
  printF ("| Card Text: " , 0 , GRN , BOLD); 
  
  printCardText(cardText);
  
  printF ("\\____________________________/" , 1 , GRN );
  cout << endl;
}
/* ========================================================================= */

void BlackCard::print() const
{
  printF ("/=======  BLACK CARD  =======\\" , 1 , RED);
  this->Card::print();

  printF ("| Revealed: " , 0 , RED , BOLD); 
  cout << (isRevealed ? "YES              " : "NO             ");
  printF ("|" , 1 , RED , BOLD); 
}
/* ========================================================================= */

void Personality::print() const
{
  this->BlackCard::print();

  printF ("| ATK:   " , 0 , RED , BOLD); cout << attack;
  if (attack < 10) printSpaces(19); 
  else printSpaces(18);
  printF ("|" , 1 , RED , BOLD);
  printF ("| DEF:   ", 0 , RED , BOLD); cout << defence;
  if (defence < 10) printSpaces(19); 
  else printSpaces(18);
  printF ("|", 1 , RED , BOLD);
  printF ("| Honor: " , 0 , RED , BOLD); cout << honor;
  if (honor < 10) printSpaces(19); 
  else printSpaces(18);
  printF ("|" , 1 , RED , BOLD);

  printF ("|" , 0 , RED , BOLD);
  printF ("-------  FOLLOWERS  --------" , 0 , YEL);
  printF ("|" , 1 , RED , BOLD);
  for (auto i : *followers)
    i->print();
  printF ("|" , 0 , RED , BOLD);
  printF ("------- !FOLLOWERS! --------" , 0 , YEL);
  printF ("|" , 1 , RED , BOLD);
  printF ("|" , 0 , RED , BOLD);
  printF ("---------  ITEMS  ----------" , 0 , YEL);
  printF ("|" , 1 , RED , BOLD);
  for (auto i : *items)
    i->print();
  printF ("|" , 0 , RED , BOLD);
  printF ("--------- !ITEMS! ----------" , 0 , YEL);
  printF ("|" , 1 , RED , BOLD);
  printF ("\\____________________________/" , 1 , RED); 
  cout << endl;
}

/* ========================================================================= */

void Holding::print() const
{
  this->BlackCard::print();

  printF("| Harvest value: " , 0 , RED , BOLD); cout << harvestValue <<"           ";
  printF("|" , 1 , RED , BOLD);

  printF ("\\____________________________/" , 1 , RED);
  cout << endl; 
}

/* ========================================================================= */

void Mine::print() const
{
  this->BlackCard::print();
  printF("| Harvest value: " , 0 , RED , BOLD); cout << harvestValue;
  printSpaces(11);
  printF("|" , 1 , RED , BOLD);

  if (upperHolding && printUpper)
  {
    printSub = false;
    printF ("|--  UpperHolding  --" , 1 , CYN); cout << endl;
    upperHolding->print();
    printF ("|-- !UpperHolding! --" , 0 , CYN); cout << endl;
    printSub = true;
  }

  printF ("\\____________________________/" , 1 , RED);
  cout << endl;
}

/* ========================================================================= */

void GoldMine::print() const
{
  this->BlackCard::print();
  printF("| Harvest value: " , 0 , RED , BOLD); cout << harvestValue;
  printSpaces(11);
  printF("|" , 1 , RED , BOLD);

  if (upperHolding && printUpper)
  {
    printSub = false;
    printF ("|--  UpperHolding  --" , 1 , CYN);
    upperHolding->print();
    printF ("|-- !UpperHolding! --" , 0 , CYN);
    printSub = true;
  }

  if (subHolding && printSub)
  {
    printUpper = false;
    printF ("|--  subHolding  --\n" , 1 , CYN);
    subHolding->print();
    printF ("|-- !subHolding! --\n" , 0 , CYN);
    printUpper = true;
  }

  printF ("\\____________________________/" , 1 , RED);
  cout << endl;
}
/* ========================================================================= */

void CrystalMine::print() const
{
  this->BlackCard::print();
  printF("| Harvest value: " , 0 , RED , BOLD); cout << harvestValue;
  printSpaces(11);
  printF("|" , 1 , RED , BOLD);

  if (subHolding)
  {
    printUpper = false;
    printF ("|--  subHolding  --" , 1 , CYN);
    subHolding->print();
    printF ("|-- !subHolding! --" , 1 , CYN);
    printUpper = true;
  }

  printF ("\\____________________________/" , 1 , RED);
  cout << endl;
}
/* ========================================================================= */

void StrongHold::print() const
{
  this->BlackCard::print();
  printF("| Harvest value: " , 0 , RED , BOLD); cout << harvestValue;
  printSpaces(11);
  printF("|" , 1 , RED , BOLD);

  printF("| Starting Honor: " , 0 , RED , BOLD); cout << initHonor;
  printSpaces(10);
  printF("|" , 1 , RED , BOLD);
  printF("| Starting DEF  : " , 0 , RED , BOLD); cout << initDefence;
  printSpaces(10);  
  printF("|" , 1 , RED , BOLD);

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
  cout << getUserName() << endl << endl;
  printF("/=======||   BEGINNING OF STATS   ||=======\\" , 1 , MAG , BOLD);
  cout << endl; printF("Honor: " , 0 , YEL , UNDR); 
  cout << honor << endl;
  cout << endl; printF("Active provinces: " , 0 , YEL , UNDR);
  cout << activeProvinces << endl;

  if (activeProvinces == 0)
  {
    printF("\\=======||  END OF STATS  ||=======/" , 1 , MAG , BOLD);
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
  printF("\\=======||  END OF STATS  ||=======/" , 1 , MAG ,BOLD);
}

/* ========================================================================= */

void Game::printGameStatistics() const
{
  static uint32_t roundCnt = 0;

  printF ("Printing global game statistics!" , 1 , MAG , UNDR);
  printF("=========||  BEGINNING OF GLOBAL STATS  ||=========" , 1 , MAG , FILL);
  printF("Current round: " , 0 , YEL );
  cout << ++roundCnt << endl;

  for (auto i : *players)
    i->printStatistics();

  printF("=========||  END OF GLOBAL STATS  ||=========" , 1 , MAG , FILL);
}
/* ========================================================================= */