#ifndef _DECK_
#define _DECK_

#include "DeckPimpl.h"

#include <stdexcept>

extern int seed;

//============================================================================
// Deck represents an object consisting of CARD_COUNT number of cards which
// are instances of the card class.
//
// Specification fields:
//	The private implementation of Deck's data members _deckData:
//		Card* _cards[CARD_COUNT]
//			- Stores pointers to card objects that fully specify a CARD_COUNT
//			  number cards for a deck in a game. This is the deck which will
//			  be shuffled for each round of the game
//		Card* _orderedCards[CARD_COUNT]
//			- Stores ordered pointers to the same card objects in _cards
//			  for reference after shuffling the _cards deck
//============================================================================

class Deck
{
	friend std::ostream &operator<<(std::ostream&, const Deck&);

	public:
		Deck();
		~Deck() noexcept;

		Deck(const Deck&) noexcept;
		Deck& operator=(const Deck&) noexcept;
		Deck(Deck&&) noexcept;
		Deck& operator=(Deck&&) noexcept;

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

		DeckData* _deckData;
};

std::ostream &operator<<(std::ostream&, const Deck&);

#endif
