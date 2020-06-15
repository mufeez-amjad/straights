#include <iostream>

#include "Human.h"
#include "Card.h"

Command Human::playTurn(std::unordered_set<int> &validTurns)
{
	Command co;
	std::cin >> co;

	switch (co.type) {
		case PLAY:
			if (!_isValidTurn(co.card, validTurns)) { // check if card is a valid play
				throw InvalidMoveException("This is not a legal play.");
			}
			break;
		case DISCARD:
			if (validTurns.size()) { // cannot discard if Player has a valid play
				throw InvalidMoveException("You have a legal play. You may not discard.");
			}
			discardCard(co.card);
			break;
		default:
			// other commands handled by Game
			break;
	}

	return co;
}

bool Human::_isValidTurn(Card c, std::unordered_set<int> &validTurns)
{
	int hash = c.getHash();
	return validTurns.find(hash) != validTurns.end();
}
