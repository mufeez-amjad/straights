#ifndef _HUMAN_
#define _HUMAN_

#include "Player.h"

//============================================================================
// Human is a derived class from Player which represents a player in a game,
// whose actions are determined by input from a user of the program.
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

class Human : public Player
{
	public:
		Human() : Player() { _type = PlayerType::HUMAN; };
		Human& operator=(const Human&) noexcept;

		Command playTurn(std::unordered_set<int>&) override;
		// returns:  The move the Human Player requests via std::cin
		// throws:   InvalidMoveException if the requested move specified
		//           from std::cin is illegal.

		class InvalidMoveException
		{
			public:
				InvalidMoveException(std::string s) : _message(s) {};
				std::string getMessage() const {return _message;}
			private:
				std::string _message;
		};

	private:
		bool _isValidTurn(Card, std::unordered_set<int>&);
		// returns:  True if playing the Card passed as the first parameter
		//           is in the set of valid moves (passed by reference as
		//           the second parameter).
};

#endif
