#ifndef _CARDTABLE_
#define _CARDTABLE_

#include "Card.h"

class CardTable
{
	friend std::ostream &operator<< (std::ostream&, CardTable&);

	public:
		CardTable();
		bool addCard(Card*);
		void clear(void);

	private:
		Card* _table[CARD_COUNT];
};

std::ostream &operator<< (std::ostream&, CardTable&);

#endif
