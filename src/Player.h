#ifndef _PLAYER_
#define _PLAYER_

#include <unordered_set>
#include <vector>

#include "Card.h"
#include "Command.h"
#include "PlayerPimpl.h"

class Player
{
	public:
		Player();
		Player(std::vector<Card*>, std::vector<Card*>);
		virtual ~Player() noexcept;

		// Accessors
		std::vector<Card*> getHand(void) const;
		std::vector<Card*> getDiscards(void) const;
		PlayerType getType(void) const;

		// Mutators
		virtual Command playTurn(std::unordered_set<int>&) = 0;

		void removeCard(Card*);
		void setHand(Card**);
		void resetHand();

	private:
		PlayerData* _playerData;

	protected:
		PlayerType _type;
		void discardCard(Card);
};

#endif
