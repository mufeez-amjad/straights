#ifndef _COMPUTER_
#define _COMPUTER_

#include "Human.h"

//============================================================================
// Computer is a derived class from Player which represents a player in a game,
// whose actions are automated by the game class.
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


class Computer : public Player
{
	public:
		Computer() : Player() { _type = PlayerType::COMPUTER; };
		// Computer& operator=(const Computer&) noexcept;
		
		Computer(Player&);

		Command playTurn(std::unordered_set<int>&) override;
			// returns: a Command specifying the computer player's move
};

#endif
