
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


//==========================================|| G R E E N  C A R D ||==========================================

class GreenCard : public Card
{
protected:

  size_t attackBonus;          
  size_t defenceBonus;
  const size_t minHonor;

  const std::string cardText;
  
  const size_t effectBonus; // [Harry] auta a8roizontai sto antistoixo bonus field sto equipment phase (an ginei upgrade)
  const size_t effectCost;  // meta den exoun KAMIA xrhsimothta

  bool attached; // antistoixo ths isDead tou blackCard < Personality

  const enum GreenCardType type;

public:
    
  GreenCard(const std::string & name , const size_t & cost , const size_t & attackBonus ,const size_t & defenceBonus ,const size_t & minHonor ,const std::string & cardText ,const size_t & effectBonus ,const size_t & effectCost , const enum GreenCardType = FOLLOWER);

  enum GreenCardType getGreenCardType() const { return type; }

  size_t getATK() const { return attackBonus;  }
  size_t getDEF() const { return defenceBonus; }
  size_t getMinHonor() const { return minHonor; }
  size_t getEffectCost() const { return effectCost; }

  void attach() { attached = true;  }
  void detach() { attached = false; }

  bool isAttached() const { return attached; }
  virtual void attachToPersonality(PersonalityPtr) = 0;

  void upgrade(); 

  virtual void print() const = 0;
  /* Not defined for this class */
  virtual size_t getMaxPerPersonality() const = 0;
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