#ifndef _COMPUTER_
#define _COMPUTER_

#include "Player.h"

class Computer : public Player {
	public:
		Command playTurn(std::unordered_set<int>&) override;
		char getType() override {return 'c';};
};

#endif