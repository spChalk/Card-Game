/* startingPhase.cpp */
// TODO: disguss whether drawFateCard / revealProvinces 
// should be of class Player
#include <iostream>
#include <queue>
#include <vector>

#include "baseClasses.h"

namespace // namespace_begin
{

void untapEverything(std::shared_ptr<Player >);
void drawFateCard(std::shared_ptr<Player >);
void revealProvinces(std::shared_ptr<Player >);

/* ========================================================================= */

void untapEverything(std::shared_ptr<Player > player)
{
  auto holdings = player->getHoldings();
  auto army     = player->getArmy();

  for (auto i : *holdings)
    i->setUnTapped();

  for (auto i : *army)
    i->setUnTapped();

  player->getStrongHold()->setUnTapped();

  std::cout << "Everything is now untapped!" << std::endl;
}

/* ========================================================================= */

void revealProvinces(std::shared_ptr<Player > player)
{
  auto provinces = player->getProvinces();

  for (auto i : *provinces)
  {
    if (i->checkBroken() == false)
      i->getCard()->setRevealed();
  }

  std::cout << "Provinces revealed!" << std::endl;
}

/* ========================================================================= */
void drawFateCard(std::shared_ptr<Player > player) // take care if empty fate deck!
{
  auto fate = player->getFateDeck();

  if (fate->size() > 0)
  {
    auto hand = player->getHand();

    hand->push_back(fate->front());
    fate->pop();

    std::cout << "Player \'" << player->getUserName() 
              << "\' just drew a fate card!" << std::endl;
  }
  else
  {
    std::cout << "Fate deck is empty! No more Green Cards for player \'" 
              << player->getUserName() << "\' !" << std::endl;
  }
}

}; // namespace_end
/* ========================================================================= */

void Game::startingPhase (std::shared_ptr<Player > player)
{
  untapEverything(player);
  drawFateCard(player);
  revealProvinces(player);
  player->printHand();
  player->printProvinces();
}
/* ========================================================================= */
