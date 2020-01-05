
#include "baseClasses.h"
#include "player.h"

/* ========================================================================= */
size_t Player::getCurrMoney() const
{
  HoldingListPtr holdings = this->getHoldings();

  size_t total = 0;

  if (this->getStrongHold()->checkTapped() == false)
    total += this->getStrongHold()->getHarvestValue();

  for (auto i : *holdings)
    if (i->checkTapped() == false) total += i->getHarvestValue();

  return total;
}
/* ========================================================================= */

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

/* ========================================================================= */

void Player::cleanup()
{
  for (auto it = army->begin(); it != army->end(); /* NOTHING */)
  {
    if ((*it)->checkIfDead() == true)
      it = army->erase(it);
    else
    {
      (*it)->cleanup(); // erase detached greenCards
      ++it;
    }
  }
}

/* ========================================================================= */

BlackCardPtr Player::drawBlackCard(void) { // TODO : assert if empty
  BlackCardPtr tmp = dynastyDeck->front();
  dynastyDeck->pop();
  return tmp;
}

/* ========================================================================= */

GreenCardPtr Player::drawFateCard(void) { // TODO : assert if empty
  GreenCardPtr tmp = fateDeck->front();
  fateDeck->pop();
  return tmp;
}
/* ========================================================================= */
