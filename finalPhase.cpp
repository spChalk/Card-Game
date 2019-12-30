//======|| GAME :: FINAL PHASE ||======
#include <iostream>
#include <vector>
#include "baseClasses.h"

static void discardSurplusFateCards (Player * pl , size_t numOfCards) {
  std::cout << "Player : " << pl->getUserName() << " has to discard "<< numOfCards <<" Fate Cards !" << std::endl;
  
    std::cout << "Type 'Y' (YES) or '<any other key>' (NO) after each card's \
    appearance, to discard it." << std::endl;

  for (auto * i : *(pl->getHand())) {
    
    if (numOfCards == 0) {
      std::cout << "Discarded Surplus Fate Cards !" << std::endl;
      return;
    } 

    i->print();
    std::cout << std::endl <<"Discard ? "<< std::endl << "> Your answer: " ;
    std::string answer;
    std::getline(std::cin, answer);
    std::cout << answer << std::endl;

    if (answer == "Y") { 
      pl->getHand()->pop_back();
      std::cout << "Cards remaining : " << numOfCards-- << std::endl;
    }
  }
}

void Game::finalPhase(Player * pl) {

    std::cout << "Final Phase Started !" << std::endl;

  if (pl->getHand()->size() > MAX_HAND_CARDS)
    discardSurplusFateCards(pl , pl->getHand()->size() - MAX_HAND_CARDS);

  // printGameStatistics
  pl->printHand();
  pl->printProvinces();
  // printArena
  pl->printHoldings();

  std::cout << "Final Phase Ended !" << std::endl;

}