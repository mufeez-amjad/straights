#ifndef _PLAYER_
#define _PLAYER_

#include "Card.h"
#include "Command.h"

enum PlayerNumber { ONE, TWO, THREE, FOUR };

class Player {
	public:
		Card* hand[];
		Card* discard_pile[];
	private:
		virtual void playTurn(Command);
		void placeCard(Card*);
		void discardCard(Card*);
};

#endif
