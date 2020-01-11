/* startingPhase.cpp */ // COMMENTS = OK
#include <iostream>

#include "basicHeader.hpp"

using std::cout;
using std::endl;

namespace // namespace_start
{

void untapEverything(PlayerPtr);
void drawFateCard   (PlayerPtr);
void revealProvinces(PlayerPtr);

/* ========================================================================= */
 /* Untap every holding/personality a player owns */
void untapEverything(PlayerPtr player)
{
  HoldingListPtr holdings = player->getHoldings();
  ArmyPtr        army     = player->getArmy();

  for (auto i : *holdings)
    i->setUnTapped();

  for (auto i : *army)
    i->setUnTapped();

  player->getStrongHold()->setUnTapped();

  printF ("Everything is now untapped!" , 1 , MAG , FILL);
}

/* ========================================================================= */
/* Reveal every hidden province of a player */
void revealProvinces(PlayerPtr player)
{
  ProvinceListPtr provinces = player->getProvinces();

  for (auto i : *provinces)
  {
    if (i->checkBroken() == false) /* If the province isn't broken */
      i->getCard()->setRevealed();
  }

  cout << "Revealed "<< player->getUserName() <<"'s Provinces !" << endl;
}

/* ========================================================================= */
/* Draw a fate card from the fate deck and place it @ the hand of the player.
 * If the fate deck is empty, do nothing.
 */
void drawFateCard(PlayerPtr player)
{
  FateDeckPtr fate = player->getFateDeck();

  if (fate->empty() == false)
  {
    HandPtr hand = player->getHand();

    hand->push_back(player->drawFateCard());

    printF ("Player \'" , 0 , MAG , FILL); 
    cout << player->getUserName(); 
    printF ("\' just drew a fate card!" , 1 , MAG , FILL);
  }
  else
  {
    printF ("Fate deck is empty! No more Green Cards for player \'" , 0 , MAG , FILL); 
    cout << player->getUserName();
    printF ("\' !" , 1 , MAG , FILL);
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
