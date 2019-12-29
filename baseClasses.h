/* baseClasses.h */

// I love camelCase // :|
/* Declarations */ // also works as an index :)
class Game;
class Player;
class Card;
class GreenCard;
class BlackCard;

class Personality;
class Holding;
class Mine;
class GoldMine;
class CrystalMine;
class StrongHold;

class Follower;
class Item;


#include <cstddef> // size_t
#include <queue>
#include <string>
#include <vector>
#include <unordered_map>

#define MAX_HAND_CARDS 7

 
using std::vector;
using std::queue;

//==========================================|| C A R D ||==========================================

class Card
{
protected:

  const std::string name;
    
  const size_t cost;
    
  bool isTapped;

public:

  Card(const std::string & name , const size_t & cost );
  virtual ~Card();

  void setTapped()   { isTapped = true;  }
  void setUnTapped() { isTapped = false; }

  virtual void print() const = 0;
};

// Kalutera na mhn valoume ta panta ola const gt mporei na exoume 8emata meta 

//==========================================|| G R E E N  C A R D ||==========================================

class GreenCard : public Card
{
protected:

  const size_t attackBonus;              /* I think bonuses are e.g  0,2 x attack . That's why they're floats */
  const size_t defenceBonus;
  const size_t minHonor;

  const std::string cardText;
  
  const size_t effectBonus;
  const size_t effectCost;

public:
    
  GreenCard(const std::string & name , const size_t & cost , const size_t & attackBonus ,const size_t & defenceBonus ,const size_t & minHonor ,const std::string & cardText ,const size_t & effectBonus ,const size_t & effectCost );

  virtual void print() const = 0;
};

//==========================================|| B L A C K  C A R D ||==========================================

class BlackCard : public Card
{
protected:

  bool isRevealed;

public:
    
  BlackCard(const std::string & name , const size_t & cost); 

  void setRevealed() { isRevealed = true;  }
  void setHidden()   { isRevealed = false; }

  bool checkRevealed() { return isRevealed; }

  virtual void print() const = 0;
};

//==========================================|| F O L L O W E R ||==========================================

class Follower : public GreenCard
{
public:

  Follower(const std::string & name , const size_t & cost , const size_t & attackBonus ,const size_t & defenceBonus ,const size_t & minHonor ,const std::string & cardText ,const size_t & effectBonus ,const size_t & effectCost );

  void print() const;
};

//==========================================|| I T E M ||==========================================

class Item : public GreenCard
{
  const size_t durability;

public:
    
  Item(const size_t & dur , const std::string & name , const size_t & cost , const size_t & attackBonus ,const size_t & defenceBonus ,const size_t & minHonor ,const std::string & cardText ,const size_t & effectBonus ,const size_t & effectCost );

  void print() const;
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
    
  Personality(const std::string & name , const size_t & cost , const size_t & attack ,const size_t & defence , const size_t & honor);
  ~Personality();

  void print() const;
};

//==========================================|| H O L D I N G ||==========================================

class Holding : public BlackCard
{
protected:

  const size_t harvestValue;     

public:
    
  Holding(const std::string & name , const size_t & cost , const size_t & harvestValue);

  virtual void print() const; // isws den xreiazontai prints sta mines :shrug: (alla mallon xreiazontai)
};

//==========================================|| M I N E ||==========================================

class Mine : public Holding
{
  Holding * upperHolding;

public:
    
  Mine(const std::string & name = "Mine", const size_t & cost = 5 , const size_t & harvestValue = 3);
  ~Mine();

  void print() const;
};

//==========================================|| C R Y S T A L  M I N E ||==========================================
// ligo malakia pou exw mia oloidia class me allo onoma enos member alla nta3 ugeia
class CrystalMine : public Holding
{
  Holding * subHolding;

public:
    
  CrystalMine(const std::string & name , const size_t & cost , const size_t & harvestValue);
  ~CrystalMine();

  void print() const; 
};

//==========================================|| G O L D  M I N E ||==========================================

class GoldMine : public Holding
{
  Holding * upperHolding;
  Holding * subHolding;

public:
    
  GoldMine(const std::string & name , const size_t & cost , const size_t & harvestValue);  
  ~GoldMine();

  void print() const;
};

//==========================================|| S T R O N G H O L D ||==========================================

class StrongHold : public Holding
{
  const size_t initHonor;
  const size_t initDefence;
/*  const size_t initMoney; == harvest apo base class */
public:
    
  StrongHold();

  const size_t & getInitHonor() { return initHonor; }

  void print() const;
};

//==========================================|| P R O V I N C E ||==========================================
class Province
{
  bool isBroken; // init as false

  BlackCard *card;

public:

  Province(BlackCard *);
  ~Province();

  bool checkBroken() const { return isBroken; }
  void setBroken() { isBroken = true; }

  BlackCard * getCard() { return card; }
 
  void print() const;

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
  const std::string userName;

  StrongHold *strongHold;

  const size_t honor;
  
  size_t activeProvinces;

  queue <GreenCard *> * fateDeck;
  queue <BlackCard *> * dynastyDeck;

  vector <GreenCard *>   * hand;
  vector <Holding *>     * holdings;
  vector <Personality *> * army;

  vector <Province *>    * provinces;

public:

  Player(const std::string & userName , StrongHold * stronghold );
  ~Player();

  size_t getHonor() const { return honor; }

  size_t getProvincesNum() const { return activeProvinces; }

  const std::string& getUserName() const { return userName; }
  
  queue <GreenCard *>    * getFateDeck() { return fateDeck; }
  queue <BlackCard *>    * getDynastyDeck() { return dynastyDeck; }
  vector <GreenCard *>   * getHand() { return hand; }
  vector <Province *>    * getProvinces() { return provinces; }
  vector <Personality *> * getArmy() { return army; }
  vector <Holding *>     * getHoldings() { return holdings; }

  void setFateDeck(queue<GreenCard *> * fDeck) { fateDeck = fDeck; }
  void setDynastyDeck(queue<BlackCard *> * dDeck) { dynastyDeck = dDeck; }

  StrongHold * getStrongHold() { return strongHold; }

  void print() const;
  void printHoldings() const;
  void printArmy() const;
  void printHand() const;
  void printProvinces() const;
};

//==========================================|| G A M E ||==========================================

class Game
{
  vector <Player *> * players;
 
  size_t checkWinningCondition(void);

  void startingPhase (Player *);
  void equipmentPhase(Player *);
  void battlePhase   (Player *);
  void economyPhase  (Player *);
  void finalPhase    (Player *);

public:

  Game(size_t numPlayers, size_t maxGreenCards, size_t maxBlackCards, size_t maxHand /*might need more, you're up*/);
  ~Game();

  void initGameBoard(vector <Player *> * players , size_t numPlayers , size_t maxGreenCards , size_t maxBlackCards);
  void printGameStats(void);
  void gameplay(void);
};

//==========================================|| E N D  O F  F I L E ||==========================================