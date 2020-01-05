
#ifndef BLACKCARDS_0
#define BLACKCARDS_0

class Personality;
class Holding;
class Mine;
class GoldMine;
class CrystalMine;
class StrongHold;

#include "basicCards.h"
#include "greenCards.h"

enum PersonalityType
{
  ATTACKER, DEFENDER, CHAMPION, CHANCELLOR, SHOGUN
};

enum HoldingType
{
  MINE, GOLD_MINE, CRYSTAL_MINE, PLAIN, FARMLAND, GIFT_N_FAVOUR, STRONGHOLD 
};

//==========================================|| B L A C K  C A R D ||==========================================

class BlackCard : public Card
{
protected:

  bool isRevealed;

  const enum BlackCardType type;

public:
    
  BlackCard(const std::string & name , const size_t & cost , const enum BlackCardType = PERSONALITY); 

  enum BlackCardType getBlackCardType() const { return type; }

  void setRevealed() { isRevealed = true;  }
  void setHidden()   { isRevealed = false; }

  bool checkRevealed() const { return isRevealed; }

  virtual void print() const = 0;
  virtual void attachToPlayer(PlayerPtr) = 0;
};

//==========================================|| P E R S O N A L I T Y ||==========================================

class Personality : public BlackCard
{
  const size_t attack;
  const size_t defence;
  
  size_t honor; // honor can be decreased till 0

  bool isDead;
  
  FollowerListPtr followers;
  ItemListPtr     items;

  const enum PersonalityType type;

public:
    
  Personality(const std::string & name , const size_t & cost , const size_t & attack ,const size_t & defence , const size_t & honor , const enum PersonalityType );

  enum PersonalityType getPersonalityType() const { return type; }

  size_t getATK() const { return attack;  }
  size_t getDEF() const { return defence; }
  size_t getHonor() const { return honor; }

  void die() { isDead = true; } // this is nice
  void kys() { isDead = true; } // this is nicer
  void decreaseHonor() { --honor; }

  bool checkIfDead() const { return isDead; }

  FollowerListPtr getFollowers() const { return followers; }
  ItemListPtr     getItems()     const { return items; }

  void print() const;
  void attachToPlayer(PlayerPtr);

  void cleanup(); // removes detached items + followers
};

//==========================================|| H O L D I N G ||==========================================

class Holding : public BlackCard
{
protected:

  size_t harvestValue; // Not const , because during Mine linkage it grows 

  const enum HoldingType type;

public:
    
  Holding(const std::string & name , const size_t & cost , const size_t & harvestValue , const enum HoldingType type);

  enum HoldingType getHoldingType() const { return type; }

  size_t getHarvestValue() const { return harvestValue; }

  void increaseHarvestValueBy (size_t points) { harvestValue += points; }

  virtual void print() const; // isws den xreiazontai prints sta mines :shrug: (alla mallon xreiazontai)

  void attachToPlayer(PlayerPtr);
};

//==========================================|| M I N E ||==========================================

class Mine : public Holding
{
  GoldMinePtr upperHolding;

public:
    
  Mine(const std::string & name = "MINE", const size_t & cost = 5 , const size_t & harvestValue = 3);

  void setUpperHolding (GoldMinePtr gMine) { upperHolding = gMine ; }
  void attachToPlayer(PlayerPtr);
  void print() const;

  GoldMinePtr getUpperHolding (void) const { return upperHolding ; }
};

//==========================================|| C R Y S T A L  M I N E ||==========================================
// ligo malakia pou exw mia oloidia class me allo onoma enos member alla nta3 ugeia
class CrystalMine : public Holding
{
  GoldMinePtr subHolding;

public:
    
  CrystalMine(const std::string & name = "CRYSTAL_MINE" , const size_t & cost = 12 , const size_t & harvestValue = 6);

  void setSubHolding (GoldMinePtr gMine) { subHolding = gMine ; }
  void attachToPlayer(PlayerPtr);
  void print() const;

  GoldMinePtr getSubHolding (void) const { return subHolding ; }
};

//==========================================|| G O L D  M I N E ||==========================================

class GoldMine : public Holding
{
  CrystalMinePtr upperHolding;
  MinePtr        subHolding;

public:
    
  GoldMine(const std::string & name = "GOLD_MINE", const size_t & cost = 7 , const size_t & harvestValue = 5);  

  void setUpperHolding (CrystalMinePtr crM) { upperHolding = crM ; }
  void setSubHolding (MinePtr M)            { subHolding = M ; }
  void attachToPlayer(PlayerPtr);
  void print() const;

  CrystalMinePtr getUpperHolding() const { return upperHolding ; } 
  MinePtr        getSubHolding()   const { return subHolding ; }


};

//==========================================|| S T R O N G H O L D ||==========================================

class StrongHold : public Holding
{
  const size_t initHonor;
  const size_t initDefence;
/*  const size_t initMoney; == harvest apo base class */
public:
    
  StrongHold();

  size_t getInitHonor() const { return initHonor; }
  size_t getInitDEF()   const { return initDefence; }

  void print() const;
};


#endif