#include "basicHeader.hpp"
#include "player.hpp"

/* ========================================================================= */

Province::Province(BlackCardPtr blackCard)
: isBroken(false), 
  card(blackCard)
  {}

/* ========================================================================= */

Player::Player(const std::string & userName )
: userName(userName) , 
  strongHold(nullptr),       
  honor(0), 
  activeProvinces(0), 
  fateDeck(std::make_shared < std::deque<std::shared_ptr <GreenCard > > >()) , 
  dynastyDeck(std::make_shared< std::deque<std::shared_ptr <BlackCard > > >()) , 
  hand(std::make_shared< std::list<std::shared_ptr <GreenCard > > >()) , 
  army(std::make_shared< std::list<std::shared_ptr <Personality > > >()) , 
  holdings(std::make_shared< std::list<std::shared_ptr <Holding > > >()) , 
  provinces(std::make_shared< std::list<std::shared_ptr <Province > > >())
  {}

/* ========================================================================= */
uint16_t Player::getCurrMoney() const
{
  HoldingListPtr holdings = this->getHoldings();  /* Check player's holdings */

  uint16_t total = 0;

  if (this->getStrongHold()->checkTapped() == false)  /* Get StrongHold's Value */
    total += this->getStrongHold()->getHarvestValue();

  for (auto i : *holdings)                            /* Gather the money from all the untapped holdings */    
    if (i->checkTapped() == false) total += i->getHarvestValue();

  return total;
}

/* ========================================================================= */

bool Player::makePurchase (int32_t cost) {
  
  if (cost == 0) return true;

  if (getCurrMoney() < cost)
    return false;      /* If the required cost is more than player's budget , exit */
    
  // Main part
  if (getStrongHold()->checkTapped() == false)
  {
    getStrongHold()->setTapped();
    cost -= getStrongHold()->getHarvestValue();
  }

  for (auto it = holdings->begin() ; cost > 0 && it != holdings->end() ; it++) {

    if ((*it)->checkTapped() == false) {
      cost -= (*it)->getHarvestValue();
      (*it)->setTapped();            
    }
  }
  return true;
}

/* ========================================================================= */

void Player::cleanup()
{
  for (auto it = army->begin(); it != army->end(); /* NOTHING */)
  {
    if ((*it)->checkIfDead() == true)
      it = army->erase(it);
    else
    {
      (*it)->cleanup(); /* Erase detached greenCards */
      ++it;
    }
  }
}

/* ========================================================================= */

BlackCardPtr Player::drawBlackCard(void) {
  BlackCardPtr tmp = dynastyDeck->front();
  dynastyDeck->pop_front();
  return tmp;
}

/* ========================================================================= */

GreenCardPtr Player::drawFateCard(void) {
  GreenCardPtr tmp = fateDeck->front();
  fateDeck->pop_front();
  return tmp;
}
/* ========================================================================= */
