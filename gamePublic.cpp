/* gamePublic.cpp */
// [Χάρης] Note: σου προτείνω να γράψεις εδώ τα public functions
// της κλάσης Game και ξεχωριστά τα phases σου αλλά ό,τι 
// θες γενικά
#include <algorithm>  // sort
#include <cstddef>    // size_t
#include <iostream>
#include <fstream>
#include <unordered_map>


#include "baseClasses.h"

using std::cout;  // an se enoxloun mporoume na ta vgaloume
using std::endl;

#define NO_WINNER 0

/* ========================================================================= */
static bool playerCompare(Player *p1, Player *p2) {
  return (p1->getHonor() > p1->getHonor());
}


static void deckBuilder (Player * pl , size_t maxGreenCards , size_t maxBlackCards) {
  std::unordered_map<std::string , size_t > * gMap = readAndMap("Personalities_and_Holdings.txt");
  std::unordered_map<std::string , size_t > * bMap = readAndMap("Followers_and_Weapons.txt");
  
  queue<GreenCard *> * fateDeck = new queue<GreenCard *>;
  queue<BlackCard *> * dynastyDeck = new queue<BlackCard *>;

  for (size_t i = 0; i < maxGreenCards; i++) {
    
    for (size_t j = 0 ; j < gMap->bucket_count() ; j++) {
      
      if (gMap->bucket_size(j) == 6) {
        Follower * newFollower = new Follower(/* args */);
        fateDeck->push(newFollower);
      } else {
        Item * newItem = new Item(/* args */);
        fateDeck->push(newItem);
      }
      i++;
    }
  }
  
  for (size_t i = 0; i < maxBlackCards; i++) {
    
    for (size_t j = 0 ; j < bMap->bucket_count() ; j++) {
      
      if (bMap->bucket_size(j) == 4) {
        Personality * newPers = new Personality(/* args */);
        dynastyDeck->push(newPers);
      } else {
        Holding * newHolding = new Holding(/* args */);
        dynastyDeck->push(newHolding);
      }
      i++;
    }
  }

  pl->setFateDeck(fateDeck);
  pl->setDynastyDeck(dynastyDeck);

  delete gMap;
  delete bMap;
}

/* ========================================================================= */

std::unordered_map<std::string , size_t> * readAndMap (const std::string & fileName ) {
  std::unordered_map<std::string , size_t > * uMap = new std::unordered_map<std::string , size_t>;
  std::ifstream newFile (fileName);
  std::string name , num;

  if (newFile.is_open()) {
    getline (newFile , name); // Maybe add assertion for safety checking
    
    while ( getline (newFile , num) ) {
      if (num.length() > 1) {
        name = num;
        continue;
      }
      (*uMap)[name] = std::stoi(num);  
    }
    newFile.close();
  } else {
    std::cout << "Couldn't open file ." << std::endl;
    exit(EXIT_FAILURE);
  }  
  return uMap;
}

/* ========================================================================= */

Game::Game(size_t numPlayers, size_t maxGreenCards, size_t maxBlackCards, size_t maxHand /*might need more, you're up*/) {  
  
  players = new vector <Player *>;  // Create a new vector 
  
  initGameBoard(players , numPlayers , maxGreenCards , maxBlackCards);


}

Game::~Game() { delete players; }

void Game::initGameBoard(vector<Player *> * players , size_t numPlayers ,size_t maxGreenCards , size_t maxBlackCards) {
  for (size_t i = 0 ; i < numPlayers ; i++) {
    StrongHold * newStrH = new StrongHold(/* args */);
    // Make Provinces
    Player * newPl = new Player("Player" + std::to_string(i) , newStrH , /* provinces*/);
    deckBuilder(newPl , maxGreenCards , maxBlackCards);
    players->push_back(newPl);
  }
} 




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