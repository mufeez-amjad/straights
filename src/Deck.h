#ifndef _DECK_
#define _DECK_

#include <iostream>

#include "Card.h"

extern int seed;

class Deck
{
	friend std::ostream &operator<<(std::ostream&, const Deck&);

	public:
		Deck();
		~Deck();

		void shuffle(void);
		Card* at(unsigned int);

		Card* lookup(Card);
		Card* lookup(Card*);

	private:
		void _orderCards(void);

		Card* _cards[CARD_COUNT];
		Card* _orderedCards[CARD_COUNT];
};

std::ostream &operator<<(std::ostream&, const Deck&);

#endif
