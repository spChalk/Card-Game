//======|| EQUIPMENT PHASE IMPL ||======

#include <iostream>
// #include <vector>

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

void upgradeGreenCard(PlayerPtr player, GreenCardPtr card)
{
  size_t currMoney = player->getCurrMoney();
  if (currMoney >= card->getEffectCost())
  {
    player->makePurchase(card->getEffectCost()); // TODO: interactive (makePurchase in general)
    card->upgrade();
    cout << "The selected GreenCard has been upgraded!\nNew stats:" << endl;
    card->print();
    cout << "Current amount of money: " << player->getCurrMoney() << endl;
  }
  else
    cout << "Not enough money to make the purchase.\nCurrent money: "
         << currMoney << "\nEffect cost: " << card->getEffectCost() << endl;
}
/* ========================================================================= */

bool hasEnoughMoney(PlayerPtr player, GreenCardPtr card)
{ 
  size_t currMoney = player->getCurrMoney();
  if (currMoney >= card->getCost()) 
    return true;

  cout << "Not enough money to buy this card!\nMoney available: "
       << currMoney << "\nCard Cost: " << card->getCost() << endl;
  return false;
}
/* ========================================================================= */

bool hasEnoughHonor(PersonalityPtr person, GreenCardPtr card)
{ 
  if (person->getHonor() >= card->getMinHonor())
    return true;

  cout << "Not enough honor to buy this card!\nPersonality's current honor: "
       << person->getHonor() << "\nCard minimum honor: " << card->getMinHonor()
       << endl;
  return false;
}
/* ========================================================================= */

bool hasntReachedLimit(PersonalityPtr person, GreenCardPtr card)
{
  size_t maxCardPerPers = card->getMaxPerPersonality();
  enum GreenCardType cardType = card->getGreenCardType();

  if (cardType == FOLLOWER)
  {
    FollowerPtr curr = std::dynamic_pointer_cast<Follower> (card);

    FollowerListPtr followers = person->getFollowers();
    for (auto i : *followers)
    {

      if (i->getFollowerType() == curr->getFollowerType())
        --maxCardPerPers;
      
      if (maxCardPerPers == 0) break;
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
      
      if (maxCardPerPers == 0) break;
    }
  }

  if (maxCardPerPers == 0)
  {
    cout << "Personality is already fully equipped! \
Can't carry more equipment of this type!\nMax equipment \
of this type: " << card->getMaxPerPersonality() << endl;
    return false;  
  }

  return true;
}


}; // namespace_end


/* ========================================================================= */

void Game::equipmentPhase (PlayerPtr player)
{
  cout << "Equipment Phase Started !" << endl;

  cout << "Printing Army!" << endl;
  player->printArmy();
  
  cout << "Printing Hand!" << endl;
  player->printHand();

  cout << "Type 'Y' (YES) or '<any other key>' (NO) after each card's \
appearance if you want to enhance the card's attributes!" << endl;

  for (auto pers : *(player->getArmy())) 
  {
    pers->print();
    cout << "Equip this Personality ?\n> Your answer : ";
    std::string answer;
    std::getline(std::cin, answer);
    cout << answer << endl;

    if (answer != "Y") continue;

    cout << "Cards in Hand :" << endl;
    for (auto card : *(player->getHand()))
    {
      card->print();
      cout << endl <<"Proceed to purchase ?\n> Your answer: ";
      std::getline(std::cin , answer);
      cout << answer << endl;

      if (answer != "Y") continue;

      //if (player->makePurchase(it->getCost()) == true && /*minHonor*/ && /* < MAX_CARDS_PER_PERS */)
      if ( hasEnoughMoney(player, card) 
        && hasEnoughHonor(pers, card) 
        && hasntReachedLimit(pers, card))
      {
        player->makePurchase(card->getCost());

        card->attachToPersonality(pers);
        cout << "Purchase Completed ! " << endl;
    
        cout << "Do you also want to upgrade this card ?\n> Your answer: ";
        std::getline(std::cin , answer);
        cout << answer << endl;

        if (answer == "Y") upgradeGreenCard(player, card);

        cout << "Remaining money: " << player->getCurrMoney() << endl;
      }
    }
  }

  cout << "Equipment Phase Ended !" << endl;
}
/* ========================================================================= */