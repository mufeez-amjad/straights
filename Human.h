#ifndef _HUMAN_
#define _HUMAN_

#include "Player.h";

class Human : Player {
    public:
        void playTurn(Command);
        void rageQuit();
};


#endif