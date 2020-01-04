//======|| GAME :: ECONOMY PHASE ||======

#include <iostream>
#include <queue>
// #include <vector>
#include <memory>
#include "baseClasses.h"

namespace {

  bool checkForFullChain (CrystalMinePtr crM) {                                               // Check if 
    return (crM->getSubHolding() != nullptr                                                   // CrystalMine -> GoldMine exists
        && crM->getSubHolding()->getUpperHolding() == crM                                     // CrystalMine -> GoldMine -> CrystalMine exists
        && crM->getSubHolding()->getSubHolding() != nullptr                                   // CrystalMine -> GoldMine -> Mine exists
        && crM->getSubHolding()->getSubHolding()->getUpperHolding() == crM->getSubHolding()); // CrystalMine -> GoldMine -> Mine -> GoldMine exists
  }

  bool checkForFullChain (MinePtr M) {                                                         // Check if 
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

void Personality::attachToPlayer (PlayerPtr pl) {
  pl->getArmy()->push_back(std::make_shared< Personality >(*this));
}

void Holding::attachToPlayer (PlayerPtr pl) {
  pl->getHoldings()->push_back(std::make_shared< Holding >(*this));  
}

void Mine::attachToPlayer(PlayerPtr pl) {
  
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

void GoldMine::attachToPlayer(PlayerPtr pl) {
  
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

void CrystalMine::attachToPlayer(PlayerPtr pl) {

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

using std::cout;
using std::endl;

void Game::economyPhase(std::shared_ptr<Player> pl) {

  cout << "Economy Phase Started !" << endl;
  // Reveal Provinces ** if needed **

  /* for (auto i = pl->getProvinces()->begin() ; i != pl->getProvinces()->end() ; i++) 
    if ((*i)->checkBroken == false && (*i)->getCard()->checkRevealed() == false)
      (*i)->getCard()->setRevealed(); */
  
  cout << "Player : " << pl->getUserName() << " has the option to buy Provinces." << endl ;

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
          i->setCard( pl->drawBlackCard() );
        } 
        else cout << "You do not have enough money to buy this province . . ." << endl;
      }
    }
  }
  cout << "Economy Phase Ended !" << endl;
}