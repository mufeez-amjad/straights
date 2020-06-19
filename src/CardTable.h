#ifndef _CARDTABLE_
#define _CARDTABLE_

#include "Card.h"

//============================================================================
// CardTable represents a table of cards which have currently been played in
// the game
//
// Specification fields:
//		- Card* _table[CARD_COUNT]
//			- Contains nullptrs for any cards not on the table, and pointers
//			  to the same Card objects as pointed to by _deck in the Deck
//			  if the card has been played previously during the round
//============================================================================

class CardTable
{
	friend std::ostream &operator<< (std::ostream&, CardTable&);

	public:
		CardTable();

		bool addCard(Card*);
			// returns: true if the Card* is added to the table, otherwise
			//          returns false if the Card* is null or not added to the
			//          table. Card* is not added if it is already on the table
			// modifies: if the Card* is not nullptr and not in the table,
			//           _table will contain the Card*

		void clear(void);
			// modifies: sets all indicies of _table to nullptr

	private:
		Card* _table[CARD_COUNT];
};

std::ostream &operator<< (std::ostream&, CardTable&);

#endif
