#include <iostream>
#include <cassert>

#include "Human.h"
#include "Card.h"

Human& Human::operator=(const Human& h) noexcept
{
	if (this == &h)
		return *this;

	Human h_copy = Human(h);

	PlayerData* temp_player = this->_playerData;
	this->_playerData = h_copy._playerData;
	h_copy._playerData = temp_player;

	return *this;
}

Command Human::playTurn(std::unordered_set<int> &validTurns)
{
	Command co;
	std::cout << "> ";
	std::cin >> co;

	if (co.type == PLAY || co.type == DISCARD) {
		bool found = false;

		for (auto c : getHand()) {
			if (*c == co.card) {
				found = true;
				break;
			}
		}
		if (!found) {
			// supress unused variable warning when compiling without assertions
			// leave in curly braces since assert() macro will be removed by
			// -DNDEBUG flag
			assert(false);
		}
	}

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
