#ifndef _COMPUTER_
#define _COMPUTER_

#include "Human.h"

class Computer : public Player
{
	public:
		Computer() : Player() { _type = PlayerType::COMPUTER; };
		Computer(Player&);
		Command playTurn(std::unordered_set<int>&) override;
};

#endif
