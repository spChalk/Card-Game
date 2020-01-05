
#ifndef BASIC_HEADER_0
#define BASIC_HEADER_0

/* Standard headers */
#include <cstddef> // size_t
#include <list>
#include <memory>  // smart pointers
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

/* Declarations */
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

/* Typedefs */
typedef std::shared_ptr <Player>      PlayerPtr;

typedef std::shared_ptr <GreenCard>   GreenCardPtr;
typedef std::shared_ptr <BlackCard>   BlackCardPtr;

typedef std::shared_ptr <Item>        ItemPtr;
typedef std::shared_ptr <Follower>    FollowerPtr;

typedef std::shared_ptr <Mine>        MinePtr;
typedef std::shared_ptr <GoldMine>    GoldMinePtr;
typedef std::shared_ptr <CrystalMine> CrystalMinePtr;
typedef std::shared_ptr <StrongHold>  StrongHoldPtr;
typedef std::shared_ptr <Holding>     HoldingPtr;
typedef std::shared_ptr <Province>    ProvincePtr;
typedef std::shared_ptr <Personality> PersonalityPtr;

typedef std::shared_ptr < std::queue <GreenCardPtr > > FateDeckPtr;
typedef std::shared_ptr < std::queue <BlackCardPtr > > DynastyDeckPtr;

typedef std::shared_ptr < std::list <PlayerPtr> >      PlayerListPtr;
typedef std::shared_ptr < std::list <PersonalityPtr> > ArmyPtr;
typedef std::shared_ptr < std::list <GreenCardPtr> >   HandPtr;
typedef std::shared_ptr < std::list <ProvincePtr> >    ProvinceListPtr;
typedef std::shared_ptr < std::list <HoldingPtr> >     HoldingListPtr;

typedef std::shared_ptr < std::list <ItemPtr> >     ItemListPtr;
typedef std::shared_ptr < std::list <FollowerPtr> > FollowerListPtr;


//temp_start
#include "basicCards.h"
#include "greenCards.h"
#include "blackCards.h"
#include "player.h"
#include "game.h"
// end_temp
// 
#include "templateFunction.h"

void printF (const std::string & s , const size_t & colour = 37, const size_t & format = 0 );

#endif