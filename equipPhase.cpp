//======|| EQUIPMENT PHASE IMPL ||======

#include <iostream>
#include <vector>

#include "baseClasses.h"

using std::cout;
using std::endl;

namespace // namespace_start
{

void upgradeGreenCard (Player *,      GreenCard *);
bool hasEnoughMoney   (Player *,      GreenCard *);
bool hasEnoughHonor   (Personality *, GreenCard *);
bool hasntReachedLimit(Personality *, GreenCard *);
/* ========================================================================= */

void upgradeGreenCard(Player * player, GreenCard *card)
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

bool hasEnoughMoney(Player *player, GreenCard *card)
{ 
  size_t currMoney = player->getCurrMoney();
  if (currMoney >= card->getCost()) 
    return true;

  cout << "Not enough money to buy this card!\nMoney available: "
       << currMoney << "\nCard Cost: " << card->getCost() << endl;
  return false;
}
/* ========================================================================= */

bool hasEnoughHonor(Personality *person, GreenCard *card)
{ 
  if (person->getHonor() >= card->getMinHonor())
    return true;

  cout << "Not enough honor to buy this card!\nPersonality's current honor: "
       << person->getHonor() << "\nCard minimum honor: " << card->getMinHonor()
       << endl;
  return false;
}
/* ========================================================================= */

bool hasntReachedLimit(Personality *person, GreenCard *card)
{
  enum GreenCardType cardType = card->getGreenCardType();
  size_t maxCardPerPers = card->getMaxPerPersonality();

  if (cardType == FOLLOWER)
  {
    std::vector<Follower *> * followers = person->getFollowers();
    for (auto *i : *followers)
    {
      if (i->getFollowerType() == card->getFollowerType())
        --maxCardPerPers;
      
      if (maxCardPerPers == 0) break;
    }
  }
  else // cardType == ITEM
  {
    std::vector<Item *> * items = person->getItems();
    for (auto *i : *items)
    {
      if (i->getItemType() == card->getItemType())
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

void Follower::attachToPersonality (Personality * pers) {
  pers->getFollowers()->push_back(this);
}
/* ========================================================================= */

void Item::attachToPersonality (Personality * pers) {
  pers->getItems()->push_back(this);
}
/* ========================================================================= */

size_t Player::getCurrMoney()
{
  std::vector <Holding *> * holdings = this->getHoldings();

  size_t total = 0;

  if (this->getStrongHold()->checkTapped() == false)
    total += this->getStrongHold()->getHarvestValue();

  for (auto *i : *holdings)
    if (i->checkTapped() == false) total += i->getHarvestValue();

  return total;
}
/* ========================================================================= */

void Game::equipmentPhase (Player * player)
{
  cout << "Equipment Phase Started !" << endl;

  cout << "Printing Army!" << endl;
  player->printArmy();
  
  cout << "Printing Hand!" << endl;
  player->printHand();

  cout << "Type 'Y' (YES) or '<any other key>' (NO) after each card's \
appearance if you want to enhance the card's attributes!" << endl;

  for (auto * pers : *(player->getArmy())) 
  {
    pers->print();
    cout << "Equip this Personality ?\n> Your answer : ";
    std::string answer;
    std::getline(std::cin, answer);
    cout << answer << endl;

    if (answer != "Y") continue;

    cout << "Cards in Hand :" << endl;
    for (auto * card : *(player->getHand()))
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

void GreenCard::upgrade() 
{ 
  attackBonus  += effectBonus;
  defenceBonus += effectBonus;
}
/* ========================================================================= */