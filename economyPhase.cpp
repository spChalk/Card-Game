//======|| GAME :: ECONOMY PHASE ||======

// TODO : Na kanw mia currentMoney ston Player pou na deixnei ka8e fora ta lefta tou
// etsi wste sto makePurchase na exw mono ena check anti gia to 1o parse

// TODO : sto economyPhase , an agorasw Holding na au3anw apeu8eias ta lefta tou Player

// TODO : na dw ti ginetai me ta Mine , Gold. .... . peri attachments & sub/upper holdings 
#include <iostream>
#include <queue>
#include <vector>
#include "baseClasses.h"

static size_t checkForFullChain (CrystalMine * crM) {                           // Check if 
  return (crM->getSubHolding() != nullptr                                       // CrystalMine -> GoldMine exists
      && crM->getSubHolding()->getUpperHolding() != nullptr                     // CrystalMine -> GoldMine -> CrystalMine exists
      && crM->getSubHolding()->getSubHolding() != nullptr                       // CrystalMine -> GoldMine -> Mine exists
      && crM->getSubHolding()->getSubHolding()->getUpperHolding() != nullptr)   // CrystalMine -> GoldMine -> Mine -> GoldMine exists
      ? 3*crM->getHarvestValue()                                                // If Fully Linked , return SUPER BONUS
      : crM->getharvestValue();                                                 // Else return standard Bonus
}

bool Player::makePurchase (size_t cost) {
  size_t tempCost = cost;
  
  // First , check if you can collect the required money from holdings
  // Do not tap anything
  for (auto it = holdings->begin() ; it != holdings->end() ; it++) { 
    if ((*it)->checkTapped() == false)  // If it is untapped
      tempCost -= (*it)->getCost();   // Subtract its cost 
    
    if (tempCost <= 0) break;         // We can proceed to the main part
  }
  
  if (tempCost > 0) return false;     // If the required cost is still positive , exit 
    
  // Main part 
  for (auto it = holdings->begin() ; it != holdings->end() ; it++) {

    if ((*it)->checkTapped() == false) {
      cost -= (*it)->getCost();
      (*it)->setTapped();            
    }
            
    if (cost <= 0) return true;
  }
}

void Personality::attachToPlayer (Player * pl) {
  pl->getArmy()->push_back(this);
}

void Holding::attachToPlayer (Player * pl) {
  pl->getHoldings()->push_back(this);  
}

void Mine::attachToPlayer(Player * pl) {
  
  for (auto * i : *(pl->getHoldings())) {
    
    if (i->getName() == "GOLD_MINE") {
      
      upperHolding = i;
      harvestValue +=2;
      break;
    }
  }
  pl->getHoldings()->push_back(this);
}

void GoldMine::attachToPlayer(Player * pl) {
  
  for (auto * i : *(pl->getHoldings())) {  // Check for Mines
    if (i->getName() == "MINE") {
      
      subHolding = i;
      harvestValue +=4;
      break;
    }
  }
  for (auto * i : *(pl->getHoldings())) {  // Check for Crystal Mines
    if (i->getName() == "CRYSTAL_MINE") {
      
      upperHolding = i;

      if (subHolding == nullptr)  // If there's no link with a Mine
        harvestValue +=5;         // Add the bonus
      else {
        harvestValue -=4;         // If there's also a link with a Mine
        harvestValue += 2*harvestValue ;  // Double the INITIAL harvest Value
      }
      
      break;
    }
  }
  pl->getHoldings()->push_back(this);
}

void CrystalMine::attachToPlayer(Player * pl) {

  for (auto * i : *(pl->getHoldings())) {
    
    if (i->getName() == "GOLD_MINE") {
      
      subHolding = i;
      harvestValue += checkForFullChain(this);
      break;
    }
  }
  pl->getHoldings()->push_back(this);
}

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
          i->getCard()->attachToPlayer(pl);
          i->setCard( pl->drawBlackCard() );
        } 
        else std::cout << "You do not have enough money to buy this province . . ." << std::endl;
      }
    }
  }
  std::cout << "Economy Phase Ended !" << std::endl;
}