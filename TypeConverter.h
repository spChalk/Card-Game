#ifndef _TYPECONVERTER_HPP_
#define _TYPECONVERTER_HPP_

#include "Card.hpp"
#include "Personality.hpp"
#include "Holding.hpp"
#include "Follower.hpp"
#include "Follower.hpp"
#include "Item.hpp"

class TypeConverter
{
public:
	TypeConverter();
	void getCorrectType(BlackCard *card, Personality **person, Holding **hold);
	void getCorrectType(GreenCard *card, Follower **follow, Item **item);
	Personality *getPersonality(BlackCard *d);
	Holding *getHolding(BlackCard *d);
	Follower *getFollower(GreenCard *d);
	Item *getItem(GreenCard *d);
};

#endif

