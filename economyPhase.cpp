//======|| GAME :: ECONOMY PHASE ||======

#include <iostream>
#include <queue>
#include <vector>
#include <memory>
#include "baseClasses.h"

namespace {

  bool checkForFullChain (std::shared_ptr< CrystalMine > crM) {                                                // Check if 
    return (crM->getSubHolding() != nullptr                                                   // CrystalMine -> GoldMine exists
        && crM->getSubHolding()->getUpperHolding() == crM                                     // CrystalMine -> GoldMine -> CrystalMine exists
        && crM->getSubHolding()->getSubHolding() != nullptr                                   // CrystalMine -> GoldMine -> Mine exists
        && crM->getSubHolding()->getSubHolding()->getUpperHolding() == crM->getSubHolding()); // CrystalMine -> GoldMine -> Mine -> GoldMine exists
  }

  bool checkForFullChain (std::shared_ptr< Mine > M) {                                                         // Check if 
    return (M->getUpperHolding() != nullptr                                                   // Mine -> GoldMine exists
        && M->getUpperHolding()->getSubHolding() == M                                         // Mine -> GoldMine -> Mine exists
        && M->getUpperHolding()->getUpperHolding() != nullptr                                 // Mine -> GoldMine -> CrystalMine exists
        && M->getUpperHolding()->getUpperHolding()->getSubHolding() == M->getUpperHolding()); // Mine -> GoldMine -> CrystalMine -> GoldMine exists
  }

}  // Namespace End

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

void Personality::attachToPlayer (std::shared_ptr< Player > pl) {
  pl->getArmy()->push_back(std::make_shared< Personality >(*this));
}

void Holding::attachToPlayer (std::shared_ptr< Player > pl) {
  pl->getHoldings()->push_back(std::make_shared< Holding >(*this));  
}

void Mine::attachToPlayer(std::shared_ptr< Player > pl) {
  
  for (auto i : *(pl->getHoldings())) {
    
    if (i->getHoldingType() == GOLD_MINE) {
      if ((std::static_pointer_cast<GoldMine>(i))->getSubHolding() == nullptr) {

        upperHolding = std::static_pointer_cast<GoldMine>(i);
        (std::static_pointer_cast<GoldMine>(i))->setSubHolding(std::make_shared< Mine >(*this));

        if (checkForFullChain(std::make_shared< Mine >(*this)) == true) {
          upperHolding->getUpperHolding()->increaseHarvestValueBy(3*(upperHolding->getUpperHolding()->getHarvestValue()));
          i->increaseHarvestValueBy(2*(i->getHarvestValue()));
        }
        else {
          i->increaseHarvestValueBy(4);
        }
        harvestValue += 2;
        
        break;
      }
    }
  }
  pl->getHoldings()->push_back(std::make_shared< Mine >(*this));
}

void GoldMine::attachToPlayer(std::shared_ptr< Player > pl) {
  
  for (auto i : *(pl->getHoldings())) {  // Check for Mines
    if (i->getHoldingType() == MINE) {
      if ((std::static_pointer_cast<Mine>(i))->getUpperHolding() == nullptr) {
        subHolding = std::static_pointer_cast<Mine>(i);
        (std::static_pointer_cast<Mine>(i))->setUpperHolding(std::make_shared< GoldMine >(*this));
      
        harvestValue += 4;
        i->increaseHarvestValueBy(2);

        break;
      }
    }
  }
  for (auto i : *(pl->getHoldings())) {  // Check for Crystal Mines
    if (i->getHoldingType() == CRYSTAL_MINE) {
      if ((std::static_pointer_cast<CrystalMine>(i))->getSubHolding() == nullptr) {
        upperHolding = std::static_pointer_cast<CrystalMine>(i);
        (std::static_pointer_cast<CrystalMine>(i))->setSubHolding(std::make_shared< GoldMine >(*this));

        if (subHolding == nullptr) {        // If there's no link with a Mine
          harvestValue +=5;                 // Add the bonus
          i->increaseHarvestValueBy(i->getHarvestValue());
        }
        else {
          harvestValue += 2*harvestValue;
          i->increaseHarvestValueBy(3*(i->getHarvestValue()));
        }
        break;    
      }
    }
  }
  pl->getHoldings()->push_back(std::make_shared< GoldMine >(*this));
}

void CrystalMine::attachToPlayer(std::shared_ptr< Player > pl) {

  for (auto i : *(pl->getHoldings())) {
    
    if (i->getHoldingType() == GOLD_MINE) {
      if ((std::static_pointer_cast<GoldMine>(i))->getUpperHolding() == nullptr) {
        subHolding = std::static_pointer_cast<GoldMine>(i);
        (std::static_pointer_cast<GoldMine>(i))->setUpperHolding(std::make_shared< CrystalMine >(*this));

        if (checkForFullChain(std::make_shared< CrystalMine >(*this)) == true) {
          harvestValue += 3*harvestValue;
          i->increaseHarvestValueBy(2*(i->getHarvestValue()));
        }
        else {
          harvestValue += harvestValue;
          i->increaseHarvestValueBy(5);
        }
        break;
      }
    }
  }
  pl->getHoldings()->push_back(std::make_shared< CrystalMine >(*this));
}

void Game::economyPhase(std::shared_ptr<Player> pl) {

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
  for (auto i : *(pl->getProvinces())) {

    if (i->checkBroken() == false && i->getCard()->checkRevealed() == true) {
      
      i->print();
      std::cout << std::endl <<"Proceed to purchase ?" << std::endl << "> Your answer: " ;
      std::string answer;
      std::getline(std::cin, answer);
      std::cout << answer << std::endl;

      if (answer == "Y") {
        if (pl->makePurchase(i->getCard()->getCost()) == true) {
          std::cout << "Purchase Completed ! " << std::endl;
          i->getCard()->setTapped();  // TODO : nomizw einai peritto
          i->getCard()->attachToPlayer(pl);
          i->setCard( pl->drawBlackCard() );
        } 
        else std::cout << "You do not have enough money to buy this province . . ." << std::endl;
      }
    }
  }
  std::cout << "Economy Phase Ended !" << std::endl;
}