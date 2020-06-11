#ifndef _COMP_
#define _COMP_

#include "Player.h"

class Computer : public Player {
	public:
		void playTurn(Command);
};

#endif
