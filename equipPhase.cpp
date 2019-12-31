//======|| EQUIPMENT PHASE IMPL ||======

// TODO : Na valw oles tis proupo8eseis agoras kartas 
// TODO : Upgrade Cards
// [Harry]: TODO: na valw orismata sta tou namespace + accessors sto baseClasses.h

#include <iostream>
#include <vector>
#include "baseClasses.h"

using std::cout;
using std::endl;

namespace // namespace_start
{

bool hasEnoughMoney();
bool hasEnoughHonor();
bool hasntReachedLimit();

}; // namespace_end

void Follower::attachToPersonality (Personality * pers) {
  pers->getFollowers()->push_back(this);
}

void Item::attachToPersonality (Personality * pers) {
  pers->getItems()->push_back(this);
}
/* ========================================================================= */

void Game::equipmentPhase (Player * pl) {
  cout << "Equipment Phase Started !" << endl;

  cout << "Printing Army!" << endl;
  pl->printArmy();
  
  cout << "Printing Hand!" << endl;
  pl->printHand();

  cout << "Type 'Y' (YES) or '<any other key>' (NO) after each card's \
appearance if you want to enhance the card's attributes!" << endl;

  for (auto * pers : *(pl->getArmy())) 
  {
    pers->print();
    cout << "Equip this Personality ?\n> Your answer : ";
    std::string answer;
    std::getline(std::cin, answer);
    cout << answer << endl;

    if (answer != "Y") continue;

    cout << "Cards in Hand :" << endl;
    for (auto * card : *(pl->getHand()))
    {
      card->print();
      cout << endl <<"Proceed to purchase ?\n> Your answer: ";
      std::getline(std::cin , answer);
      cout << answer << endl;

      if (answer != "Y") continue;

      //if (pl->makePurchase(it->getCost()) == true && /*minHonor*/ && /* < MAX_CARDS_PER_PERS */)
      if (hasEnoughMoney() && hasEnoughHonor() && hasntReachedLimit())
      {
        cout << "Purchase Completed ! " << endl;
        card->attachToPersonality(pers);
    
        cout << "Do you also want to upgrade this card ?\n> Your answer: ";
        std::getline(std::cin , answer);
        cout << answer << endl;

        if (answer == "Y") {
          //TODO : upgrade card
        }
      }
      //else 
      //  cout << "You do not have enough money for purchase . . ." << endl;
    }  
  }

  cout << "Equipment Phase Ended !" << endl;
}