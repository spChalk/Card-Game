//======|| GAME :: FINAL PHASE ||======
//TODO: change the the handling of MAX_HAND_CARDS define
#include <iostream>
#include <vector>

#include "baseClasses.h"
#include "rules.hpp" // temp

using std::cout;
using std::endl;

/* ========================================================================= */

static void discardSurplusFateCards (Player * pl , size_t numOfCards)
{ // could be a method of class Player, since MAX_HAND_CARDS *will* also be a field
  while (numOfCards > 0)
  {
    cout << "Player : " << pl->getUserName() << " has to discard "
         << numOfCards << " Fate Cards from their hand!" << endl;

    cout << "\nPrinting hand!" << endl;
    pl->printHand();
  
    cout << "\nType 'Y' (YES) or '<any other key>' (NO) after each card's \
    appearance, to discard it." << endl;

    for (auto card = pl->getHand()->begin(); card != pl->getHand()->end(); )
    {
      (*card)->print();
      cout << "\nDiscard?\n> Your answer: ";
      std::string answer;
      std::getline(std::cin, answer);
      cout << answer << endl;

      if (answer == "Y")
      {
        card = pl->getHand()->erase(card);
        cout << "Cards still to discard: " << --numOfCards << endl;
      }
      else
        ++card;
    }  
  }
}
/* ========================================================================= */

void Game::finalPhase(Player * pl)
{
  cout << "Final Phase Started !" << endl;

  if (pl->getHand()->size() > MAX_HAND_CARDS)
    discardSurplusFateCards(pl , pl->getHand()->size() - MAX_HAND_CARDS);

  cout << "Final Phase Ended !" << endl;

  printGameStatistics(); //[harry] everything about prints is included here
}
/* ========================================================================= */