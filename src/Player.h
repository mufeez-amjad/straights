#ifndef _PLAYER_
#define _PLAYER_

#include <unordered_set>
#include <vector>
#include <unordered_set>

#include <iostream> // TODO: remove

#include "Card.h"
#include "Command.h"

#define PLAYER_COUNT 4

class Player {
	friend class Game;

	public:
		virtual Command playTurn(std::unordered_set<int>&) = 0;
		virtual ~Player();

		// Accessors
		std::vector<Card*> getHand(void) const;
		std::vector<Card*> getDiscards(void) const;

		// Mutators
		void removeCard(Card*);
		void setHand(Card*); // pointer to start of the array at i*13
	private:
		std::vector<Card*> hand;
		std::vector<Card*> discards;

		virtual char getType() = 0;

	protected:
		void discardCard(Card);
};

#endif
