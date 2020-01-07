
#include "basicHeader.hpp"
#include "blackCards.hpp"

/* ========================================================================= */

namespace {  /* namespace start */

  bool checkForFullChain (CrystalMinePtr crM) {                                               /* Check if                                                        */
    return (crM->getSubHolding() != nullptr                                                   /* CrystalMine -> GoldMine exists                                  */
        && crM->getSubHolding()->getUpperHolding() == crM                                     /* CrystalMine -> GoldMine -> CrystalMine == this                  */
        && crM->getSubHolding()->getSubHolding() != nullptr                                   /* CrystalMine -> GoldMine -> Mine exists                          */
        && crM->getSubHolding()->getSubHolding()->getUpperHolding() == crM->getSubHolding()); /* CrystalMine -> GoldMine -> Mine -> GoldMine == this -> GoldMine */
  }

  bool checkForFullChain (MinePtr M) {                                                        /* Check if                                                        */                
    return (M->getUpperHolding() != nullptr                                                   /* Mine -> GoldMine exists                                         */                  
        && M->getUpperHolding()->getSubHolding() == M                                         /* Mine -> GoldMine -> Mine == this                                */              
        && M->getUpperHolding()->getUpperHolding() != nullptr                                 /* Mine -> GoldMine -> CrystalMine exists                          */          
        && M->getUpperHolding()->getUpperHolding()->getSubHolding() == M->getUpperHolding()); /* Mine -> GoldMine -> CrystalMine -> GoldMine == this -> GoldMine */            
  }

}  /* namespace end */

/* ========================================================================= */

Mine::Mine(const std::string & name , const uint16_t & cost , const uint16_t & harvestValue) 
: Holding(name , cost , harvestValue , MINE), 
  upperHolding(nullptr)
  {} 

void Mine::attachToPlayer(PlayerPtr pl) {
  
  for (auto i : *(pl->getHoldings())) {  /* Search in Player's Holdings */
    
    if (i->getHoldingType() == GOLD_MINE) {  /* If a Gold Mine is found */
      if ((std::static_pointer_cast<GoldMine>(i))->getSubHolding() == nullptr) {  /* If the Gold Mine is not 
                                                                                    connected to a Mine */
        upperHolding = std::static_pointer_cast<GoldMine>(i);           /* Link this Mine with the Gold Mine */
        (std::static_pointer_cast<GoldMine>(i))->setSubHolding(std::make_shared< Mine >(*this));

        if (checkForFullChain(std::make_shared< Mine >(*this)) == true) {  /* Check for full linkage between the Mines */
          /* Add Bonuses */
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
  pl->getHoldings()->push_back(std::make_shared< Mine >(*this));  /* Attach this Mine to Player */
}

/* ========================================================================= */

GoldMine::GoldMine(const std::string & name , const uint16_t & cost , const uint16_t & harvestValue)
: Holding(name , cost , harvestValue , GOLD_MINE), 
  upperHolding(nullptr),
  subHolding(nullptr)
  {} 

void GoldMine::attachToPlayer(PlayerPtr pl) {
  
  for (auto i : *(pl->getHoldings())) {  

    if (i->getHoldingType() == MINE) {  /* If a Mine is found */
      if ((std::static_pointer_cast<Mine>(i))->getUpperHolding() == nullptr) {  /* If the Mine is not 
                                                                                    connected to a Gold Mine */
        subHolding = std::static_pointer_cast<Mine>(i);                 /* Link this Gold Mine with the Mine */
        (std::static_pointer_cast<Mine>(i))->setUpperHolding(std::make_shared< GoldMine >(*this));
        /* Add Bonuses */
        harvestValue += 4;
        i->increaseHarvestValueBy(2);

        break;
      }
    }
  }
  for (auto i : *(pl->getHoldings())) {  /* Then , check for Crystal Mines */

    if (i->getHoldingType() == CRYSTAL_MINE) {
      if ((std::static_pointer_cast<CrystalMine>(i))->getSubHolding() == nullptr) {

        upperHolding = std::static_pointer_cast<CrystalMine>(i);
        (std::static_pointer_cast<CrystalMine>(i))->setSubHolding(std::make_shared< GoldMine >(*this));

        if (subHolding == nullptr) {        /* If this Gold Mine has no link with a Mine */
          harvestValue +=5;                 /* Add the bonuses */
          i->increaseHarvestValueBy(i->getHarvestValue());
        }
        else {                              /* Else , a full linkage is formed */
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

CrystalMine::CrystalMine(const std::string & name , const uint16_t & cost , const uint16_t & harvestValue) 
: Holding(name , cost , harvestValue , CRYSTAL_MINE), 
  subHolding(nullptr)
  {} 


void CrystalMine::attachToPlayer(PlayerPtr pl) {

  for (auto i : *(pl->getHoldings())) {
    
    if (i->getHoldingType() == GOLD_MINE) {

      if ((std::static_pointer_cast<GoldMine>(i))->getUpperHolding() == nullptr) {
        subHolding = std::static_pointer_cast<GoldMine>(i);
        (std::static_pointer_cast<GoldMine>(i))->setUpperHolding(std::make_shared< CrystalMine >(*this));

        /* If there's a link with a Gold Mine , check for full linkage */
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

/* ===========================|| E N D  O F  F I L E ||=========================== */