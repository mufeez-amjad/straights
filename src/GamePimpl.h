#ifndef _GAME_PIMPL_
#define _GAME_PIMPL_

#include "Player.h"
#include "Deck.h"
#include "CardTable.h"

#include <unordered_set>

struct PlayerRecord
{
	// round accumulator
	int score;
	// single round score
	int points;

	Player* player;
};

struct GameData
{
	bool _playing;
	bool _activeRound;
	int _currentPlayer;
	int _cardsInPlay;
	std::unordered_set<int> _validMoves;
	Deck* _deck;
	CardTable* _table;
	PlayerRecord _players[PLAYER_COUNT];
};

#endif
