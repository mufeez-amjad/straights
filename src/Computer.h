#ifndef _COMPUTER_
#define _COMPUTER_

#include "Player.h"

class Computer : public Player {
	public:
		Command playTurn(std::unordered_set<Card*>&);
};

#endif