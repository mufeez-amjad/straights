#ifndef _COMPUTER_
#define _COMPUTER_

#include "Human.h"

class Computer : public Player {
	public:
		Computer();
		Computer(Player*);
		Command playTurn(std::unordered_set<int>&) override;
		char getType() override;
};

#endif
