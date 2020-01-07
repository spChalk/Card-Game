/* finalPhase.cpp */ // COMMENTS = OK
#include <iostream>
#include <string>

#include "rules.hpp"  // MAX_HAND_CARDS
#include "basicHeader.hpp"

using std::cout;
using std::endl;

namespace {  // namespace_start

/* ========================================================================= */
/* Remove `numOfCards` cards from a player's hand.
 * Player decides which ones to remove.
 */ 
void discardSurplusFateCards (PlayerPtr pl , uint16_t numOfCards)
{
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
      cout << endl;

      if (answer == "Y")
      {
        card = pl->getHand()->erase(card);
        cout << "Cards still to discard: " << --numOfCards << endl;
      }
      else
        ++card;

      if (numOfCards == 0) break;
    }
  }
}

} // namespace_end 

/* ========================================================================= */

void Game::finalPhase(PlayerPtr pl)
{
  cout << "Final Phase Started !" << endl;

  int32_t extraCards = pl->getHand()->size() - MAX_HAND_CARDS;
  
  if (extraCards > 0)
    discardSurplusFateCards(pl , extraCards);

  cout << "Final Phase Ended !" << endl;

  printGameStatistics(); /* All Final Phase prints are included here */
}
/* ========================================================================= */