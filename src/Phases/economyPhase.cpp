//======|| GAME :: ECONOMY PHASE ||======

#include <iostream>
#include <string>

#include "basicHeader.hpp"

using std::cout;
using std::endl;

void Game::economyPhase(PlayerPtr pl) {

  cout << "Economy Phase Started !" << endl;
  // Reveal Provinces ** if needed **
  
  cout << "Player : " << pl->getUserName() 
       << " has the option to buy Provinces." << endl ;

  // Print Provinces
  cout << "All Provinces : " << endl;
  pl->printProvinces();
  
  cout << "Type 'Y' (YES) or '<any other key>' (NO) after each card's \
  appearance, to proceed to purchase. " << endl;

  // Buy Provinces
  for (auto i : *(pl->getProvinces())) {

    if (i->checkBroken() == false && i->getCard()->checkRevealed() == true) {
      
      i->print();
      cout << endl <<"Proceed to purchase ?" << endl << "> Your answer: " ;
      std::string answer;
      std::getline(std::cin, answer);
      cout << answer << endl;

      if (answer == "Y") {
        if (pl->makePurchase(i->getCard()->getCost()) == true) {
          cout << "Purchase Completed ! " << endl;
          i->getCard()->setTapped();  // TODO : nomizw einai peritto
          i->getCard()->attachToPlayer(pl);

          if (pl->getDynastyDeck()->empty() == false)
            i->setCard( pl->drawBlackCard() );  /* Replace the card that was bought */
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