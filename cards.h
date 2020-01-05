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


#endif