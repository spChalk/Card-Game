/* economyPhase.cpp */

#include <iostream>
#include <string>

#include "basicHeader.hpp"

using std::cout;
using std::endl;

/* ========================================================================= */
void Game::economyPhase(PlayerPtr pl) {

  printF ("Economy Phase Started !" , 1 , YEL , FILL);
  printF ("Press ENTER to continue . . ." , 1);
  std::cin.clear();
  std::cin.sync();
  std::cin.get();
  
  printF ("Player : "  , 0 , MAG , BOLD);
  cout << pl->getUserName(); 
  printF (" can now buy Provinces!" , 1 , MAG , BOLD);

  printF ("Printing " , 0 , MAG);
  cout << pl->getUserName();
  printF ("'s Provinces : " , 1 , MAG);
  pl->printProvinces();
  
  printF ("Type 'Y' (YES) or '<any other key>' (NO) after each card's \
appearance, to proceed to purchase. " , 1 , MAG , BOLD);

  /* Buy provinces */
  for (auto i : *(pl->getProvinces()))     /* For every province */
  {
    if (i->checkBroken() == false && i->getCard()->checkRevealed() == true)
    {
      if (pl->getCurrMoney() == 0) {
        cout << "No money left !" << endl;
        return;
      }
      else if (pl->getCurrMoney() < i->getCard()->getCost()) 
      continue; 
      else  {
        cout << pl->getUserName();
        printF ("'s Current balance: " , 0 , YEL , BOLD);
        cout << pl->getCurrMoney() << endl;
      }

      i->print();                     /* If it is revealed and not broken */
      cout << endl << pl->getUserName();
      printF (" , do you want to proceed to purchase ?\n> Your answer: " , 0 , YEL , BOLD);
      std::string answer;
      std::getline(std::cin, answer);
      cout << endl;

      if ((answer == "Y")||(answer == "y"))      /* Attempt to make the purchase */
      { 
        if (pl->makePurchase(i->getCard()->getCost()) == true)
        {
          printF ("Purchase Completed ! " , 1 , YEL , BOLD);
         
          i->getCard()->setTapped();      /* Can't be used for this round */
          i->getCard()->attachToPlayer(pl);

          if (pl->getDynastyDeck()->empty() == false)
            i->setCard( pl->drawBlackCard() );  /* Replace the card bought */
          else {
            printF ("Dynasty deck is empty! No more Black Cards for player \'" , 0 , MAG , BOLD);
            cout << pl->getUserName();
            printF ("\' !" , 1 , MAG , BOLD);
          }
        } 
        else 
          printF ("You don't have enough money to buy this province!" , 1 , MAG , BOLD);
      }
    }
  }
  printF ("Economy Phase Ended !" , 1 , YEL , FILL); 
}
/* ========================================================================= */