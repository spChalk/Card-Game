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
    printF ("Player : " , 0 , MAG , BOLD);
    cout << pl->getUserName();
    printF (" has to discard " , 0 , MAG , BOLD);
    cout << numOfCards;
    printF (" Fate Cards from their hand!" , 1 , MAG , BOLD);

    printF ("\nPrinting hand!" , 1 , MAG);
    pl->printHand();
  
    printF ("\nType 'Y' (YES) or '<any other key>' (NO) after each card's \
appearance, to discard it." , 1 , MAG , BOLD);

    for (auto card = pl->getHand()->begin(); card != pl->getHand()->end(); )
    {
      (*card)->print();
      printF ("\nDiscard?\n> Your answer: " , 0 , MAG , BOLD);
      std::string answer;
      std::getline(std::cin, answer);
      cout << endl;

      if ((answer == "Y")||(answer == "y"))
      {
        card = pl->getHand()->erase(card);
        printF ("Cards still to discard: " , 0 , MAG , BOLD);
        cout << --numOfCards << endl;
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
  printF ("Final Phase Started !" , 1 , CYN , FILL);
  printF ("Press ENTER to continue . . ." , 1);
  std::cin.clear();
  std::cin.sync();
  std::cin.get();

  int32_t extraCards = pl->getHand()->size() - MAX_HAND_CARDS;
  
  if (extraCards > 0)
    discardSurplusFateCards(pl , extraCards);

  printF ("Final Phase Ended !" , 1 , CYN , FILL);

  printGameStatistics(); /* All Final Phase prints are included here */
}
/* ========================================================================= */