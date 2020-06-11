#ifndef _PLAYER_
#define _PLAYER_

#include <unordered_set>
#include <vector>

#include "Card.h"
#include "Command.h"

enum class PlayerNumber { ONE, TWO, THREE, FOUR };

class Player {
	public:
		virtual Command playTurn(std::unordered_set<int>&) = 0;
		// Accessors
		std::vector<Card*> getHand(void) const;
		std::vector<Card*> getDiscards(void) const;
		// Mutators
		void removeCard(Card*);
		void setHand(Card*);
	protected:
		void discardCard(Card);
	private:
		std::vector<Card*> hand;
		std::vector<Card*> discards;
};

#endif
