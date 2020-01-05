
#include "baseClasses.h"
#include "blackCards.h"

/* ========================================================================= */

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

/* ========================================================================= */
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
/* ========================================================================= */

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
/* ========================================================================= */

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
/* ========================================================================= */
