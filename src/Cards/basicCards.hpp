// TODO: make it clean
#ifndef CARDS_0
#define CARDS_0

class Card;
class GreenCard;
class BlackCard;

#include "basicHeader.hpp"

/* ======================================================== */
class Card
{
protected:

  const std::string name;
    
  const uint16_t cost;
    
  bool isTapped;

public:

  Card(const std::string & name , const uint16_t & cost );
  virtual ~Card() {} 

  const std::string getName (void) const { return name; }

  bool checkTapped() const { return isTapped; }

  void setTapped()   { isTapped = true;  }
  void setUnTapped() { isTapped = false; }

  uint16_t getCost(void) const { return cost; }

  virtual void print() const = 0;
};
/* ======================================================== */

#endif