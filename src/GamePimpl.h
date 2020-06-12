#ifndef _GAME_PIMPL_
#define _GAME_PIMPL_

#include "Player.h"
#include "Card.h"

#include <vector>

struct PlayerRecord {
	int score; // round accumulator
	int points;
	Player* player;
};

struct GameData {
	bool _playing;
	PlayerNumber _currentTurn;
	std::vector<Card*> _validMoves;
	Card* _deck[CARD_COUNT];
	PlayerRecord _players[PLAYER_COUNT];
};

#endif
