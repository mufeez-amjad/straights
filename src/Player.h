#ifndef _PLAYER_
#define _PLAYER_

#include <unordered_set>
#include <vector>

#include "Card.h"
#include "Command.h"

#define PLAYER_COUNT 4

class Player
{
	friend class Game;

	public:
		virtual Command playTurn(std::unordered_set<int>&) = 0;
		virtual ~Player();

		// Accessors
		std::vector<Card*> getHand(void) const;
		std::vector<Card*> getDiscards(void) const;

		// Mutators
		void removeCard(Card*);
		void setHand(Card**);
		void setHand(std::vector<Card*>);
		void setDiscards(std::vector<Card*>);

		virtual char getType() = 0;
	private:
		std::vector<Card*> _hand;
		std::vector<Card*> _discards;


	protected:
		void discardCard(Card);
};

#endif
