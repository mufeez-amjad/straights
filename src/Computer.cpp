#include "Computer.h"

#include <iostream>
#include <cassert>

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

		// std::cout << "hand before discard: " << getHand() << "\n";
		// std::cout << "discarding card " << c << "...\n";

		co.card = c;
		co.type = DISCARD;
		discardCard(c);
	}

	return co;
}
