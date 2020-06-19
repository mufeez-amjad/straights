#ifndef _DECK_
#define _DECK_

#include "Card.h"

#include <stdexcept>

extern int seed;

class Deck
{
	friend std::ostream &operator<<(std::ostream&, const Deck&);

	public:
		Deck();
		~Deck() noexcept;

		void shuffle(void);
			// modifies: shuffles the deck using a pseudo-random number
			//           generator, seeded by the global variable seed

		Card* at(unsigned int);
			// returns: the Card* in the deck at index passed as the parameter
			// throws: throws std::out_of_range if the index given as the
			//         parameter is greater than or equal to CARD_COUNT

		Card* lookup(Card);
			// returns: the Card* in the deck with the matching hash of the
			//          Card passed as the paramter

		Card* lookup(Card*);
			// returns: the Card* in the deck with the matching hash of the
			//          Card* passed as the paramter

	private:
		void _orderCards(void);
			// modifies: this modifies _orderedCards to accurately map from
			//           card hashes to Card* in the deck

		Card* _cards[CARD_COUNT];
		Card* _orderedCards[CARD_COUNT];
};

std::ostream &operator<<(std::ostream&, const Deck&);

#endif
