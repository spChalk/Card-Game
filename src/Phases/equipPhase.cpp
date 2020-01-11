/* equipPhase.cpp */ // COMMENTS = OK
#include <iostream>
#include <string>

#include "basicHeader.hpp"

using std::cout;
using std::endl;

namespace // namespace_start
{

void upgradeGreenCard (PlayerPtr ,      GreenCardPtr );
bool hasEnoughMoney   (PlayerPtr ,      GreenCardPtr );
bool hasEnoughHonor   (PersonalityPtr , GreenCardPtr );
bool hasntReachedLimit(PersonalityPtr , GreenCardPtr );

/* ========================================================================= */
/* Player attempts to purchase an upgrade for a greencard. */
void upgradeGreenCard(PlayerPtr player, GreenCardPtr card)
{
  if (player->makePurchase(card->getEffectCost()) == true)  // Successful 
  {                                                         // Purchase
    card->upgrade();
    cout << "The selected GreenCard has been upgraded!\nNew stats:" << endl;
    card->print();
    cout << "Current amount of money: " << player->getCurrMoney() << endl;
  }
  else
    cout << "Not enough money to make the purchase.\nCurrent money: "
         << player->getCurrMoney() << "\nEffect cost: " 
         << card->getEffectCost()  << endl;
}
/* ========================================================================= */
/* Check whether a player has enough money to cover a greencard's cost */
bool hasEnoughMoney(PlayerPtr player, GreenCardPtr card)
{ 
  uint16_t currMoney = player->getCurrMoney();
  if (currMoney >= card->getCost()) 
    return true;

  return false;
}
/* ========================================================================= */
/* Check whether a personality has enough honor 
 * to cover a greencard's minimum honor required for attachment
 */
bool hasEnoughHonor(PersonalityPtr person, GreenCardPtr card)
{ 
  if (person->getHonor() >= card->getMinHonor())
    return true;

  return false;
}
/* ========================================================================= */
/* Check whether a personality hasn't reached the maximum number of a 
 * specific kind of attachments (i.e. an item type) already attached to them
 */
bool hasntReachedLimit(PersonalityPtr person, GreenCardPtr card)
{
  uint16_t maxCardPerPers = card->getMaxPerPersonality();

  if (card->getGreenCardType() == FOLLOWER)
  {
    FollowerPtr curr = std::dynamic_pointer_cast<Follower> (card);

    FollowerListPtr followers = person->getFollowers();

    for (auto i : *followers) /* Find all attachments of the same type */
    {
      if (i->getFollowerType() == curr->getFollowerType())
        --maxCardPerPers;

      if (maxCardPerPers == 0) 
        return false;          /* We've reached the limit */
    }
  }
  else // cardType == ITEM
  {
    ItemPtr curr = std::dynamic_pointer_cast<Item> (card);

    ItemListPtr items = person->getItems();

    for (auto i : *items)
    {
      if (i->getItemType() == curr->getItemType())
        --maxCardPerPers;
      
      if (maxCardPerPers == 0) 
          return false;
    }
  }

  return true;
}


}; // namespace_end


/* ========================================================================= */

void Game::equipmentPhase (PlayerPtr player)
{
  printF ("Equipment Phase Started !" , 1 , GRN , FILL);

  printF ("Printing " , 0 , MAG , BOLD); 
  cout << player->getUserName(); 
  printF ("'s Army!" , 1 , MAG , BOLD);
  player->printArmy();
  
  printF ("Printing " , 0 , MAG , BOLD); 
  cout << player->getUserName(); 
  printF ("'s Hand!" , 1 , MAG , BOLD);
  player->printHand();

  printF ("Type 'Y' (YES) or '<any other key>' (NO) after each card's \
appearance if you want to enhance the personality's attributes!" , 1 , WHT );

  for (auto pers : *(player->getArmy()))
  {                        /* Choose a personality from the army to equip */
    pers->print();
    cout << "Equip this Personality?\n> Your answer : ";
    std::string answer;
    std::getline(std::cin, answer);
    cout << endl;

    if (answer != "Y") continue;

    cout << "Printing Cards that are available for purchase in Hand :" << endl;
    for (auto card : *(player->getHand()))
    {                      /* Choose a greencard from the hand to equip */
      /* Check if a purchase can be made considering specific limitations */
      if ( hasEnoughMoney(player, card) 
        && hasEnoughHonor(pers, card)
        && hasntReachedLimit(pers, card))
      {
        card->print();
        cout << player->getUserName() <<"'s Current balance: " << player->getCurrMoney() << endl;

        cout << endl <<"Proceed to purchase?\n> Your answer: ";
        std::getline(std::cin , answer);
        cout << endl;

        if (answer != "Y") continue;

        player->makePurchase(card->getCost());  /* Make the purchase */

        card->attachToPersonality(pers);
        cout << "Purchase Completed ! " << endl;
    
        if (player->getCurrMoney() < card->getEffectCost()) continue;
        
        cout << "Current balance: " << player->getCurrMoney() << endl;
        cout << "Do you also want to upgrade this card ?\n> Your answer: ";
        std::getline(std::cin , answer);
        cout << endl;

        if (answer == "Y")          /* Attempt to upgrade the greencard */
          upgradeGreenCard(player, card);

        cout << player->getUserName() <<"'s Remaining money: " << player->getCurrMoney() << endl;
      }
    }
  }
  printF ("Equipment Phase Ended !" , 1 , GRN , FILL);
}
/* ========================================================================= */