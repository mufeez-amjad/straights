#ifndef _PLAYER_
#define _PLAYER_

#include <unordered_set>
#include <vector>

#include "Card.h"
#include "Command.h"

enum class PlayerNumber { ONE, TWO, THREE, FOUR };

class Player {
	public:
		std::vector<Card*> hand;
		std::vector<Card*> discards;
		virtual Command playTurn(std::unordered_set<Card*>&) = 0;
		void removeCard(Card*);
		void setHand(Card*);
	protected:
		void discardCard(Card*);
		std::vector<Card*> getValidTurns(std::unordered_set<Card*>&);
};

#endif
