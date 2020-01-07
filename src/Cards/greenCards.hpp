
#ifndef GREENCARDS_0
#define GREENCARDS_0

class Follower;
class Item;

#include "basicCards.hpp"

/* ========================================================================= */

/* Types of Green Cards */
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

/* =========================|| G R E E N  C A R D ||========================= */

class GreenCard : public Card
{
protected:

  uint16_t attackBonus;          
  uint16_t defenceBonus;
  const uint16_t minHonor;

  const std::string cardText;
  
  const uint16_t effectBonus; 
  const uint16_t effectCost;  

  bool attached; 

  const enum GreenCardType type;

  const uint16_t maxPerPerson;  /* Max Green Cards per Person */

public:

  GreenCard(const std::string &, const uint16_t &, const uint16_t &, 
            const uint16_t &, const uint16_t &, const std::string &, 
            const uint16_t &, const uint16_t &, const uint16_t & , 
            const enum GreenCardType = FOLLOWER);

  uint16_t getATK() const { return attackBonus;  }
  uint16_t getDEF() const { return defenceBonus; }
  uint16_t getMinHonor() const { return minHonor; }
  uint16_t getEffectCost() const { return effectCost; }
  enum GreenCardType getGreenCardType() const { return type; }
  /* Not defined for this class */
  virtual uint16_t getMaxPerPersonality() const = 0;

  bool isAttached() const { return attached; }

  void attach() { attached = true;  }
  void detach() { attached = false; }
  void upgrade();

  virtual void print() const = 0;
  virtual void attachToPersonality(PersonalityPtr) = 0;
};

/* ===========================|| F O L L O W E R ||=========================== */

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

/* ===============================|| I T E M ||=============================== */

class Item : public GreenCard
{
  uint16_t durability;  /* Can be decreased till 0 */

  const enum ItemType type;

public:
    
  Item(const uint16_t &, const std::string &, const uint16_t &, const uint16_t &,
       const uint16_t &, const uint16_t &, const std::string &, const uint16_t &, 
       const uint16_t &, const enum ItemType , const uint16_t);

  uint16_t getDurability()        const { return durability; }
  uint16_t getMaxPerPersonality() const { return maxPerPerson; }
  enum ItemType getItemType()   const { return type; }

  void decreaseDurability() { --durability; }
  void attachToPersonality(PersonalityPtr);
  
  void print() const;
};

#endif
/* =========================|| E N D  O F  F I L E ||========================= */