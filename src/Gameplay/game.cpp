/* gamePublic.cpp */
// [Χάρης] Note: σου προτείνω να γράψεις εδώ τα public functions
// της κλάσης Game και ξεχωριστά τα phases σου αλλά ό,τι 
// θες γενικά
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <cassert>
#include <memory>
#include <cctype>
#include <vector>
// #include <limits>

#include "basicHeader.hpp"
#include "rules.hpp" // PERS_HOLD_TXT_PATH, FLLW_ITEM_TXT_PATH

#define CARD_TXT_PATH "./src/Cards/proverbs.txt"

using std::cout;  // an se enoxloun mporoume na ta vgaloume
using std::endl;

namespace {  // Namespace Start

/* ========================================================================= */
// Finds and returns <uint16_t> number from a string
// Works for a single number (otherwise it'll return all numbers as a single one)
// If there's no number , -1 (uint16_t max) is returned 
uint16_t extractNumber(const std::string& str) {
  std::string newStr;
  for (char i : str) 
    if (isdigit(i) || 'i' == '0')
      newStr += i;
  return (newStr.size() != 0) ? std::stoi(newStr) : -1 ; 
}

std::shared_ptr < std::unordered_map<std::string , std::vector<uint16_t> > > readAndMap (const std::string & fileName ) {
  std::shared_ptr < std::unordered_map<std::string , std::vector<uint16_t> > > uMap = std::make_shared < std::unordered_map<std::string , std::vector<uint16_t> > >();
  std::ifstream newFile (fileName);
  std::string name , temp;
  uint16_t num;

  if (newFile.is_open()) {
    
    while ( getline (newFile , name) ) {
      num = extractNumber(name);
      if (num != (uint16_t)-1 ) 
        (*uMap)[temp].push_back(num);  
      else 
        temp = name;
      }
    newFile.close();
  } else {
    cout << "Couldn't open file ." << endl;
    exit(EXIT_FAILURE);
  }  
  return uMap;
}

/* ========================================================================= */
std::shared_ptr < std::vector< std::string >> cardTxtVecPtr;
std::ifstream *cardtxt;

void readCardTxt()
{  
  std::string txt;

  if (cardtxt->is_open())
  {
    for (uint16_t i = 0; i != DECK_SIZE; ++i)
    {
      if (cardtxt->eof()) // if we reached the end of the file
      {                   // rewing to the start
        cardtxt->clear();
        cardtxt->seekg(0);
      }

      getline(*cardtxt, txt);
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
  std::shared_ptr < std::unordered_map<std::string , std::vector<uint16_t> > > bMap = readAndMap(PERS_HOLD_TXT_PATH); // defined in rules.hpp
  std::shared_ptr < std::unordered_map<std::string , std::vector<uint16_t> > > gMap = readAndMap(FLLW_ITEM_TXT_PATH);
  
  readCardTxt();

  for (uint16_t i = 0; i < maxGreenCards; i++) {
    
    for (auto j = gMap->begin() ; j != gMap->end() ; j++ ) {

      if (j->first == "FOOTSOLDIER")
        pushNtimes(pl->getFateDeck() , j , FOOTSOLDIER , NO_FOOTSOLDIER , &i, (*cardTxtVecPtr)[i]);
      else if (j->first == "ARCHER")
        pushNtimes(pl->getFateDeck() , j , ARCHER , NO_ARCHER , &i, (*cardTxtVecPtr)[i]);
      else if (j->first == "SIEGER")
        pushNtimes(pl->getFateDeck() , j , SIEGER , NO_SIEGER , &i, (*cardTxtVecPtr)[i]);
      else if (j->first == "CAVALRY")
        pushNtimes(pl->getFateDeck() , j , CAVALRY , NO_CAVALRY , &i, (*cardTxtVecPtr)[i]);
      else if (j->first == "NAVAL")
        pushNtimes(pl->getFateDeck() , j , ATAKEBUNE , NO_NAVAL , &i, (*cardTxtVecPtr)[i]);
      else if (j->first == "BUSHIDO")
        pushNtimes(pl->getFateDeck() , j , BUSHIDO , NO_BUSHIDO , &i, (*cardTxtVecPtr)[i]);
      else if (j->first == "KATANA")
        pushNtimes(pl->getFateDeck() , j , KATANA , NO_KATANA , &i, (*cardTxtVecPtr)[i]);
      else if (j->first == "SPEAR")
        pushNtimes(pl->getFateDeck() , j , SPEAR , NO_SPEAR , &i, (*cardTxtVecPtr)[i]);
      else if (j->first == "BOW")
        pushNtimes(pl->getFateDeck() , j , BOW , NO_BOW , &i, (*cardTxtVecPtr)[i]);
      else if (j->first == "NINJATO")
        pushNtimes(pl->getFateDeck() , j , NINJATO , NO_NINJATO , &i, (*cardTxtVecPtr)[i]);
      else if (j->first == "WAKIZASHI")
        pushNtimes(pl->getFateDeck() , j , WAKIZASHI , NO_WAKIZASHI , &i, (*cardTxtVecPtr)[i]);
  
    }
  }
  
  for (uint16_t i = 0; i < maxBlackCards; i++) {
    
    for (auto j = bMap->begin() ; j != bMap->end() ; j++ ) {

      if (j->first == "ATTACKER")
        pushNtimes(pl->getDynastyDeck() , j , ATTACKER , NO_ATTACKING , &i );
      else if (j->first == "DEFENDER")
        pushNtimes(pl->getDynastyDeck() , j , DEFENDER , NO_DEFENSIVE , &i );
      else if (j->first == "SHOGUN")
        pushNtimes(pl->getDynastyDeck() , j , SHOGUN , NO_SHOGUN , &i );
      else if (j->first == "CHANCELLOR")
        pushNtimes(pl->getDynastyDeck() , j , CHANCELLOR , NO_CHANCELLOR , &i );
      else if (j->first == "CHAMPION")
        pushNtimes(pl->getDynastyDeck() , j , CHAMPION , NO_CHAMPION , &i );
      else if (j->first == "SOLO")
        pushNtimes(pl->getDynastyDeck() , j , GIFT_N_FAVOUR , NO_SOLO , &i );
      else if (j->first == "PLAIN")
        pushNtimes(pl->getDynastyDeck() , j , PLAIN , NO_PLAIN , &i );
      else if (j->first == "FARMS")
        pushNtimes(pl->getDynastyDeck() , j , FARMLAND , NO_FARMS , &i );
      else if (j->first == "MINE")
        pushNtimes(pl->getDynastyDeck() , j , MINE , NO_MINE , &i );
      else if (j->first == "GOLD_MINE")
        pushNtimes(pl->getDynastyDeck() , j , GOLD_MINE , NO_GOLD_MINE , &i );
      else if (j->first == "CRYSTAL_MINE")
        pushNtimes(pl->getDynastyDeck() , j , CRYSTAL_MINE , NO_CRYSTAL_MINE , &i );
      else if (j->first == "STRONGHOLD") {
        StrongHoldPtr newStrH = std::make_shared<StrongHold>(j->second[0] , j->second[1] , j->first ,j->second[2]);
        pl->setStrongHold(newStrH);
      }

    }
  }
}

} // NameSpace End

/* ========================================================================= */

void Game::initGameBoard(PlayerListPtr players , uint16_t numPlayers ) {
  
  std::ifstream file(CARD_TXT_PATH);
  cardtxt = &file;
  cardTxtVecPtr = std::make_shared < std::vector< std::string >>(DECK_SIZE);

  for (uint16_t i = 0 ; i < numPlayers ; i++) {

    cout << "> Give username for player " << i+1 << "!\nUsername: ";
    std::string username;
    std::getline(std::cin, username);
    cout << endl;
          // Make player (assign name , StrongHold and honor(via StrongHold))
    auto newPl = std::make_shared< Player >(username);
          // Make fateDeck and dynastyDeck
    deckBuilder(newPl , DECK_SIZE , DECK_SIZE);
    
    for (uint16_t i = 0; i < MAX_HAND_CARDS / 2 ; i++) {           // As einai oi arxikes kartes sto xeri ises me to miso twn MAX , dunno
      newPl->getHand()->push_back(newPl->drawFateCard());
    }
    
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

bool playerCompare(PlayerPtr p1, PlayerPtr p2) { // make sure this is descending order
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

/* Plays the game. Terminates only when there's a winner *
 * TODO: Maybe add some violent termination feature ?    */
void Game::gameplay(void)
{
  //std::sort(players->begin(), players->end(), playerCompare); // sort by honor // too lazy to PQ it
  players->sort(playerCompare);

  uint16_t win = 0;

  while(win == 0) // while no winner is found
  {
    for (auto i : *players) // c-like != python...
    {
      cout << "Player's \'" << i->getUserName() << "\' turn!" << endl;

      startingPhase(i);
      equipmentPhase(i);
      battlePhase(i);

      if ((win = checkWinningCondition()) != 0) // we have a winner
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
  
  players = std::make_shared< std::list <PlayerPtr> >();  // Create a new list 
  
  initGameBoard(players , getNumOfPlayers());
  
  printGameStatistics();
  
  gameplay(); 
}

/* ========================================================================= */

/* Checks whether we have a winner                  *
 * Returns his place in the list counting from 1  *
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