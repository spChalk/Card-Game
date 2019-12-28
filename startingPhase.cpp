/* startingPhase.cpp */
// TODO: printing functions
// TODO: drawFateCard : empty deck ?
#include <iostream>
#include <queue>
#include <vector>

#include "baseClasses.h"

static void untapEverything(Player *);
static void drawFateCard(Player *);
static void revealProvinces(Player *);

static void printHand(Player *) {}  // T O D O
static void printProvinces(Player *) {} // T O D O

/* ========================================================================= */

static void untapEverything(Player *player)
{
  auto * holdings = player->getHoldings();
  auto * army     = player->getArmy();

  for (auto *i : *holdings)
    i->setUnTapped();

  for (auto *i : *army)
    i->setUnTapped();

  player->getStrongHold()->setUnTapped();

  std::cout << "Everything is now untapped!" << std::endl;
}

/* ========================================================================= */

static void revealProvinces(Player *player)
{
  auto * provinces = player->getProvinces();

  for (auto *i : *provinces)
    i->setRevealed();

  std::cout << "Provinces revealed!" << std::endl;
}

/* ========================================================================= */
static void drawFateCard(Player *player) // TODO: take care if empty fate deck!
{
  auto * fate = player->getFateDeck();
  auto * hand = player->getHand();

  hand->push_back(fate->front());
  fate->pop();

  std::cout << "Player \'" << player->getUserName() 
            << "\' just drew a fate card!" << std::endl;
}

/* ========================================================================= */

void Game::startingPhase (Player *player)
{
  untapEverything(player);
  drawFateCard(player);
  revealProvinces(player);
  printHand(player);
  printProvinces(player);
}
/* ========================================================================= */
