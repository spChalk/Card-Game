/* game.cpp */
// TODO: set srand on line: 178 with std::time(0)
#include <algorithm> /* std::random_shuffle */
#include <cctype>    /* isdigit */
#include <ctime>     /* std::time */
#include <iostream>
#include <fstream>   /* std::ifstream */
#include <memory>    /* smart pointers */
#include <unordered_map>
#include <vector>

#include "basicHeader.hpp"
#include "blackCards.hpp"    /* enums */
#include "greenCards.hpp"    /* enums */
#include "rules.hpp" /* PERS_HOLD_TXT_PATH , FLLW_ITEM_TXT_PATH */

#define CARD_TXT_PATH "./src/Cards/proverbs.txt"

using std::cout;
using std::endl;

namespace {  // namespace_start

/* ========================================================================= */
/* Finds and returns <uint16_t> number from a string.
  Works for a single number (otherwise it will return all numbers included 
  in the string as a single one) . If there's no number , -1 (uint16_t max) is returned */
uint16_t extractNumber(const std::string& str) {
  std::string newStr;
  for (char i : str) 
    if (isdigit(i) || 'i' == '0')
      newStr += i;
  return (newStr.size() != 0) ? std::stoi(newStr) : -1 ; 
}

/* Reads a given file and returns an unordered map (Key type: string , Mapped Object : uint16_t vector) 
  consisting of its info */
std::shared_ptr < std::unordered_map<std::string , std::vector<uint16_t> > > readAndMap (const std::string & fileName ) {
  std::shared_ptr < std::unordered_map<std::string , std::vector<uint16_t> > > uMap = std::make_shared < std::unordered_map<std::string , std::vector<uint16_t> > >();
  std::ifstream newFile (fileName);
  std::string name , temp;
  uint16_t num;

  if (newFile.is_open()) {  /* Read the file */
    
    while ( getline (newFile , name) ) {  /* Get every line */
      num = extractNumber(name);          /* Extract the line's number */
      if (num != (uint16_t)-1 )           /* If there's a number , insert into map's vector */
        (*uMap)[temp].push_back(num);  
      else 
        temp = name;                      /* Else , save it as key value */
      }
    newFile.close();
  } else {
    cout << "Couldn't open file ." << endl;
    exit(EXIT_FAILURE);
  }  
  return uMap;
}

/* ========================================================================= */
std::shared_ptr < std::vector< std::string >> cardTxtVecPtr;  /* Vector of strings */
std::ifstream *cardtxt;

void readCardTxt()
{  
  std::string txt;

  if (cardtxt->is_open())
  {
    for (uint16_t i = 0; i != DECK_SIZE; ++i)
    {
      if (cardtxt->eof())  /* If we reached the end of the file */
      {                    /* rewind to the start */
        cardtxt->clear();
        cardtxt->seekg(0);
      }

      getline(*cardtxt, txt); /* Insert the text into vector */
      (*cardTxtVecPtr)[i] = txt;  
    }
  }
  else
  {
    cout << "Error proccessing card text file." << endl;
    exit(EXIT_FAILURE); 
  }

}
/* ========================================================================= */


void deckBuilder (std::shared_ptr<Player> pl , uint16_t maxGreenCards , uint16_t maxBlackCards) {
  std::shared_ptr < std::unordered_map<std::string , std::vector<uint16_t> > > bMap = readAndMap(PERS_HOLD_TXT_PATH);
  std::shared_ptr < std::unordered_map<std::string , std::vector<uint16_t> > > gMap = readAndMap(FLLW_ITEM_TXT_PATH);
  /* bMap contains all BlackCard info */
  /* gMap contains all GreenCard info */
  readCardTxt();

  for (uint16_t i = 0; i < maxGreenCards; i++) {
    /* Based on map's key values , form player's Fate Deck */
    for (auto j = gMap->begin() ; j != gMap->end() ; j++ ) {

      if (j->first == "FOOTSOLDIER")
        pushNtimes(pl->getFateDeck() , j , FollowerType::FOOTSOLDIER , NO_FOOTSOLDIER , i, MAX_FOOTSOLDIER_PER_PERS ,cardTxtVecPtr);
      else if (j->first == "ARCHER")
        pushNtimes(pl->getFateDeck() , j , FollowerType::ARCHER , NO_ARCHER , i , MAX_ARCHER_PER_PERS ,cardTxtVecPtr);
      else if (j->first == "SIEGER")
        pushNtimes(pl->getFateDeck() , j , FollowerType::SIEGER , NO_SIEGER , i , MAX_SIEGER_PER_PERS , cardTxtVecPtr);
      else if (j->first == "CAVALRY")
        pushNtimes(pl->getFateDeck() , j , FollowerType::CAVALRY , NO_CAVALRY , i , MAX_CAVALRY_PER_PERS , cardTxtVecPtr);
      else if (j->first == "NAVAL")
        pushNtimes(pl->getFateDeck() , j , FollowerType::ATAKEBUNE , NO_NAVAL , i , MAX_NAVAL_PER_PERS , cardTxtVecPtr);
      else if (j->first == "BUSHIDO")
        pushNtimes(pl->getFateDeck() , j , FollowerType::BUSHIDO , NO_BUSHIDO , i , MAX_BUSHIDO_PER_PERS , cardTxtVecPtr);
      else if (j->first == "KATANA")
        pushNtimes(pl->getFateDeck() , j , ItemType::KATANA , NO_KATANA , i , MAX_KATANA_PER_PERS , cardTxtVecPtr);
      else if (j->first == "SPEAR")
        pushNtimes(pl->getFateDeck() , j , ItemType::SPEAR , NO_SPEAR , i , MAX_SPEAR_PER_PERS , cardTxtVecPtr);
      else if (j->first == "BOW")
        pushNtimes(pl->getFateDeck() , j , ItemType::BOW , NO_BOW , i , MAX_BOW_PER_PERS , cardTxtVecPtr);
      else if (j->first == "NINJATO")
        pushNtimes(pl->getFateDeck() , j , ItemType::NINJATO , NO_NINJATO , i , MAX_NINJATO_PER_PERS , cardTxtVecPtr);
      else if (j->first == "WAKIZASHI")
        pushNtimes(pl->getFateDeck() , j , ItemType::WAKIZASHI , NO_WAKIZASHI , i , MAX_WAKIZASHI_PER_PERS , cardTxtVecPtr);
  
    }
  }
  
  std::random_shuffle(pl->getFateDeck()->begin(), pl->getFateDeck()->end());

  /* Based on map's key values , form player's Dynasty Deck */
  for (uint16_t i = 0; i < maxBlackCards; i++) {
    
    for (auto j = bMap->begin() ; j != bMap->end() ; j++ ) {

      if (j->first == "ATTACKER")
        pushNtimes(pl->getDynastyDeck() , j , PersonalityType::ATTACKER , NO_ATTACKING , i );
      else if (j->first == "DEFENDER")
        pushNtimes(pl->getDynastyDeck() , j , PersonalityType::DEFENDER , NO_DEFENSIVE , i );
      else if (j->first == "SHOGUN")
        pushNtimes(pl->getDynastyDeck() , j , PersonalityType::SHOGUN , NO_SHOGUN , i );
      else if (j->first == "CHANCELLOR")
        pushNtimes(pl->getDynastyDeck() , j , PersonalityType::CHANCELLOR , NO_CHANCELLOR , i );
      else if (j->first == "CHAMPION")
        pushNtimes(pl->getDynastyDeck() , j , PersonalityType::CHAMPION , NO_CHAMPION , i );
      else if (j->first == "SOLO")
        pushNtimes(pl->getDynastyDeck() , j , HoldingType::GIFT_N_FAVOUR , NO_SOLO , i );
      else if (j->first == "PLAIN")
        pushNtimes(pl->getDynastyDeck() , j , HoldingType::PLAIN , NO_PLAIN , i );
      else if (j->first == "FARMS")
        pushNtimes(pl->getDynastyDeck() , j , HoldingType::FARMLAND , NO_FARMS , i );
      else if (j->first == "MINE")
        pushNtimes(pl->getDynastyDeck() , j , HoldingType::MINE , NO_MINE , i );
      else if (j->first == "GOLD_MINE")
        pushNtimes(pl->getDynastyDeck() , j , HoldingType::GOLD_MINE , NO_GOLD_MINE , i );
      else if (j->first == "CRYSTAL_MINE")
        pushNtimes(pl->getDynastyDeck() , j , HoldingType::CRYSTAL_MINE , NO_CRYSTAL_MINE , i );
      else if (j->first == "STRONGHOLD") {
        StrongHoldPtr newStrH = std::make_shared<StrongHold>(j->second[0] , j->second[1] , j->first ,j->second[2]);
        pl->setStrongHold(newStrH);
      }

    }
  }

  std::random_shuffle(pl->getDynastyDeck()->begin(), pl->getDynastyDeck()->end());
}

}; // namespace_end

