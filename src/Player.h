#ifndef _PLAYER_
#define _PLAYER_

#include <vector>

#include "Card.h"
#include "Command.h"

enum PlayerNumber { ONE, TWO, THREE, FOUR };

class Player {
	public:
		std::vector<Card*> hand;
		std::vector<Card*> discards;
	protected:
		virtual Command playTurn(std::vector<Card*>);
		void removeCard(Card*);
		void setHand(Card*);	//pointer to start of the array at i*13
};

#endif
