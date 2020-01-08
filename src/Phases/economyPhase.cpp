/* economyPhase.cpp */ //COMMENTS = OK

#include <iostream>
#include <string>

#include "basicHeader.hpp"

using std::cout;
using std::endl;

/* ========================================================================= */
void Game::economyPhase(PlayerPtr pl) {

  cout << "Economy Phase Started !" << endl;
  // Reveal Provinces ** if needed **
  
  cout << "Player : " << pl->getUserName() 
       << " can now buy Provinces!" << endl;

  cout << "Printing Provinces : " << endl;
  pl->printProvinces();
  
  cout << "Type 'Y' (YES) or '<any other key>' (NO) after each card's \
appearance, to proceed to purchase. " << endl;

  /* Buy provinces */
  for (auto i : *(pl->getProvinces()))     /* For every province */
  {
    if (i->checkBroken() == false && i->getCard()->checkRevealed() == true)
    {
      i->print();                     /* If it is revealed and not broken */
      cout << "Current balance:" << pl->getCurrMoney() << endl;
      cout << "\nProceed to purchase ?\n> Your answer: " ;
      std::string answer;
      std::getline(std::cin, answer);
      cout << endl;

      if (answer == "Y")      /* Attempt to make the purchase */
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
  cout << "Economy Phase Ended !" << endl;
}
/* ========================================================================= */