/* ========================================================================= */
/* Initialization of Game Board */
void Game::initGameBoard(PlayerListPtr players , uint16_t numPlayers ) {
  
  std::ifstream file(CARD_TXT_PATH);
  cardtxt = &file;
  cardTxtVecPtr = std::make_shared < std::vector< std::string >>(DECK_SIZE);

  std::srand(1); // TODO: Change it before finalisation // set as 1 to recreate bugs

  for (uint16_t i = 0 ; i < numPlayers ; i++) {  /* For every player */

    printF ("> Give username for player " , 0 , BLU , BOLD);
    cout << i+1 ;
    printF ("!\nUsername: " , 0 , BLU , BOLD);
    std::string username;
    std::getline(std::cin, username);
    cout << endl;
          /* Make player */
    PlayerPtr newPl = std::make_shared< Player >(username);
          /* Make player's FateDeck , DynastyDeck and StrongHold */
    deckBuilder(newPl , DECK_SIZE , DECK_SIZE);
          /* Form player's hand */
    for (uint16_t i = 0; i < MAX_HAND_CARDS / 2 ; i++) {           
      newPl->getHand()->push_back(newPl->drawFateCard());
    }
          /* Form player's provinces */
    for (uint16_t i = 0; i < 4; i++) {
      ProvincePtr newPr = std::make_shared< Province >(newPl->drawBlackCard());
      newPl->getProvinces()->push_back(newPr);
      newPl->increaseProvinceNum();
    }
    
    players->push_back(newPl);
  }
  cardtxt->close();
}

