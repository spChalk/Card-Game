
#include "baseClasses.h"
#include "greenCards.h"
#include "blackCards.h"

/* ========================================================================= */

void GreenCard::upgrade() 
{ 
  attackBonus  += effectBonus;
  defenceBonus += effectBonus;
}

/* ========================================================================= */

void Follower::attachToPersonality (PersonalityPtr pers) {
  pers->getFollowers()->push_back(std::make_shared<Follower>(*this));
}

/* ========================================================================= */

void Item::attachToPersonality (PersonalityPtr pers) {
  pers->getItems()->push_back(std::make_shared<Item>(*this));
}
/* ========================================================================= */

void Personality::cleanup()
{
  for (auto it = followers->begin(); it != followers->end(); /* NOTHING */)
  {
    if ((*it)->isAttached() == false)
      it = followers->erase(it);
    else
      ++it;
  }

  for (auto it = items->begin(); it != items->end(); /* NOTHING */)
  {
    if ((*it)->isAttached() == false)
      it = items->erase(it);
    else
      ++it;
  }
}

/* ========================================================================= */

void Personality::attachToPlayer (PlayerPtr pl) {
  pl->getArmy()->push_back(std::make_shared< Personality >(*this));
}

/* ========================================================================= */

void Holding::attachToPlayer (PlayerPtr pl) {
  pl->getHoldings()->push_back(std::make_shared< Holding >(*this));  
}
/* ========================================================================= */
