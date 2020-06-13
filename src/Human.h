#ifndef _HUMAN_
#define _HUMAN_

#include "Player.h"

class Human : public Player {
	public:
		Command playTurn(std::unordered_set<int>&) override;

		class InvalidMoveException
		{
			public:
				InvalidMoveException(std::string s) : _message(s) {};
				std::string getMessage() const {return _message;}
			private:
				std::string _message;
		};

		char getType() override;

	private:
		bool isValidTurn(Card, std::unordered_set<int>&);
};

#endif
