
#ifndef GREENCARDS_0
#define GREENCARDS_0

class Follower;
class Item;

#include "basicCards.hpp"

/* ========================================================================= */

enum GreenCardType
{
  FOLLOWER, ITEM
};

enum FollowerType 
{
  FOOTSOLDIER, ARCHER, CAVALRY, BUSHIDO, SIEGER, ATAKEBUNE
};

enum ItemType
{
  KATANA, SPEAR, BOW, NINJATO, WAKIZASHI
};

/* ========================================================================= */

class GreenCard : public Card
{
protected:

  uint16_t attackBonus;          
  uint16_t defenceBonus;
  const uint16_t minHonor;

  const std::string cardText;
  
  const uint16_t effectBonus; // [Harry] auta a8roizontai sto antistoixo bonus field sto equipment phase (an ginei upgrade)
  const uint16_t effectCost;  // meta den exoun KAMIA xrhsimothta

  bool attached; // antistoixo ths isDead tou blackCard < Personality

  const enum GreenCardType type;

  const uint16_t maxPerPerson; // MAX_<GREENCARD>_PER_PERSON gia na mhn xrhsimopoioume tis define'd times pantou sta .cpp

public:

  GreenCard(const std::string &, const uint16_t &, const uint16_t &, 
            const uint16_t &, const uint16_t &, const std::string &, 
            const uint16_t &, const uint16_t &, const uint16_t & , 
            const enum GreenCardType = FOLLOWER);

  enum GreenCardType getGreenCardType() const { return type; }

  bool isAttached() const { return attached; }

  uint16_t getATK() const { return attackBonus;  }
  uint16_t getDEF() const { return defenceBonus; }
  uint16_t getMinHonor() const { return minHonor; }
  uint16_t getEffectCost() const { return effectCost; }

  void attach() { attached = true;  }
  void detach() { attached = false; }
  void upgrade();

  virtual void print() const = 0;
  virtual void attachToPersonality(PersonalityPtr) = 0;
  /* Not defined for this class */
  virtual uint16_t getMaxPerPersonality() const = 0;
};

/* ========================================================================= */

class Follower : public GreenCard
{
  const enum FollowerType type;
  
public:

  Follower(const std::string &, const uint16_t &, const uint16_t &, const uint16_t &,
           const uint16_t &, const std::string &, const uint16_t &, const uint16_t &, 
           const enum FollowerType , const uint16_t);

  enum FollowerType getFollowerType() const { return type; }

  uint16_t getMaxPerPersonality() const { return maxPerPerson; }

  void attachToPersonality(PersonalityPtr);
  
  void print() const;
};

/* ========================================================================= */

class Item : public GreenCard
{
  uint16_t durability; // not const because it can be decreased till 0 

  const enum ItemType type;

public:
    
  Item(const uint16_t &, const std::string &, const uint16_t &, const uint16_t &,
       const uint16_t &, const uint16_t &, const std::string &, const uint16_t &, 
       const uint16_t &, const enum ItemType , const uint16_t);

  enum ItemType getItemType()   const { return type; }
  
  uint16_t getDurability()        const { return durability; }
  uint16_t getMaxPerPersonality() const { return maxPerPerson; }
  
  void decreaseDurability() { --durability; }
  void attachToPersonality(PersonalityPtr);
  
  void print() const;
};
/* ========================================================================= */

#endif