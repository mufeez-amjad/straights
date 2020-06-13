#ifndef _GAME_PIMPL_
#define _GAME_PIMPL_

#include "Player.h"
#include "Card.h"

#include <unordered_set>
#include <unordered_map>

struct PlayerRecord {
	int score; // round accumulator
	int points;
	Player* player;
};

struct GameData {
	bool _playing;
	bool _activeRound;
	int _currentPlayer;
	int _cardsInHand;
	std::unordered_set<int> _validMoves;
	Card* _deck[CARD_COUNT];
	Card* _orderedDeck[CARD_COUNT];
	Card* _table[CARD_COUNT];
	PlayerRecord _players[PLAYER_COUNT];
};

#endif
