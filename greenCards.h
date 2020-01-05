
#ifndef GREENCARDS_0
#define GREENCARDS_0

class Follower;
class Item;

#include "cards.h"

enum FollowerType 
{
  FOOTSOLDIER, ARCHER, CAVALRY, BUSHIDO, SIEGER, ATAKEBUNE
};

enum ItemType
{
  KATANA, SPEAR, BOW, NINJATO, WAKIZASHI
};


//==========================================|| F O L L O W E R ||==========================================

class Follower : public GreenCard
{
  const enum FollowerType type;
  const size_t maxPerPerson; // MAX_<GREENCARD>_PER_PERSON gia na mhn xrhsimopoioume tis define'd times pantou sta .cpp
  // [Spiros] Yparxei 8ema an xrhsimopoioume ta defined all the way ? 

public:

  Follower(const std::string & name , const size_t & cost , const size_t & attackBonus ,const size_t & defenceBonus ,const size_t & minHonor ,const std::string & cardText ,const size_t & effectBonus ,const size_t & effectCost , const enum FollowerType , const size_t maxPerPerson);

  enum FollowerType getFollowerType() const { return type; }

  size_t getMaxPerPersonality() const { return maxPerPerson; }

  void print() const;
  void attachToPersonality(PersonalityPtr);
};

//==========================================|| I T E M ||==========================================

class Item : public GreenCard
{
  size_t durability; // not const because it can be decreased till 0 

  const enum ItemType type;
  const size_t maxPerPerson;

public:
    
  Item(const size_t & dur , const std::string & name , const size_t & cost , const size_t & attackBonus ,const size_t & defenceBonus ,const size_t & minHonor ,const std::string & cardText ,const size_t & effectBonus ,const size_t & effectCost , const enum ItemType , const size_t maxPerPerson);

  enum ItemType getItemType() const { return type; }
  
  size_t getDurability() const { return durability; }
  size_t getMaxPerPersonality() const { return maxPerPerson; }
  
  void decreaseDurability() { --durability; }
  void attachToPersonality(PersonalityPtr);
  
  void print() const;
};

#endif