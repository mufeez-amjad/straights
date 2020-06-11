#ifndef _GAME_PIMPL_
#define _GAME_PIMPL_

#include "Player.h"
#include "Card.h"

struct PlayerRecord {
	int score; // round accumulator
	int points;
	Player* player;
};

struct GameData {
	PlayerRecord _players[];
	PlayerNumber _currentTurn;
	Card* _deck[];
	Card* _validMoves[];
};

#endif