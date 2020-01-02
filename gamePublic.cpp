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
        if (j->first == "MINE")
          deck->push ((D *)new Mine ());  
        else if (j->first == "GOLD_MINE")
          deck->push ((D *)new GoldMine ());
        else if (j->first == "CRYSTAL_MINE")
          deck->push ((D *)new CrystalMine ());    
        else 
          deck->push ((D *)new Holding (j->first , j->second[0] , j->second[1] , (const enum HoldingType)type));
    }
    (*times)++;
  }
}

/* ========================================================================= */

std::unordered_map<std::string , vector<size_t> > * readAndMap (const std::string & fileName ) {
  std::unordered_map<std::string , vector<size_t> > * uMap = new std::unordered_map<std::string , vector<size_t> >;
  std::ifstream newFile (fileName);
  std::string name , num;

  if (newFile.is_open()) {
    
    while ( getline (newFile , num) ) {
      if (num.length() > 2) {
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
  std::unordered_map<std::string , vector<size_t> > * bMap = readAndMap("Personalities_and_Holdings.txt");
  std::unordered_map<std::string , vector<size_t> > * gMap = readAndMap("Followers_and_Weapons.txt");
  
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
  
  delete gMap;

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
  
  delete bMap;
}

} // NameSpace End

/* ========================================================================= */

BlackCard * Player::drawBlackCard(void) { // TODO : assert if empty
  BlackCard * tmp = dynastyDeck->front();
  dynastyDeck->pop();
  return tmp;
}

/* ========================================================================= */

GreenCard * Player::drawFateCard(void) { // TODO : assert if empty
  GreenCard * tmp = fateDeck->front();
  fateDeck->pop();
  return tmp;
}

/* ========================================================================= */

void Game::initGameBoard(vector <Player *> * players , size_t numPlayers ,size_t maxGreenCards , size_t maxBlackCards , size_t maxHand) {
  for (size_t i = 0 ; i < numPlayers ; i++) {

          // Make player (assign name , StrongHold and honor(via StrongHold))
    Player * newPl = new Player("Player" + std::to_string(i) );
          // Make fateDeck and dynastyDeck
    deckBuilder(newPl , maxGreenCards , maxBlackCards);
    
    for (size_t i = 0; i < maxHand / 2 ; i++) {           // As einai oi arxikes kartes sto xeri ises me to miso twn MAX , dunno
      newPl->getHand()->push_back(newPl->drawFateCard());
    }
    
    for (size_t i = 0; i < 4; i++) {
      Province * newPr = new Province(newPl->drawBlackCard());
      newPl->getProvinces()->push_back(newPr);
      newPl->increaseProvinceNum();
    }
    
    players->push_back(newPl);
  }
}
/* ========================================================================= */

static bool playerCompare(Player *p1, Player *p2) { // make sure this is descending order
  return (p1->getHonor() > p2->getHonor());
}

/* ========================================================================= */

/* Plays the game. Terminates only when there's a winner *
 * TODO: Maybe add some violent termination feature ?    */
void Game::gameplay(void)
{
  std::sort(players->begin(), players->end(), playerCompare); // sort by honor // too lazy to PQ it

  size_t winPos;

  while(true) // while no winner is found
  {
    for (auto *i : *players) // c-like != python...
    {
      cout << "Player's \'" << i->getUserName() << "\' turn!" << endl;

      startingPhase(i);
      equipmentPhase(i);
      battlePhase(i);

      if ((winPos = checkWinningCondition()) != 0) // we have a winner
        break;

      economyPhase(i);
      finalPhase(i);
    }
  }

  Player *winner = players->at(winPos-1);
  std::cout << "Player \'" << winner->getUserName() 
            << "\' just won the game!" << std::endl;
}

/* ========================================================================= */

Game::Game(size_t numPlayers, size_t maxGreenCards, size_t maxBlackCards, size_t maxHand /*might need more, you're up*/) {  
  
  players = new vector<Player *>;  // Create a new vector 
  
  initGameBoard(players , numPlayers , maxGreenCards , maxBlackCards , maxHand);
  
  printGameStatistics();
  
  gameplay(); 
}

Game::~Game () { delete players; }

/* ========================================================================= */

/* Checks whether we have a winner                  *
 * Returns his place in the vector counting from 1  *
 * If no winner is found, returns 0 (NO_WINNER)     */
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
        return 0;    /* We already found another player with prov */
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