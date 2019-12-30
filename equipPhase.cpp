//======|| EQUIPMENT PHASE IMPL ||======

// TODO : Na valw oles tis proupo8eseis agoras kartas 
// TODO : Upgrade Cards

#include <iostream>
#include <vector>
#include "baseClasses.h"

void Follower::attachToPersonality (Personality * pers) {
  pers->getFollowers()->push_back(this);
}

void Item::attachToPersonality (Personality * pers) {
  pers->getItems()->push_back(this);
}

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
    if (pers->checkIfDead() == false) {

      pers->print();
      std::cout << "Equip this Personality ?" << std::endl << "> Your answer : " ;
      std::string answer;
      std::getline(std::cin, answer);
      std::cout << answer << std::endl;

      if (answer == "Y") {
        std::cout << "Cards in Hand :" << std::endl;
        for (auto * it : *(pl->getHand())) {
        
          it->print();
          std::cout << std::endl <<"Proceed to purchase ?" << std::endl << "> Your answer: " ;
          std::getline(std::cin , answer);
          std::cout << answer << std::endl;

          if (answer == "Y") {
            if (pl->makePurchase(it->getCost()) == true && /*minHonor*/ && /* < MAX_CARDS_PER_PERS */) {
              std::cout << "Purchase Completed ! " << std::endl;
              it->attachToPersonality(pers);
    
              std::cout << std::endl <<"Do you also want to upgrade this card ?" << std::endl << "> Your answer: " ;
              std::getline(std::cin , answer);
              std::cout << answer << std::endl;

              if (answer == "Y") {
                //TODO : upgrade card
              }

              
            } else  std::cout << "You do not have enough money for purchase . . ." << std::endl;
          }  
        }


      }
    }
  }



  std::cout << "Equipment Phase Ended !" <<std::endl;
}