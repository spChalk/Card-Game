//======|| GAME :: ECONOMY PHASE ||======
// TODO : Na kanw mia currentMoney ston Player pou na deixnei ka8e fora ta lefta tou
// etsi wste sto makePurchase na exw mono ena check anti gia to 1o parse
// TODO : sto economyPhase , an agorasw Holding na au3anw apeu8eias ta lefta tou Player
#include <iostream>
#include <queue>
#include <vector>
#include "baseClasses.h"

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

void Game::economyPhase(Player * pl) {

  std::cout << "Economy Phase Started !" << std::endl;
  // Reveal Provinces
  for (auto i = pl->getProvinces()->begin() ; i != pl->getProvinces()->end() ; i++) 
    if ((*i)->getCard()->checkRevealed() == false)
      (*i)->getCard()->setRevealed();
  // Print Provinces
  pl->printProvinces();
  // Buy Provinces
  for (auto i = pl->getProvinces()->begin() ;  i != pl->getProvinces()->end() ; i++) {

      if ((*i)->checkBroken() == false && (*i)->getCard()->checkTapped() == false)

        if (pl->makePurchase((*i)->getCard()->getCost()) == true) {
            
            (*i)->getCard()->attachToPlayer(pl);
            (*i)->setCard( pl->drawBlackCard() );
        }
  }
  
  std::cout << "Economy Phase Ended !" << std::endl;
}