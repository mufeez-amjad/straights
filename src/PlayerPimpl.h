#ifndef _PLAYER_PIMPL_
#define _PLAYER_PIMPL_

#include <unordered_set>
#include <vector>

#include "Card.h"
#include "Command.h"

#define PLAYER_COUNT 4

enum class PlayerType : char {
     HUMAN = 'h',
     COMPUTER = 'c',
};

struct PlayerData {
	std::vector<Card*> _hand;
	std::vector<Card*> _discards;
};

#endif
