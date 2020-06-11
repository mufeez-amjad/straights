#ifndef _HUMAN_
#define _HUMAN_

#include <vector>

#include "Player.h"

class Human : public Player {
	public:
		Command playTurn(std::vector<Card *>);
		void rageQuit();
	private:
		bool isValidTurn(std::vector<Card*>);
};

#endif
