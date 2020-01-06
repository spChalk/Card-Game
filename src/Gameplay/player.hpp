#ifndef PLAYER_0
#define PLAYER_0

class Player;
class Province;

#include "basicHeader.hpp"

/* ================================================================= */
class Province
{
  bool isBroken; // init as false

  BlackCardPtr card;

public:

  Province(BlackCardPtr);

  bool checkBroken() const { return isBroken; }

  void setBroken() { isBroken = true; }
  void setCard(BlackCardPtr bc) { card = bc ; }

  BlackCardPtr getCard() const { return card; }

  void print() const;

};

/* ================================================================= */

class Player
{
  const std::string userName;

  StrongHoldPtr strongHold;

  const size_t honor;
  
  size_t activeProvinces;

  FateDeckPtr    fateDeck;
  DynastyDeckPtr dynastyDeck;

  HandPtr hand;
  ArmyPtr army;

  HoldingListPtr  holdings;
  ProvinceListPtr provinces;

public:

  Player(const std::string & userName );

  const std::string& getUserName() const { return userName; }

  size_t getHonor()        const { return honor; }
  size_t getProvincesNum() const { return activeProvinces; }
  size_t getCurrMoney()    const;

  void decreaseProvinceNum() { --activeProvinces; }
  void increaseProvinceNum() { ++activeProvinces; }
  
  FateDeckPtr    getFateDeck()    const { return fateDeck; }
  DynastyDeckPtr getDynastyDeck() const { return dynastyDeck; }
  
  HandPtr getHand() const { return hand; }
  ArmyPtr getArmy() const { return army; }

  ProvinceListPtr getProvinces() const { return provinces; }
  HoldingListPtr  getHoldings()  const { return holdings; }

  StrongHoldPtr getStrongHold()  const { return strongHold; }

  void setFateDeck   (FateDeckPtr    fDeck) { fateDeck    = fDeck; }
  void setDynastyDeck(DynastyDeckPtr dDeck) { dynastyDeck = dDeck; }

  void print()              const;
  void printHoldings()      const;
  void printArmy()          const;
  void printArena()         const;
  void printAvailableArmy() const;
  void printHand()          const;
  void printProvinces()     const;
  void printStatistics()    const;

  bool makePurchase (size_t cost ); // Tap Holdings until you cover the needed cost
    // Returns true if the purchase is successfull
  void cleanup(); // Removes 1) dead personalities from army 2) detached GreenCards

  BlackCardPtr drawBlackCard (void);
  GreenCardPtr drawFateCard (void);
};  
/* ================================================================= */

#endif