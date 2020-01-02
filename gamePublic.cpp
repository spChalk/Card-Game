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

#include "baseClasses.h"
#include "rules.hpp"

using std::cout;  // an se enoxloun mporoume na ta vgaloume
using std::endl;

namespace {  // Namespace Start

#define NO_WINNER 0
// TODO : Kanonika o kwdikas twn templates paei se .h arxeio

// D stands for Deck's Cards. D can be GreenCard or BlackCard
// E stands for Enum. 
template <class D , typename E>
// Pushes <total> times , <D type> objects in the given <deck>
void pushNtimes(std::queue< D *> * deck , std::unordered_map<std::string , vector<size_t> >::iterator j ,const E type  , size_t total , size_t * times ) {

  size_t temp = total;
  while (temp--)
  {
    if (j->second.size() == 6) {  // Follower
      deck->push ((D *)new Follower (j->first , j->second[0] , j->second[1] , j->second[2] , j->second[3] , "Random Text" , j->second[4] , j->second[5] , (const enum FollowerType)type , total));
    }
    else if (j->second.size() == 7) {  // Item
      deck->push ((D *)new Item (j->second[6] , j->first , j->second[0] , j->second[1] , j->second[2] , j->second[3] , "Random Text" , j->second[4] , j->second[5] , (const enum ItemType)type , total));
    }
    else if (j->second.size() == 4) {  // Personality
      deck->push ((D *)new Personality (j->first , j->second[0] , j->second[1] , j->second[2] , j->second[3] , (const enum PersonalityType)type));
    }
    else if (j->second.size() == 2) {  // Holding
      deck->push ((D *)new Holding (j->first , j->second[0] , j->second[1] , (const enum HoldingType)type));
    }
    (*times)++;
  }
}

/* ========================================================================= */
bool playerCompare(Player *p1, Player *p2) {
  return (p1->getHonor() > p1->getHonor());
}

/* ========================================================================= */

std::unordered_map<std::string , vector<size_t> > * readAndMap (const std::string & fileName ) {
  std::unordered_map<std::string , vector<size_t> > * uMap = new std::unordered_map<std::string , vector<size_t> >;
  std::ifstream newFile (fileName);
  std::string name , num;

  if (newFile.is_open()) {
    
    while ( getline (newFile , num) ) {
      if (num.length() > 1) {
        name = num;
        continue;
      }
      (*uMap)[name].push_back(std::stoi(num));  
    }
    newFile.close();
  } else {
    std::cout << "Couldn't open file ." << std::endl;
    exit(EXIT_FAILURE);
  }  
  return uMap;
}

/* ========================================================================= */

void deckBuilder (Player * pl , size_t maxGreenCards , size_t maxBlackCards) {
  std::unordered_map<std::string , vector<size_t> > * gMap = readAndMap("Personalities_and_Holdings.txt");
  std::unordered_map<std::string , vector<size_t> > * bMap = readAndMap("Followers_and_Weapons.txt");
  
  queue<GreenCard *> * fateDeck = new queue<GreenCard *>;
  queue<BlackCard *> * dynastyDeck = new queue<BlackCard *>;

  for (size_t i = 0; i < maxGreenCards; i++) {
    
    for (auto j = gMap->begin() ; j != gMap->end() ; j++ ) {

      if (j->first == "FOOTSOLDIER")
        pushNtimes(fateDeck , j , FOOTSOLDIER , NO_FOOTSOLDIER , &i );
      else if (j->first == "ARCHER")
        pushNtimes(fateDeck , j , ARCHER , NO_ARCHER , &i );
      else if (j->first == "SIEGER")
        pushNtimes(fateDeck , j , SIEGER , NO_SIEGER , &i );
      else if (j->first == "CAVALRY")
        pushNtimes(fateDeck , j , CAVALRY , NO_CAVALRY , &i );
      else if (j->first == "NAVAL")
        pushNtimes(fateDeck , j , ATAKEBUNE , NO_NAVAL , &i );
      else if (j->first == "BUSHIDO")
        pushNtimes(fateDeck , j , BUSHIDO , NO_BUSHIDO , &i );
      else if (j->first == "KATANA")
        pushNtimes(fateDeck , j , KATANA , NO_KATANA , &i );
      else if (j->first == "SPEAR")
        pushNtimes(fateDeck , j , SPEAR , NO_SPEAR , &i );
      else if (j->first == "BOW")
        pushNtimes(fateDeck , j , BOW , NO_BOW , &i );
      else if (j->first == "NINJATO")
        pushNtimes(fateDeck , j , NINJATO , NO_NINJATO , &i );
      else if (j->first == "WAKIZASHI")
        pushNtimes(fateDeck , j , WAKIZASHI , NO_WAKIZASHI , &i );
  
    }
  }
  
  delete gMap;

  for (size_t i = 0; i < maxBlackCards; i++) {
    
    for (auto j = bMap->begin() ; j != bMap->end() ; j++ ) {

      if (j->first == "ATTACKER")
        pushNtimes(dynastyDeck , j , ATTACKER , NO_ATTACKING , &i );
      else if (j->first == "DEFENDER")
        pushNtimes(dynastyDeck , j , DEFENDER , NO_DEFENSIVE , &i );
      else if (j->first == "SHOGUN")
        pushNtimes(dynastyDeck , j , SHOGUN , NO_SHOGUN , &i );
      else if (j->first == "CHANCELLOR")
        pushNtimes(dynastyDeck , j , CHANCELLOR , NO_CHANCELLOR , &i );
      else if (j->first == "CHAMPION")
        pushNtimes(dynastyDeck , j , CHAMPION , NO_CHAMPION , &i );
      else if (j->first == "SOLO")
        pushNtimes(dynastyDeck , j , GIFT_N_FAVOUR , NO_SOLO , &i );
      else if (j->first == "PLAIN")
        pushNtimes(dynastyDeck , j , PLAIN , NO_PLAIN , &i );
      else if (j->first == "FARMS")
        pushNtimes(dynastyDeck , j , FARMLAND , NO_FARMS , &i );
      else if (j->first == "MINE")
        pushNtimes(dynastyDeck , j , MINE , NO_MINE , &i );
      else if (j->first == "GOLD_MINE")
        pushNtimes(dynastyDeck , j , GOLD_MINE , NO_GOLD_MINE , &i );
      else if (j->first == "CRYSTAL_MINE")
        pushNtimes(dynastyDeck , j , CRYSTAL_MINE , NO_CRYSTAL_MINE , &i );

    }
  }

  delete bMap;

  pl->setFateDeck(fateDeck);
  pl->setDynastyDeck(dynastyDeck);
}

} // NameSpace End

