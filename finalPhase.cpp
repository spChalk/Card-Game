//======|| GAME :: FINAL PHASE ||======
#include <iostream>
#include <vector>
#include "baseClasses.h"

static void discardSurplusFateCards (Player * pl , size_t numOfCards) {
    //TODO : kalutera na valw na kanei discard tis cards me to ligotero sumferon
    //              maybe a function pou mageireuei attack,defence & minHonor
    while (numOfCards--) pl->getHand()->pop_back();
}

void Game::finalPhase(Player * pl) {

  if (pl->getHand()->size() > MAX_HAND_CARDS)
    discardSurplusFateCards(pl , pl->getHand()->size() - MAX_HAND_CARDS);

  // printGameStatistics
  // printHand
  // printProvinces
  // printArena
  // printHoldings
}