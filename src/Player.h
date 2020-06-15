#ifndef _PLAYER_
#define _PLAYER_

#include <unordered_set>
#include <vector>

#include "Card.h"
#include "Command.h"

#define PLAYER_COUNT 4

enum class PlayerType : char {
     HUMAN = 'h',
     COMPUTER = 'c',
};

class Player
{
	friend class Game;

	public:
		virtual ~Player();

		// Accessors
		std::vector<Card*> getHand(void) const;
		std::vector<Card*> getDiscards(void) const;
		PlayerType getType(void) const;

		// Mutators
		virtual Command playTurn(std::unordered_set<int>&) = 0;

		void removeCard(Card*);
		void setHand(Card**);
		void setHand(std::vector<Card*>);
		void setDiscards(std::vector<Card*>);

	private:
		std::vector<Card*> _hand;
		std::vector<Card*> _discards;

	protected:
		PlayerType _type;
		void discardCard(Card);
};

#endif
