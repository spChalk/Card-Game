// TODO: make it clean
#ifndef CARDS_0
#define CARDS_0

class Card;
class GreenCard;
class BlackCard;

#include "baseClasses.h"

enum GreenCardType
{
  FOLLOWER, ITEM
};

enum BlackCardType
{
  PERSONALITY, HOLDING
};

//==========================================|| C A R D ||==========================================

class Card
{
protected:

  const std::string name;
    
  const size_t cost;
    
  bool isTapped;

public:

  Card(const std::string & name , const size_t & cost );
  virtual ~Card() {} 

  const std::string getName (void) const { return name; }

  void setTapped()   { isTapped = true;  }
  void setUnTapped() { isTapped = false; }

  size_t getCost(void) const { return cost; }
  
  bool checkTapped() const { return isTapped; }

  virtual void print() const = 0;
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

#endif