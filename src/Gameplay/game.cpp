/* gamePublic.cpp */
// [Χάρης] Note: σου προτείνω να γράψεις εδώ τα public functions
// της κλάσης Game και ξεχωριστά τα phases σου αλλά ό,τι 
// θες γενικά
#include <algorithm>  // sort
#include <cstddef>    // size_t
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

using std::cout;  // an se enoxloun mporoume na ta vgaloume
using std::endl;

namespace {  // Namespace Start

/* ========================================================================= */
// Finds and returns <size_t> number from a string
// Works for a single number (otherwise it'll return all numbers as a single one)
// If there's no number , -1 (size_t max) is returned 
size_t extractNumber(const std::string& str) {
  std::string newStr;
  for (char i : str) 
    if (isdigit(i) || 'i' == '0')
      newStr += i;
  return (newStr.size() != 0) ? std::stoi(newStr) : -1 ; 
}

std::shared_ptr < std::unordered_map<std::string , std::vector<size_t> > > readAndMap (const std::string & fileName ) {
  std::shared_ptr < std::unordered_map<std::string , std::vector<size_t> > > uMap = std::make_shared < std::unordered_map<std::string , std::vector<size_t> > >();
  std::ifstream newFile (fileName);
  std::string name , temp;
  size_t num;

  if (newFile.is_open()) {
    
    while ( getline (newFile , name) ) {
      num = extractNumber(name);
      if (num != (size_t)-1 ) 
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

void deckBuilder (std::shared_ptr<Player> pl , size_t maxGreenCards , size_t maxBlackCards) {
  std::shared_ptr < std::unordered_map<std::string , std::vector<size_t> > > bMap = readAndMap(PERS_HOLD_TXT_PATH); // defined in rules.hpp
  std::shared_ptr < std::unordered_map<std::string , std::vector<size_t> > > gMap = readAndMap(FLLW_ITEM_TXT_PATH);
  
  for (size_t i = 0; i < maxGreenCards; i++) {
    
    for (auto j = gMap->begin() ; j != gMap->end() ; j++ ) {

      if (j->first == "FOOTSOLDIER")
        pushNtimes(pl->getFateDeck() , j , FOOTSOLDIER , NO_FOOTSOLDIER , &i );
      else if (j->first == "ARCHER")
        pushNtimes(pl->getFateDeck() , j , ARCHER , NO_ARCHER , &i );
      else if (j->first == "SIEGER")
        pushNtimes(pl->getFateDeck() , j , SIEGER , NO_SIEGER , &i );
      else if (j->first == "CAVALRY")
        pushNtimes(pl->getFateDeck() , j , CAVALRY , NO_CAVALRY , &i );
      else if (j->first == "NAVAL")
        pushNtimes(pl->getFateDeck() , j , ATAKEBUNE , NO_NAVAL , &i );
      else if (j->first == "BUSHIDO")
        pushNtimes(pl->getFateDeck() , j , BUSHIDO , NO_BUSHIDO , &i );
      else if (j->first == "KATANA")
        pushNtimes(pl->getFateDeck() , j , KATANA , NO_KATANA , &i );
      else if (j->first == "SPEAR")
        pushNtimes(pl->getFateDeck() , j , SPEAR , NO_SPEAR , &i );
      else if (j->first == "BOW")
        pushNtimes(pl->getFateDeck() , j , BOW , NO_BOW , &i );
      else if (j->first == "NINJATO")
        pushNtimes(pl->getFateDeck() , j , NINJATO , NO_NINJATO , &i );
      else if (j->first == "WAKIZASHI")
        pushNtimes(pl->getFateDeck() , j , WAKIZASHI , NO_WAKIZASHI , &i );
  
    }
  }
  
  for (size_t i = 0; i < maxBlackCards; i++) {
    
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

    }
  }
}

/* ========================================================================= */

bool playerCompare(PlayerPtr p1, PlayerPtr p2) { // make sure this is descending order
  return (p1->getHonor() > p2->getHonor());
}

} // NameSpace End

/* ========================================================================= */

void Game::initGameBoard(PlayerListPtr players , size_t numPlayers ,size_t maxGreenCards , size_t maxBlackCards , size_t maxHand) {
  for (size_t i = 0 ; i < numPlayers ; i++) {

          // Make player (assign name , StrongHold and honor(via StrongHold))
    auto newPl = std::make_shared< Player >("Player" + std::to_string(i) );
          // Make fateDeck and dynastyDeck
    deckBuilder(newPl , maxGreenCards , maxBlackCards);
    
    for (size_t i = 0; i < maxHand / 2 ; i++) {           // As einai oi arxikes kartes sto xeri ises me to miso twn MAX , dunno
      newPl->getHand()->push_back(newPl->drawFateCard());
    }
    
    for (size_t i = 0; i < 4; i++) {
      ProvincePtr newPr = std::make_shared< Province >(newPl->drawBlackCard());
      newPl->getProvinces()->push_back(newPr);
      newPl->increaseProvinceNum();
    }
    
    players->push_back(newPl);
  }
}

/* ========================================================================= */

/* Plays the game. Terminates only when there's a winner *
 * TODO: Maybe add some violent termination feature ?    */
void Game::gameplay(void)
{
  //std::sort(players->begin(), players->end(), playerCompare); // sort by honor // too lazy to PQ it
  players->sort(playerCompare);

  size_t win = 0;

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

Game::Game(size_t numPlayers, size_t maxGreenCards, size_t maxBlackCards, size_t maxHand /*might need more, you're up*/) {  
  
  players = std::make_shared< std::list <PlayerPtr> >();  // Create a new list 
  
  initGameBoard(players , numPlayers , maxGreenCards , maxBlackCards , maxHand);
  
  printGameStatistics();
  
  gameplay(); 
}

/* ========================================================================= */

/* Checks whether we have a winner                  *
 * Returns his place in the list counting from 1  *
 * If no winner is found, returns 0 (NO_WINNER)     */
size_t Game::checkWinningCondition(void)
{
  bool playersWithProvinces = 0;
  size_t pos;
  size_t ctr = 1;

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