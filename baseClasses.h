// Feel free to rename the file ;)
// I love camelCase // :|

#include <iostream>
#include <queue>
#include <vector>

//==========================================|| C A R D ||==========================================

class Card
{
  const std::string name;
    
  const size_t cost;
    
  bool isTapped;

public:

  Card(/* args */);
  ~Card();
};

// Kalutera na mhn valoume ta panta ola const gt mporei na exoume 8emata meta 

//==========================================|| G R E E N  C A R D ||==========================================

class GreenCard : public Card
{
  const size_t attackBonus;              /* I think bonuses are e.g  0,2 x attack . That's why they're floats */
  const size_t defenceBonus;
  const size_t minHonor;

  const std::string cardText;           /* Dunno if its const or not. We'll see */

  const size_t effectBonus;
  const size_t effectCost;

public:
    
  GreenCard(/* args */);
  ~GreenCard();
};

//==========================================|| B L A C K  C A R D ||==========================================

class BlackCard : public Card
{
  bool isRevealed;

public:
    
  BlackCard(/* args */); 
  ~BlackCard();
};

//==========================================|| F O L L O W E R ||==========================================

class Follower : public GreenCard
{
public:
    
  Follower(/* args */);
  ~Follower();
};

//==========================================|| I T E M ||==========================================

class Item : public GreenCard
{
  const size_t durability;

public:
    
  Item(/* args */);
  ~Item();
};

//==========================================|| P E R S O N A L I T Y ||==========================================

class Personality : public BlackCard
{
  const size_t attack;
  const size_t defence;
  const size_t honor;

  bool isDead;
  
  vector <Follower *> * followers;
  vector <Item *>     * items;

public:
    
  Personality(/* args */);
  ~Personality();
};

//==========================================|| H O L D I N G ||==========================================

class Holding : public BlackCard
{
  const size_t harvestValue;     

public:
    
  Holding(/* args */);
  ~Holding();
};

//==========================================|| M I N E ||==========================================

class Mine : public Holding
{
  Holding * upperHolding;

public:
    
  Mine(/* args */);
  ~Mine();
};

//==========================================|| C R Y S T A L  M I N E ||==========================================
// ligo malakia pou exw mia oloidia class me allo onoma enos member alla nta3 ugeia
class CrystalMine : public Holding
{
  Holding * subHolding;

public:
    
  CrystalMine(/* args */);
  ~CrystalMine();
};

//==========================================|| G O L D  M I N E ||==========================================

class GoldMine : public Holding
{
  Holding * upperHolding;
  Holding * subHolding;

public:
    
  GoldMine(/* args */);  
  ~GoldMine();
};

//==========================================|| S T R O N G H O L D ||==========================================

class StrongHold : public Holding
{
  const size_t initHonor;
  const size_t initMoney;
  const size_t initDefence;

public:
    
  StrongHold(/* args */);
  ~StrongHold();
};

//==========================================|| T Y P E D E F S ||==========================================

typedef Item Katana;
typedef Item Spear;
typedef Item Bow;
typedef Item Ninjato;
typedef Item Wakizashi;

typedef Follower Footsoldier;
typedef Follower Archer;
typedef Follower Cavalry;
typedef Follower Bushido;
typedef Follower Sieger;
typedef Follower Atakebune;

typedef Personality Attacker;
typedef Personality Defender;
typedef Personality Champion;
typedef Personality Chancellor;
typedef Personality Shogun;

typedef Holding Plain;
typedef Holding Farmland;
typedef Holding Gift_n_Favour;

//==========================================|| P L A Y E R ||==========================================

class Player
{
  const size_t honor;

  queue <GreenCard *> * fateDeck;
  queue <BlackCard *> * dynastyDeck;

  vector <GreenCard *> * hand;
  vector <Holding *> * holdings;
  vector <Personality *> * army;
  vector <BlackCard *> * provinces;

public:

  Player(/* args */);
  ~Player();
};

//==========================================|| E N D  O F  F I L E ||==========================================
