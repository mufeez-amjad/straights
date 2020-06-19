#ifndef _HUMAN_
#define _HUMAN_

#include "Player.h"

class Human : public Player
{
	public:
		Human() : Player() { _type = PlayerType::HUMAN; };

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
