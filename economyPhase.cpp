//======|| GAME :: ECONOMY PHASE ||======

#include <iostream>
#include <queue>
#include <vector>
#include "baseClasses.h"

namespace {

  size_t checkForFullChain (CrystalMine * crM) {                                  // Check if 
    return (crM->getSubHolding() != nullptr                                       // CrystalMine -> GoldMine exists
        && crM->getSubHolding()->getUpperHolding() != nullptr                     // CrystalMine -> GoldMine -> CrystalMine exists
        && crM->getSubHolding()->getSubHolding() != nullptr                       // CrystalMine -> GoldMine -> Mine exists
        && crM->getSubHolding()->getSubHolding()->getUpperHolding() != nullptr)   // CrystalMine -> GoldMine -> Mine -> GoldMine exists
        ? 3*crM->getHarvestValue()                                                // If Fully Linked , return SUPER BONUS
        : crM->getHarvestValue();                                                 // Else return standard Bonus
  }

  size_t checkForFullChain (Mine * M) {                                           // Check if 
    return (M->getUpperHolding() != nullptr                                       // Mine -> GoldMine exists
        && M->getUpperHolding()->getSubHolding() != nullptr                       // Mine -> GoldMine -> Mine exists
        && M->getUpperHolding()->getUpperHolding() != nullptr                     // Mine -> GoldMine -> CrystalMine exists
        && M->getUpperHolding()->getUpperHolding()->getSubHolding() != nullptr)   // Mine -> GoldMine -> CrystalMine -> GoldMine exists
        ? 3*M->getHarvestValue()                                                  // If Fully Linked , return SUPER BONUS
        : 2;                                                                      // Else return standard Bonus
  }

  size_t checkForFullChain (GoldMine * glM) {                                     // Check if 
    return (glM->getSubHolding() != nullptr                                       // GoldMine -> Mine exists
        && glM->getSubHolding()->getUpperHolding() != nullptr                     // GoldMine -> Mine -> GoldMine exists
        && glM->getUpperHolding() != nullptr                                      // GoldMine -> CrystalMine exists
        && glM->getUpperHolding()->getSubHolding() != nullptr)                    // GoldMine -> CrystalMine -> GoldMine exists
        ? 3*glM->getHarvestValue()                                                // If Fully Linked , return SUPER BONUS
        : 0;                                                                      // Else return nothing
  }

}

bool Player::makePurchase (size_t cost) {
  
  if (getCurrMoney() < cost)
    return false;     // If the required cost is more than player's budget , exit 
    
  // Main part
  if (getStrongHold()->checkTapped() == false)
    cost -= getStrongHold()->getHarvestValue();

  for (auto it = holdings->begin() ; cost > 0 && it != holdings->end() ; it++) {

    if ((*it)->checkTapped() == false) {
      cost -= (*it)->getHarvestValue();
      (*it)->setTapped();            
    }
  }
  return true;
}

void Personality::attachToPlayer (Player * pl) {
  pl->getArmy()->push_back(this);
}

void Holding::attachToPlayer (Player * pl) {
  pl->getHoldings()->push_back(this);  
}

// void Mine::attachToPlayer(Player * pl) {
  
//   for (auto * i : *(pl->getHoldings())) {
    
//     if (i->getName() == "GOLD_MINE") {
      
//       upperHolding = (GoldMine *)i;
//       ((GoldMine *)i)->setSubHolding(this);

//       harvestValue += checkForFullChain(this);
//       break;
//     }
//   }
//   pl->getHoldings()->push_back(this);
// }

// void GoldMine::attachToPlayer(Player * pl) {
  
//   for (auto * i : *(pl->getHoldings())) {  // Check for Mines
//     if (i->getName() == "MINE") {
      
//       subHolding = (Mine *)i;
//       ((Mine *)i)->setUpperHolding(this);

//       harvestValue +=4 ;
//       break;
//     }
//   }
//   for (auto * i : *(pl->getHoldings())) {  // Check for Crystal Mines
//     if (i->getName() == "CRYSTAL_MINE") {
      
//       upperHolding = (CrystalMine *)i;
//       ((CrystalMine *)i)->setSubHolding(this);

//       if (subHolding == nullptr)  // If there's no link with a Mine
//         harvestValue +=5;         // Add the bonus
//       else {
//         size_t temp = checkForFullChain(this);
//         harvestValue -=4;         // If there's also a link with a Mine
        
//         (temp == 0) ?      
//         harvestValue += 2*harvestValue :  // Double the INITIAL harvest Value
//         harvestValue += temp;
        
//       }
      
//       break;
//     }
//   }
//   pl->getHoldings()->push_back(this);
// }

// void CrystalMine::attachToPlayer(Player * pl) {

//   for (auto * i : *(pl->getHoldings())) {
    
//     if (i->getName() == "GOLD_MINE") {
      
//       subHolding = (GoldMine *)i;
//       ((GoldMine *)i)->setUpperHolding(this);

//       harvestValue += checkForFullChain(this);
//       break;
//     }
//   }
//   pl->getHoldings()->push_back(this);
// }

void Game::economyPhase(Player * pl) {

  std::cout << "Economy Phase Started !" << std::endl;
  // Reveal Provinces ** if needed **

  /* for (auto i = pl->getProvinces()->begin() ; i != pl->getProvinces()->end() ; i++) 
    if ((*i)->checkBroken == false && (*i)->getCard()->checkRevealed() == false)
      (*i)->getCard()->setRevealed(); */
  
  std::cout << "Player : " << pl->getUserName() << " has the option to buy Provinces." << std::endl ;

  // Print Provinces
  std::cout << "All Provinces : " << std::endl;
  pl->printProvinces();
  
  std::cout << "Type 'Y' (YES) or '<any other key>' (NO) after each card's \
  appearance, to proceed to purchase. " << std::endl;

  // Buy Provinces
  for (auto * i : *(pl->getProvinces())) {

    if (i->checkBroken() == false && i->getCard()->checkRevealed() == true) {
      
      i->print();
      std::cout << std::endl <<"Proceed to purchase ?" << std::endl << "> Your answer: " ;
      std::string answer;
      std::getline(std::cin, answer);
      std::cout << answer << std::endl;

      if (answer == "Y") {
        if (pl->makePurchase(i->getCard()->getCost()) == true) {
          std::cout << "Purchase Completed ! " << std::endl;
          i->getCard()->setTapped();
          i->getCard()->attachToPlayer(pl);
          i->setCard( pl->drawBlackCard() );
        } 
        else std::cout << "You do not have enough money to buy this province . . ." << std::endl;
      }
    }
  }
  std::cout << "Economy Phase Ended !" << std::endl;
}