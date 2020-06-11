#ifndef _COMPUTER_
#define _COMPUTER_

#include "Player.h"

class Computer : public Player {
	public:
		Command playTurn(std::vector<Card *>);
};

#endif