/* ========================================================================= */
namespace // namespace_continue
{

bool playerCompare(PlayerPtr p1, PlayerPtr p2) {  /* Make sure this is descending order */
  return (p1->getHonor() > p2->getHonor());
}

/* ========================================================================= */

uint16_t getNumOfPlayers()
{
  std::string answer;
  int num;

  while (true)
  {
    cout << "> Give the number of Players about to play the game!" << endl;
    
    std::getline(std::cin, answer);
    cout << endl;

    num = std::stoi(answer);

    if (num > 1) break;
  
    cout << "> Invalid number given! (" << num 
         << "). Please, give a positive integer greater than 1!" << endl;
  }

  return num;
}

}; // namespace_end

/* ========================================================================= */

/* Plays the game. Terminates only when there's a winner */
void Game::gameplay(void)
{
  //std::sort(players->begin(), players->end(), playerCompare); // sort by honor // too lazy to PQ it
  players->sort(playerCompare);

  uint16_t win = 0;

  while(win == 0) /* While no winner is found */
  {
    for (auto i : *players)
    {
      printF ("Player's \'" , 0 , CYN , BOLD); 
      cout << i->getUserName();
      printF ("\' turn!" , 1 , CYN , BOLD);
      printF ("Press ENTER to continue . . ." , 1);
      std::cin.clear();
      std::cin.sync();
      std::cin.get();

      /* Play all the phases */
      startingPhase(i);
      equipmentPhase(i);
      battlePhase(i);

      if ((win = checkWinningCondition()) != 0) /* We have a winner */
        break;

      economyPhase(i);
      finalPhase(i);

      // TODO:(maybe) Remove that when ready!
      std::string answer;
      cout << "Do you want to quit the game? Type 'Q' if YES or \
<any other key> if NO\n> Your answer: ";
      std::getline(std::cin , answer);
      cout << answer << endl;

      if (answer == "Q") return;
    }
  }
  /* Get Winner */
  PlayerPtr winner;
  for (auto i : *players)
  {
    --win;
    if (win == 0)
    {
      winner = i;
      break;
    }
  }
  //PlayerPtr winner = players->at(win-1);
  cout << "Player \'" << winner->getUserName() 
            << "\' just won the game!" << endl;
}

/* ========================================================================= */

Game::Game() {

  players = std::make_shared< std::list <PlayerPtr> >();  /* Create a new Player list */ 
  
  initGameBoard(players , getNumOfPlayers());
  
  printGameStatistics();
  
  gameplay(); 
}

/* ========================================================================= */

/* Checks whether we have a winner                  *
 * Returns his place in the list counting from 1    *
 * If no winner is found, returns 0 (NO_WINNER)     */
uint16_t Game::checkWinningCondition(void)
{
  bool playersWithProvinces = 0;
  uint16_t pos;
  uint16_t ctr = 1;

  for (auto i : *players) // if it doesn't work, it's this cr p
  {                         // cuz idk what i'm doing, auto is lazy af

    if (i->getProvincesNum() != 0)     /* If the player still has prov */
    { 
      if (playersWithProvinces == 1)  
        return 0;    /* We already found another player with prov */
      else
      {
        playersWithProvinces = 1;
        pos = ctr;     /* Keep his position in the list */
      }
    }
    ++ctr;
  }
  return pos;
}

/* ========================================================================= */