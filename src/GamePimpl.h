#ifndef _GAME_PIMPL_
#define _GAME_PIMPL_

#include "Player.h"
#include "Deck.h"
#include "CardTable.h"

#include <unordered_set>

struct PlayerRecord
{
	int score;  // round accumulator
	int points; // single round score
	Player* player;
};

struct GameData
{
	bool _playing;
	bool _activeRound;
	int _currentPlayer;
	int _cardsInHand;
	std::unordered_set<int> _validMoves;
	Deck* _deck;
	Card* _table[CARD_COUNT];
	PlayerRecord _players[PLAYER_COUNT];
};

#endif
