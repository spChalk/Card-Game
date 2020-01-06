/* startingPhase.cpp */
#include <iostream>
#include <queue>

#include "basicHeader.hpp"

using std::cout;
using std::endl;

namespace // namespace_begin
{

void untapEverything(PlayerPtr);
void drawFateCard   (PlayerPtr);
void revealProvinces(PlayerPtr);

/* ========================================================================= */

void untapEverything(PlayerPtr player)
{
  HoldingListPtr holdings = player->getHoldings();
  ArmyPtr army     = player->getArmy();

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
  ProvinceListPtr provinces = player->getProvinces();

  for (auto i : *provinces)
  {
    if (i->checkBroken() == false)
      i->getCard()->setRevealed();
  }

  cout << "Provinces revealed!" << endl;
}

/* ========================================================================= */
void drawFateCard(PlayerPtr player) // take care if empty fate deck!
{
  FateDeckPtr fate = player->getFateDeck();

  if (fate->empty() == false)
  {
    HandPtr hand = player->getHand();

    hand->push_back(player->drawFateCard());

    cout << "Player \'" << player->getUserName() 
              << "\' just drew a fate card!" << endl;
  }
  else
  {
    cout << "Fate deck is empty! No more Green Cards for player \'" 
              << player->getUserName() << "\' !" << endl;
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
