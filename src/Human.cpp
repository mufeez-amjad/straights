#include <iostream>

#include "Human.h"
#include "Card.h"

Command Human::playTurn(std::unordered_set<int> &validTurns)
{
	Command co;
	std::cin >> co;

	switch (co.type) {
		case PLAY:
			if (!isValidTurn(co.card, validTurns)) {
				throw InvalidMoveException("This is not a legal play.");
			}
			break;
		case DISCARD:
			if (validTurns.size()) {
				throw InvalidMoveException("You have a legal play. You may not discard.");
			}
			discardCard(co.card);
			break;
		default:
			break;
	}

	return co;
}

bool Human::isValidTurn(Card c, std::unordered_set<int> &validTurns)
{
	int hash = c.getHash();
	return validTurns.find(hash) != validTurns.end();
}

char Human::getType()
{
	return 'h';
}
