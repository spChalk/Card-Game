// Feel free to rename the file ;)
// I love camelCase

#include <iostream>
#include <vector>
#include <queue>

//==========================================|| C A R D ||==========================================

class Card
{
    const std::string name;
    
    const unsigned int cost;
    
    bool isTapped;

public:

    Card(/* args */);

    ~Card();
};

Card::Card(/* args */) {}

Card::~Card() {}

// Kalutera na mhn valoume ta panta ola const gt mporei na exoume 8emata meta 

//==========================================|| G R E E N  C A R D ||==========================================

class GreenCard : public Card
{
    float attackBonus;              /* I think bonuses are e.g  0,2 x attack . That's why they're floats */

    float defenceBonus;

    const unsigned int minHonor;

    std::string cardText;           /* Dunno if its const or not. We'll see */

    float effectBonus;

    const unsigned int effectCost;

public:
    
    GreenCard(/* args */);
    
    ~GreenCard();
};

GreenCard::GreenCard(/* args */) {}

GreenCard::~GreenCard() {}

//==========================================|| B L A C K  C A R D ||==========================================

class BlackCard : public Card
{
    bool isRevealed;

public:
    
    BlackCard(/* args */);
    
    ~BlackCard();
};

BlackCard::BlackCard(/* args */) {}

BlackCard::~BlackCard() {}

//==========================================|| F O L L O W E R ||==========================================

class Follower : public GreenCard
{

public:
    
    Follower(/* args */);
    
    ~Follower();
};

Follower::Follower(/* args */) {}

Follower::~Follower() {}

//==========================================|| I T E M ||==========================================

class Item : public GreenCard
{
    unsigned int durability;

public:
    
    Item(/* args */);
    
    ~Item();
};

Item::Item(/* args */) {}

Item::~Item() {}

//==========================================|| P E R S O N A L I T Y ||==========================================

class Personality : public BlackCard
{
    unsigned int attack;

    unsigned int defence;

    unsigned int honor;

    bool isDead;

    vector <Follower *> * followers;

    vector <Item *> * items;

public:
    
    Personality(/* args */);
    
    ~Personality();
};

Personality::Personality(/* args */) {}

Personality::~Personality() {}

//==========================================|| H O L D I N G ||==========================================

class Holding : public BlackCard
{
    float harvestValue;     

public:
    
    Holding(/* args */);
    
    ~Holding();
};

Holding::Holding(/* args */) {}

Holding::~Holding() {}

//==========================================|| M I N E ||==========================================

class Mine : public Holding
{
    Holding * upperHolding;

public:
    
    Mine(/* args */);
    
    ~Mine();
};

Mine::Mine(/* args */) {}

Mine::~Mine() {}

//==========================================|| C R Y S T A L  M I N E ||==========================================
// ligo malakia pou exw mia oloidia class me allo onoma enos member alla nta3 ugeia
class CrystalMine : public Holding
{
    Holding * subHolding;

public:
    
    CrystalMine(/* args */);
    
    ~CrystalMine();
};

CrystalMine::CrystalMine(/* args */) {}

CrystalMine::~CrystalMine() {}

//==========================================|| G O L D  M I N E ||==========================================

class GoldMine : public Holding
{
    Holding * upperHolding;
    Holding * subHolding;

public:
    
    GoldMine(/* args */);
    
    ~GoldMine();
};

GoldMine::GoldMine(/* args */) {}

GoldMine::~GoldMine() {}

//==========================================|| S T R O N G H O L D ||==========================================

class StrongHold : public Holding
{
    unsigned int initHonor;

    unsigned int initMoney;

    unsigned int initDefence;

public:
    
    StrongHold(/* args */);
    
    ~StrongHold();
};

StrongHold::StrongHold(/* args */) {}

StrongHold::~StrongHold() {}

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

Player::Player(/* args */) {}

Player::~Player() {}

//==========================================|| E N D  O F  F I L E ||==========================================