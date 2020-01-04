/* startingPhase.cpp */
// TODO: disguss whether drawFateCard / revealProvinces 
// should be of class Player
#include <iostream>
#include <queue>
#include <vector>

#include "baseClasses.h"

using std::cout;
using std::endl;

namespace // namespace_begin
{

void untapEverything(PlayerPtr);
void drawFateCard(PlayerPtr);
void revealProvinces(PlayerPtr);

/* ========================================================================= */

void untapEverything(PlayerPtr player)
{
  auto holdings = player->getHoldings();
  auto army     = player->getArmy();

  for (auto i : *holdings)
    i->setUnTapped();

  for (auto i : *army)
    i->setUnTapped();

  player->getStrongHold()->setUnTapped();

  cout << "Everything is now untapped!" << endl;
}

/* ========================================================================= */

void revealProvinces(PlayerPtr player)
{
  auto provinces = player->getProvinces();

  for (auto i : *provinces)
  {
    if (i->checkBroken() == false)
      i->getCard()->setRevealed();
  }

  cout << "Provinces revealed!" <<endl;
}

/* ========================================================================= */
void drawFateCard(PlayerPtr player) // take care if empty fate deck!
{
  auto fate = player->getFateDeck();

  if (fate->size() > 0)
  {
    auto hand = player->getHand();

    hand->push_back(fate->front());
    fate->pop();

    cout << "Player \'" << player->getUserName() 
              << "\' just drew a fate card!" <<endl;
  }
  else
  {
    cout << "Fate deck is empty! No more Green Cards for player \'" 
              << player->getUserName() << "\' !" <<endl;
  }
}

}; // namespace_end
/* ========================================================================= */

void Game::startingPhase (PlayerPtr player)
{
  untapEverything(player);
  drawFateCard(player);
  revealProvinces(player);
  player->printHand();
  player->printProvinces();
}
/* ========================================================================= */