/* ========================================================================= */

BlackCard * Player::drawBlackCard(void) { // TODO : assert if empty
  BlackCard * tmp = dynastyDeck->front();
  dynastyDeck->pop();
  return tmp;
}

/* ========================================================================= */

Game::Game(size_t numPlayers, size_t maxGreenCards, size_t maxBlackCards, size_t maxHand /*might need more, you're up*/) {  
  
  players = new vector<Player *>;  // Create a new vector 
  
  initGameBoard(players , numPlayers , maxGreenCards , maxBlackCards);


}

/* ========================================================================= */

void Game::initGameBoard(vector <Player *> * players , size_t numPlayers ,size_t maxGreenCards , size_t maxBlackCards) {
  for (size_t i = 0 ; i < numPlayers ; i++) {

    StrongHold * newStrH = new StrongHold();  // Make StrongHold
          // Make player (assign name , StrongHold and honor(via StrongHold))
    Player * newPl = new Player("Player" + std::to_string(i) , newStrH );
          // Make fateDeck and dynastyDeck
    deckBuilder(newPl , maxGreenCards , maxBlackCards);
          // Make provinces
    vector<Province *> * provinces = new vector<Province *>;
    
    for (size_t i = 0; i < 4; i++) {
      Province * newPr = new Province(newPl->drawBlackCard());
      provinces->push_back(newPr);
    }
    
    players->push_back(newPl);
  }
}
/* ========================================================================= */


/* Plays the game. Terminates only when there's a winner *
 * TODO: Maybe add some violent termination feature ?    */
void Game::gameplay(void)
{
  std::sort(players->begin(), players->end(), playerCompare); // sort by honor // too lazy to PQ it

  size_t gameStatus = NO_WINNER;

  while(gameStatus == NO_WINNER)
  {
    for (auto *i : *players) // c-like != python...
    {
      cout << "Player's \'" << i->getUserName() << "\' turn!" << endl;

      startingPhase(i);
      equipmentPhase(i);
      battlePhase(i);

      if (gameStatus = checkWinningCondition())
        break;

      economyPhase(i);
      finalPhase(i);
    }
  }

  Player *winner = players->at(gameStatus-1);
  std::cout << "Player \'" << winner->getUserName() 
            << "\' just won the game!" << std::endl;
}

/* ========================================================================= */

/* Checks whether we have a winner                  *
 * Returns his place in the vector counting from 1  *
 * If no winner is found, returns 0                 */
size_t Game::checkWinningCondition(void)
{
  bool playersWithProvinces = 0;
  size_t pos;
  size_t ctr = 1;

  for (auto *i : *players) // if it doesn't work, it's this cr p
  {                         // cuz idk what i'm doing, auto is lazy af

    if (i->getProvincesNum() != 0)     /* If the player still has prov */
    { 
      if (playersWithProvinces == 1)  
        return NO_WINNER;    /* We already found another player with prov */
      else
      {
        playersWithProvinces = 1;
        pos = ctr;     /* Keep his position in the vector */
      }
    }
    ++ctr;
  }
  return pos;
}

/* ========================================================================= */