
#include "basicHeader.h"
#include "greenCards.h"
#include "blackCards.h"

/* ========================================================================= */

Card::Card (const std::string & name , const size_t & cost )
: name(name),
  cost(cost), 
  isTapped(true)
  {}

/* ========================================================================= */

GreenCard::GreenCard(const std::string & name ,  const size_t & cost , 
                     const size_t & attackBonus ,const size_t & defenceBonus ,
                     const size_t & minHonor ,   const std::string & cardText ,
                     const size_t & effectBonus ,const size_t & effectCost , 
                     const enum GreenCardType type) 
: Card(name , cost) , 
  attackBonus(attackBonus), 
  defenceBonus(defenceBonus), 
  minHonor(minHonor), 
  cardText(cardText), 
  effectBonus(effectBonus), 
  effectCost(effectCost), 
  attached(false), 
  type(type)
  {}


void GreenCard::upgrade() 
{ 
  attackBonus  += effectBonus;
  defenceBonus += effectBonus;
}

/* ========================================================================= */

Follower::Follower(const std::string & name ,     const size_t & cost , 
                   const size_t & attackBonus ,   const size_t & defenceBonus ,
                   const size_t & minHonor ,      const std::string & cardText ,
                   const size_t & effectBonus ,   const size_t & effectCost , 
                   const enum FollowerType type , const size_t maxPerPerson ) 
: GreenCard(name , cost , attackBonus , defenceBonus , minHonor , cardText , effectBonus , effectCost), 
  type(type), 
  maxPerPerson(maxPerPerson)
  {}


void Follower::attachToPersonality (PersonalityPtr pers) {
  pers->getFollowers()->push_back(std::make_shared<Follower>(*this));
}

/* ========================================================================= */

Item::Item(const size_t & dur ,          const std::string & name ,   const size_t & cost , 
           const size_t & attackBonus ,  const size_t & defenceBonus ,const size_t & minHonor ,
           const std::string & cardText ,const size_t & effectBonus , const size_t & effectCost , 
           const enum ItemType type,     const size_t maxPerPerson) 
: GreenCard(name , cost , attackBonus , defenceBonus , minHonor , cardText , effectBonus , effectCost) , 
  durability(dur), 
  type(type), 
  maxPerPerson(maxPerPerson)
  {}


void Item::attachToPersonality (PersonalityPtr pers) {
  pers->getItems()->push_back(std::make_shared<Item>(*this));
}
/* ========================================================================= */

BlackCard::BlackCard(const std::string & name , const size_t & cost , 
                     const enum BlackCardType type)
: Card(name , cost), 
  isRevealed(false), 
  type(type)
  {}

/* ========================================================================= */

Personality::Personality(const std::string & name , const size_t & cost ,  const size_t & attack ,
                         const size_t & defence ,   const size_t & honor , const enum PersonalityType type)
: BlackCard(name , cost), 
  attack(attack), 
  defence(defence), 
  honor(honor), 
  isDead(false), 
  followers(std::make_shared<std::list< std::shared_ptr <Follower > > >()),
  items( std::make_shared < std::list< std::shared_ptr <Item > > >()), 
  type(type)
  {}


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


void Personality::attachToPlayer (PlayerPtr pl) {
  pl->getArmy()->push_back(std::make_shared< Personality >(*this));
}

/* ========================================================================= */

Holding::Holding(const std::string & name ,    const size_t & cost , 
                 const size_t & harvestValue , const enum HoldingType type)
: BlackCard(name , cost), 
  harvestValue(harvestValue), 
  type(type)
  {}


void Holding::attachToPlayer (PlayerPtr pl) {
  pl->getHoldings()->push_back(std::make_shared< Holding >(*this));  
}

/* ========================================================================= */

StrongHold::StrongHold() 
: Holding("StrongHold" , 0 , 5 , STRONGHOLD), 
  initHonor(5), 
  initDefence(5)
  {} 
/* ========================================================================= */