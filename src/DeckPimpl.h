#ifndef _DECK_PIMPL_
#define _DECK_PIMPL_

#include "Card.h"

struct DeckData
{
	Card* _cards[CARD_COUNT];
	Card* _orderedCards[CARD_COUNT];
};

#endif