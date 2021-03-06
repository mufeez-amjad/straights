#include "Computer.h"

#include <iostream>
#include <cassert>

Computer& Computer::operator=(const Computer& c) noexcept
{
	if (this == &c)
		return *this;

	Computer c_copy = Computer(c);

	PlayerData* temp_player = this->_playerData;
	this->_playerData = c_copy._playerData;
	c_copy._playerData = temp_player;

	return *this;
}

Computer::Computer(Player& p) : Player(p.getHand(), p.getDiscards())
{
	_type = PlayerType::COMPUTER;
}

Command Computer::playTurn(std::unordered_set<int> &validTurns) {
	Command co;

	if (validTurns.size()) {
		int hash = *validTurns.begin();
		Card c = Card(hash);

		co.card = c;
		co.type = PLAY;
	} else {
		std::vector<Card*> hand = getHand();
		Card c = *hand.at(0);

		co.card = c;
		co.type = DISCARD;
		discardCard(c);
	}

	return co;
}
