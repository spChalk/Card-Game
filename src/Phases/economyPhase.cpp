/* economyPhase.cpp */ //COMMENTS = OK

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
  
  cout << "Player : " << pl->getUserName() 
       << " can now buy Provinces!" << endl;

  cout << "Printing " << pl->getUserName() << "'s Provinces : " << endl;
  pl->printProvinces();
  
  cout << "Type 'Y' (YES) or '<any other key>' (NO) after each card's \
appearance, to proceed to purchase. " << endl;

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
      else  cout << pl->getUserName() <<"'s Current balance: " << pl->getCurrMoney() << endl;

      i->print();                     /* If it is revealed and not broken */
      cout << endl << pl->getUserName() <<" , do you want to proceed to purchase ?\n> Your answer: " ;
      std::string answer;
      std::getline(std::cin, answer);
      cout << endl;

      if ((answer == "Y")||(answer == "y"))      /* Attempt to make the purchase */
      { 
        if (pl->makePurchase(i->getCard()->getCost()) == true)
        {
          cout << "Purchase Completed ! " << endl;
         
          i->getCard()->setTapped();      /* Can't be used for this round */
          i->getCard()->attachToPlayer(pl);

          if (pl->getDynastyDeck()->empty() == false)
            i->setCard( pl->drawBlackCard() );  /* Replace the card bought */
          else
            cout << "Dynasty deck is empty! No more Black Cards for player \'"
                 << pl->getUserName() << "\' !" << endl;
        } 
        else 
          cout << "You don't have enough money to buy this province!" << endl;
      }
    }
  }
  printF ("Economy Phase Ended !" , 1 , YEL , FILL); 
}
/* ========================================================================= */