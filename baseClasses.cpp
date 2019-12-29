// File that contains the implementation of constructors / destructors of baseClasses.h

// TODO : isws merikes classes xreiastoun default orismata

// TODO : use smart pointers

#include <cstddef>    // size_t
#include <iostream>
#include "baseClasses.h"

Card::Card (const std::string & name , const size_t & cost )
: name(name) , cost(cost) , isTapped(true) {}

GreenCard::GreenCard(const std::string & name , const size_t & cost , const size_t & attackBonus ,const size_t & defenceBonus ,const size_t & minHonor ,const std::string & cardText ,const size_t & effectBonus ,const size_t & effectCost ) 
: Card(name , cost) , attackBonus(attackBonus) , defenceBonus(defenceBonus) , minHonor(minHonor) , cardText(cardText) , effectBonus(effectBonus) , effectCost(effectCost) {}


BlackCard::BlackCard(const std::string & name , const size_t & cost)
: Card(name , cost) , isRevealed(false) {}

Follower::Follower(const std::string & name , const size_t & cost , const size_t & attackBonus ,const size_t & defenceBonus ,const size_t & minHonor ,const std::string & cardText ,const size_t & effectBonus ,const size_t & effectCost ) 
: GreenCard(name , cost , attackBonus , defenceBonus , minHonor , cardText , effectBonus , effectCost) {}

Item::Item(const size_t & dur , const std::string & name , const size_t & cost , const size_t & attackBonus ,const size_t & defenceBonus ,const size_t & minHonor ,const std::string & cardText ,const size_t & effectBonus ,const size_t & effectCost ) 
: GreenCard(name , cost , attackBonus , defenceBonus , minHonor , cardText , effectBonus , effectCost) , durability(dur) {}

Personality::Personality(const std::string & name , const size_t & cost , const size_t & attack ,const size_t & defence , const size_t & honor)
: BlackCard(name , cost) , attack(attack) , defence(defence) , honor(honor) , isDead(false) , followers(nullptr) , items(nullptr) {}

Personality::~Personality() {
    if (followers != nullptr) delete followers;
    if (items != nullptr) delete items;
}

Holding::Holding(const std::string & name , const size_t & cost , const size_t & harvestValue)
: BlackCard(name , cost) , harvestValue(harvestValue) {}

Mine::Mine(const std::string & name , const size_t & cost , const size_t & harvestValue) 
: Holding(name , cost , harvestValue) , upperHolding(nullptr) {} 

Mine::~Mine() { if (upperHolding != nullptr) delete upperHolding; }

CrystalMine::CrystalMine(const std::string & name , const size_t & cost , const size_t & harvestValue) 
: Holding(name , cost , harvestValue) , subHolding(nullptr) {} 

CrystalMine::~CrystalMine() { if (subHolding != nullptr) delete subHolding; }

GoldMine::GoldMine(const std::string & name , const size_t & cost , const size_t & harvestValue)
: Holding(name , cost , harvestValue) , upperHolding(nullptr) ,subHolding(nullptr) {} 

GoldMine::~GoldMine() { 
    if (upperHolding != nullptr) delete upperHolding; 
    if (subHolding != nullptr) delete subHolding; 
}

StrongHold::StrongHold() // TODO : to Stronghold den exei cost ?
: Holding("StrongHold" , 0 , 5) , initHonor(5) , initDefence(5) {} 

Province::Province(BlackCard * blC) : isBroken(false) , card(blC) {}

Province::~Province() { delete card; }  // tou pousth pia den vazw elegxo gia null kai edw

Player::Player(const std::string & userName , StrongHold * stronghold)
: userName(userName) , strongHold(stronghold) , honor(stronghold->getInitHonor()) , activeProvinces(0) , fateDeck(nullptr) , dynastyDeck(nullptr) , hand(nullptr) , holdings(nullptr) , army(nullptr) , provinces(nullptr) {}

Player::~Player() {
    // einai anagkaioi oloi oi elegxoi gia null ?
    if (strongHold != nullptr)delete strongHold;
    if (fateDeck != nullptr)delete fateDeck;
    if (dynastyDeck != nullptr)delete dynastyDeck;
    if (hand != nullptr) delete hand;
    if (holdings != nullptr) delete holdings;
    if (army != nullptr) delete army;
    if (provinces != nullptr) delete provinces;
}
