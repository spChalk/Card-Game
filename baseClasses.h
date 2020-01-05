/* baseClasses.h */
#ifndef BASE_CLASSES_0
#define BASE_CLASSES_0
// I love camelCase // :|
/* Declarations */ // also works as an index :)
class Game;
class Player;
class Card;
class GreenCard;
class BlackCard;

class Personality;
class Province;
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
#include <list>
#include <unordered_map>
#include <memory>
#include <vector>


// using std::list;
// using std::queue;

typedef std::shared_ptr< Mine >        MinePtr;
typedef std::shared_ptr< Player >      PlayerPtr;
typedef std::shared_ptr< GoldMine >    GoldMinePtr;
typedef std::shared_ptr< CrystalMine > CrystalMinePtr;
typedef std::shared_ptr< GreenCard >   GreenCardPtr;
typedef std::shared_ptr< BlackCard >   BlackCardPtr;
typedef std::shared_ptr< StrongHold >  StrongHoldPtr;
typedef std::shared_ptr< Holding >     HoldingPtr;
typedef std::shared_ptr< Province >    ProvincePtr;
typedef std::shared_ptr< Personality > PersonalityPtr;

typedef std::shared_ptr< std::queue <GreenCardPtr > >    FateDeckPtr;
typedef std::shared_ptr< std::queue <BlackCardPtr > >    DynastyDeckPtr;
typedef std::shared_ptr< std::list <GreenCardPtr > >   HandPtr;
typedef std::shared_ptr< std::list <ProvincePtr > >    ProvinceListPtr;
typedef std::shared_ptr< std::list <PersonalityPtr > > ArmyPtr;
typedef std::shared_ptr< std::list <HoldingPtr > >     HoldingListPtr;
typedef std::shared_ptr< std::list <PlayerPtr > >      PlayerListPtr;

typedef std::shared_ptr< std::list <std::shared_ptr< Item>>>    ItemListPtr;
typedef std::shared_ptr< std::list <std::shared_ptr<Follower>>> FollowerListPtr;








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


void printF (const std::string & s , const size_t & colour = 37, const size_t & format = 0 );

//temp
#include "cards.h"
#include "greenCards.h"
#include "blackCards.h"
#include "player.h"
#include "game.h"

//===================================|| T E M P L A T E  F U N C T I O N ||===================================

// D stands for Deck's Cards. D can be GreenCard or BlackCard
// E stands for Enum. 
template <class D , typename E>
// Pushes <total> times , <D type> objects in the given <deck>
void pushNtimes(std::shared_ptr < std::queue< std::shared_ptr < D > > > deck , std::unordered_map<std::string , std::vector<size_t> >::iterator j ,const E type  , size_t total , size_t * times ) {

  size_t temp = total;
  while (temp--)
  {
    if (j->second.size() == 6) {  // Follower
      deck->push (std::dynamic_pointer_cast<D>( std::make_shared< Follower >(j->first , j->second[0] , j->second[1] , j->second[2] , j->second[3] , "Random Text" , j->second[4] , j->second[5] , (const enum FollowerType)type , total) ) );
    }
    else if (j->second.size() == 7) {  // Item
      deck->push (std::dynamic_pointer_cast<D>(std::make_shared< Item >(j->second[6] , j->first , j->second[0] , j->second[1] , j->second[2] , j->second[3] , "Random Text" , j->second[4] , j->second[5] , (const enum ItemType)type , total)));
    }
    else if (j->second.size() == 4) {  // Personality
      deck->push (std::dynamic_pointer_cast<D>(std::make_shared< Personality >(j->first , j->second[0] , j->second[1] , j->second[2] , j->second[3] , (const enum PersonalityType)type)));
    }
    else if (j->second.size() == 2) {  // Holding
        if (j->first == "MINE")
          deck->push (std::dynamic_pointer_cast<D>(std::make_shared < Mine >()));  
        else if (j->first == "GOLD_MINE")
          deck->push (std::dynamic_pointer_cast<D>(std::make_shared < GoldMine >()));
        else if (j->first == "CRYSTAL_MINE")
          deck->push (std::dynamic_pointer_cast<D>(std::make_shared < CrystalMine >()));    
        else 
          deck->push (std::dynamic_pointer_cast<D>(std::make_shared < Holding >(j->first , j->second[0] , j->second[1] , (const enum HoldingType)type)));
    }
    (*times)++;
  }
}



//==========================================|| E N D  O F  F I L E ||==========================================
#endif