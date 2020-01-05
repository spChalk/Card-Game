// File that contains the implementation of constructors / destructors of baseClasses.h


#include <cstddef>    // size_t
#include <iostream>
#include <memory>
#include "baseClasses.h"

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
/* ========================================================================= */

BlackCard::BlackCard(const std::string & name , const size_t & cost , 
                     const enum BlackCardType type)
: Card(name , cost), 
  isRevealed(false), 
  type(type)
  {}
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
/* ========================================================================= */

Holding::Holding(const std::string & name ,    const size_t & cost , 
                 const size_t & harvestValue , const enum HoldingType type)
: BlackCard(name , cost), 
  harvestValue(harvestValue), 
  type(type)
  {}
/* ========================================================================= */

Mine::Mine(const std::string & name , const size_t & cost , const size_t & harvestValue) 
: Holding(name , cost , harvestValue , MINE), 
  upperHolding(nullptr)
  {} 
/* ========================================================================= */

CrystalMine::CrystalMine(const std::string & name , const size_t & cost , const size_t & harvestValue) 
: Holding(name , cost , harvestValue , CRYSTAL_MINE), 
  subHolding(nullptr)
  {} 
/* ========================================================================= */

GoldMine::GoldMine(const std::string & name , const size_t & cost , const size_t & harvestValue)
: Holding(name , cost , harvestValue , GOLD_MINE), 
  upperHolding(nullptr),
  subHolding(nullptr)
  {} 
/* ========================================================================= */

StrongHold::StrongHold() 
: Holding("StrongHold" , 0 , 5 , STRONGHOLD), 
  initHonor(5), 
  initDefence(5)
  {} 
/* ========================================================================= */

Province::Province(BlackCardPtr blackCard)
: isBroken(false), 
  card(blackCard)
  {}
/* ========================================================================= */

Player::Player(const std::string & userName )
: userName(userName) , 
  strongHold(std::make_shared< StrongHold >()), 
  honor(strongHold->getInitHonor()), 
  activeProvinces(0), 
  fateDeck(std::make_shared < std::queue<std::shared_ptr <GreenCard > > >()) , 
  dynastyDeck(std::make_shared< std::queue<std::shared_ptr <BlackCard > > >()) , 
  hand(std::make_shared< std::list<std::shared_ptr <GreenCard > > >()) , 
  army(std::make_shared< std::list<std::shared_ptr <Personality > > >()) , 
  holdings(std::make_shared< std::list<std::shared_ptr <Holding > > >()) , 
  provinces(std::make_shared< std::list<std::shared_ptr <Province > > >())
  {}
/* ========================================================================= */
