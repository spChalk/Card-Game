
#ifndef BLACKCARDS_0
#define BLACKCARDS_0

class Personality;
class Holding;
class Mine;
class GoldMine;
class CrystalMine;
class StrongHold;

#include "basicCards.hpp"
#include "greenCards.hpp"

/* ========================================================================== */

/* Types of Black Cards */
enum class BlackCardType
{
  PERSONALITY, HOLDING
};

enum class PersonalityType
{
  ATTACKER, DEFENDER, CHAMPION, CHANCELLOR, SHOGUN
};

enum class HoldingType
{
  MINE, GOLD_MINE, CRYSTAL_MINE, PLAIN, FARMLAND, GIFT_N_FAVOUR, STRONGHOLD 
};

/* =========================|| B L A C K  C A R D ||========================= */

class BlackCard : public Card
{
protected:

  bool isRevealed;

  const BlackCardType type;

public:
    
  BlackCard(const std::string & name , const uint16_t & cost , const BlackCardType); 

  BlackCardType getBlackCardType() const { return type; }

  void setRevealed() { isRevealed = true;  }
  void setHidden()   { isRevealed = false; }

  bool checkRevealed() const { return isRevealed; }

  virtual void print() const = 0;
  virtual void attachToPlayer(PlayerPtr) = 0;
};

/* ========================|| P E R S O N A L I T Y ||======================== */

class Personality : public BlackCard
{
  const uint16_t attack;
  const uint16_t defence;
  
  uint16_t honor;  /* Honor can be decreased till 0 */

  bool isDead;
  
  FollowerListPtr followers;  /* List of Followers */
  ItemListPtr     items;      /* List of Items */

  const PersonalityType type;

public:
    
  Personality(const std::string & name , const uint16_t & cost , const uint16_t & attack ,const uint16_t & defence , const uint16_t & honor , const PersonalityType );

  uint16_t getATK() const { return attack;  }
  uint16_t getDEF() const { return defence; }
  uint16_t getHonor() const { return honor; }
  FollowerListPtr getFollowers() const { return followers; }
  ItemListPtr     getItems()     const { return items; }
  PersonalityType getPersonalityType() const { return type; }

  void die() { isDead = true; }
  
  void kys() { isDead = true; }  /* Kill YourSelf, Personality commits suicide */
  
  void decreaseHonor() { --honor; }

  bool checkIfDead() const { return isDead; }

  void print() const;

  void attachToPlayer(PlayerPtr);

  void cleanup();  /* Removes detached Items & Followers */
};

/* =========================|| H O L D I N G ||========================= */

class Holding : public BlackCard
{
protected:

  uint16_t harvestValue;  

  const HoldingType type;

public:
    
  Holding(const std::string & name , const uint16_t & cost , const uint16_t & harvestValue , const HoldingType type);

  HoldingType getHoldingType() const { return type; }
  uint16_t getHarvestValue() const { return harvestValue; }

  void increaseHarvestValueBy (uint16_t points) { harvestValue += points; }

  virtual void print() const;

  void attachToPlayer(PlayerPtr);
};

/* ============================|| M I N E ||============================ */

class Mine : public Holding
{
  GoldMinePtr upperHolding;

public:
    
  Mine(const std::string & name = "MINE", const uint16_t & cost = 5 , const uint16_t & harvestValue = 3);

  GoldMinePtr getUpperHolding (void) const { return upperHolding ; }

  void setUpperHolding (GoldMinePtr gMine) { upperHolding = gMine ; }

  void attachToPlayer(PlayerPtr);
  void print() const;
};

/* =====================|| C R Y S T A L  M I N E ||===================== */

class CrystalMine : public Holding
{
  GoldMinePtr subHolding;

public:
    
  CrystalMine(const std::string & name = "CRYSTAL_MINE" , const uint16_t & cost = 12 , const uint16_t & harvestValue = 6);

  GoldMinePtr getSubHolding (void) const { return subHolding ; }

  void setSubHolding (GoldMinePtr gMine) { subHolding = gMine ; }
  
  void attachToPlayer(PlayerPtr);
  void print() const;
};

/* ========================|| G O L D  M I N E ||======================== */

class GoldMine : public Holding
{
  CrystalMinePtr upperHolding;

  MinePtr        subHolding;

public:
    
  GoldMine(const std::string & name = "GOLD_MINE", const uint16_t & cost = 7 , const uint16_t & harvestValue = 5);  

  CrystalMinePtr getUpperHolding() const { return upperHolding ; } 
  MinePtr        getSubHolding()   const { return subHolding ; }

  void setUpperHolding (CrystalMinePtr crM) { upperHolding = crM ; }
  void setSubHolding (MinePtr M)            { subHolding = M ; }
  
  void attachToPlayer(PlayerPtr);
  void print() const;
};

/* ======================|| S T R O N G H O L D ||====================== */

class StrongHold : public Holding
{
  const uint16_t initHonor;
  const uint16_t initDefence;

public:
    
  StrongHold(const uint16_t & initHonour , const uint16_t & initDefence , const std::string & name = "STRONGHOLD" , const uint16_t & harvestValue = 5 , const uint16_t & cost = 0 );

  uint16_t getInitHonor() const { return initHonor; }
  uint16_t getInitDEF()   const { return initDefence; }

  void print() const;
};

#endif
/* ======================|| E N D  O F  F I L E ||====================== */