#ifndef _PLAYER_
#define _PLAYER_

#include <unordered_set>
#include <vector>

#include "Deck.h"
#include "Command.h"
#include "PlayerPimpl.h"

#define PLAYER_COUNT 4

enum class PlayerType : char
{
	HUMAN = 'h',
	COMPUTER = 'c',
};

class Player
{
	public:
		Player();
		Player(std::vector<Card*>, std::vector<Card*>);
		virtual ~Player() noexcept;

		// Accessors
		std::vector<Card*> getHand(void) const;
			// returns: The Player's hand

		std::vector<Card*> getDiscards(void) const;
			// returns: The Player's discards

		PlayerType getType(void) const;
			// returns: The player's type (human or computer)

		// Mutators
		virtual Command playTurn(std::unordered_set<int>&) = 0;
			// returns: The player's move

		void removeCard(Card*);
			// ensures: The Card* parameter is removed from the player's hand
			//          if it is present

		void setHand(Deck&, unsigned int);
			// ensures: The player is dealt 13 consecuative cards from the Deck
			//          starting from the index in the deck passed as the
			//          second parameter.

		void resetHand();
			// ensures: The players hand and list of discards are empty.

	private:
		PlayerData* _playerData;

	protected:
		PlayerType _type;
		void discardCard(Card);
			// ensures: The Card passed as the parameter is moved from the
			//          player's hand to their list of discards.
};

#endif
