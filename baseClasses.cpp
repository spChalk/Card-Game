// File that contains the implementation of constructors / destructors of baseClasses.h

// TODO : isws merikes classes xreiastoun default orismata

// TODO : use smart pointers

#include <cstddef>    // size_t
#include <iostream>
#include "baseClasses.h"

Card::Card (const std::string & name , const size_t & cost )
: name(name) , cost(cost) , isTapped(true) {}

GreenCard::GreenCard(const std::string & name , const size_t & cost , const size_t & attackBonus ,const size_t & defenceBonus ,const size_t & minHonor ,const std::string & cardText ,const size_t & effectBonus ,const size_t & effectCost , const enum GreenCardType type) 
: Card(name , cost) , attackBonus(attackBonus) , defenceBonus(defenceBonus) , minHonor(minHonor) , cardText(cardText) , effectBonus(effectBonus) , effectCost(effectCost) , attached(false) , type(type) {}

BlackCard::BlackCard(const std::string & name , const size_t & cost , const enum BlackCardType type)
: Card(name , cost) , isRevealed(false) , type(type) {}

Follower::Follower(const std::string & name , const size_t & cost , const size_t & attackBonus ,const size_t & defenceBonus ,const size_t & minHonor ,const std::string & cardText ,const size_t & effectBonus ,const size_t & effectCost , const enum FollowerType type , const size_t maxPerPerson ) 
: GreenCard(name , cost , attackBonus , defenceBonus , minHonor , cardText , effectBonus , effectCost) , type(type) , maxPerPerson(maxPerPerson) {}

Item::Item(const size_t & dur , const std::string & name , const size_t & cost , const size_t & attackBonus ,const size_t & defenceBonus ,const size_t & minHonor ,const std::string & cardText ,const size_t & effectBonus ,const size_t & effectCost , const enum ItemType type, const size_t maxPerPerson) 
: GreenCard(name , cost , attackBonus , defenceBonus , minHonor , cardText , effectBonus , effectCost) , durability(dur) , type(type) , maxPerPerson(maxPerPerson) {}

Personality::Personality(const std::string & name , const size_t & cost , const size_t & attack ,const size_t & defence , const size_t & honor , const enum PersonalityType type)
: BlackCard(name , cost) , attack(attack) , defence(defence) , honor(honor) , isDead(false) , followers(new std::vector<Follower *>) , items(new std::vector<Item *>) , type(type) {}

Personality::~Personality() {
    delete followers;
    delete items;
}

Holding::Holding(const std::string & name , const size_t & cost , const size_t & harvestValue , const enum HoldingType type)
: BlackCard(name , cost) , harvestValue(harvestValue) , type(type) {}

Mine::Mine(const std::string & name , const size_t & cost , const size_t & harvestValue) 
: Holding(name , cost , harvestValue , MINE) , upperHolding(nullptr) {} 

Mine::~Mine() { if (upperHolding != nullptr) delete upperHolding; }

CrystalMine::CrystalMine(const std::string & name , const size_t & cost , const size_t & harvestValue) 
: Holding(name , cost , harvestValue , CRYSTAL_MINE) , subHolding(nullptr) {} 

CrystalMine::~CrystalMine() { if (subHolding != nullptr) delete subHolding; }

GoldMine::GoldMine(const std::string & name , const size_t & cost , const size_t & harvestValue)
: Holding(name , cost , harvestValue , GOLD_MINE) , upperHolding(nullptr) ,subHolding(nullptr) {} 

GoldMine::~GoldMine() { 
    if (upperHolding != nullptr) delete upperHolding; 
    if (subHolding != nullptr) delete subHolding; 
}

StrongHold::StrongHold() // TODO : to Stronghold den exei cost ?
: Holding("StrongHold" , 0 , 5 , STRONGHOLD) , initHonor(5) , initDefence(5) {} 

Province::Province(BlackCard * blC) : isBroken(false) , card(blC) {}

Province::~Province() { delete card; }  // tou pousth pia den vazw elegxo gia null kai edw

Player::Player(const std::string & userName )
: userName(userName) , strongHold(new StrongHold()) , honor(strongHold->getInitHonor()) , activeProvinces(0) , fateDeck(new queue<GreenCard *>) , dynastyDeck(new queue<BlackCard *>) , hand(new vector<GreenCard *>) , holdings(new vector<Holding *>) , army(new vector<Personality*>) , provinces(new vector<Province *>) {}

Player::~Player() {
    delete strongHold;
    delete fateDeck;
    delete dynastyDeck;
    delete hand;
    delete holdings;
    delete army;
    delete provinces;
}
