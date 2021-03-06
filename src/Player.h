#ifndef _PLAYER_
#define _PLAYER_

#include <unordered_set>
#include <vector>

#include "Deck.h"
#include "Command.h"
#include "PlayerPimpl.h"

#define PLAYER_COUNT 4

//============================================================================
// Player represents an abstract class for a player in any game. Will be
// extended by Human and Computer classes.
//
// Specification fields:
//		_type: enum class PlayerType char{ HUMAN = 'h', COMPUTER = 'c' }
//			- protected for child classes to derive
//		_playerData: Private implementation of Player's data members
//			- std::vector<Card*> _hand
//				- Stores the cards in the players hand throughout each round.
//				  Updated after the player's turn when a card is removed from
//				  the hand due to the player playing or discarding it
//			- std::vector<Card*> _discards
//				- Stores the cards that the player has discared throughout
//				  each round to be printed at the end of the round.
//============================================================================

class Player
{
	public:
		Player();
		Player(std::vector<Card*>, std::vector<Card*>);
		virtual ~Player() noexcept;

		Player(const Player&) noexcept;
		Player(Player&&) noexcept;
		Player& operator=(Player&&) noexcept;

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

	protected:
		PlayerType _type;
		PlayerData* _playerData;

		void discardCard(Card);
			// ensures: The Card passed as the parameter is moved from the
			//          player's hand to their list of discards.
};

#endif
