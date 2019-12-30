//======|| EQUIPMENT PHASE IMPL ||======
// TODO 
#include <iostream>
#include <vector>
#include "baseClasses.h"


void Game::equipmentPhase (Player * pl) {
  std::cout << "Equipment Phase Started !" <<std::endl;

  // Print army
  std::cout << "Army : " << std::endl ;
  pl->printArmy();
  
  // Print hand 
  std::cout << "Hand : " << std::endl ;
  pl->printHand();

  std::cout << "Type 'Y' (YES) or '<any other key>' (NO) after each card's appearance." << std::endl;

  for (auto * pers : *(pl->getArmy())) {
    
    pers->print();
    std::cout << "Equip this Personality ?" << std::endl << "> Your answer : " ;
    std::string answer;
    std::getline(std::cin, answer);
    std::cout << answer << std::endl;

    if (answer == "Y") {
      
      for (auto * it : *(pl->getHand())) {
        // TODO
        // buy cards 
        // upgrade them 
      }


    }

  }


  std::cout << "Equipment Phase Ended !" <<std::endl;
}