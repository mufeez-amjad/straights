#include "CardTable.h"

CardTable::CardTable()
{
	for (int i = CLUB; i != SUIT_COUNT; i++) {
		for (int j = ACE; j != RANK_COUNT; j++)
			this->_table[Card::hash(i, j)] = nullptr;
	}
}

bool CardTable::addCard(Card* card)
{
	if (card == nullptr)
		return false;

	int hash = card->getHash();

	if (this->_table[hash] == nullptr || hash >= CARD_COUNT)
		return false;

	this->_table[hash] = card;
	return true;
}

void CardTable::clear(void)
{
	for (int i = 0; i < CARD_COUNT; i++)
		this->_table[i] = nullptr;
}

std::ostream &operator<< (std::ostream& out, CardTable& table)
{
	for (int i = 0; i < SUIT_COUNT; i++) {
		std::cout << Card::getName((Suit)i) << ":";

		for (int j = 0; j < RANK_COUNT; j++) {
			if (table._table[Card::hash(i, j)] != nullptr)
				std::cout << " " << table._table[Card::hash(i, j)]->getSymbol();
		}
		if (i != SUIT_COUNT - 1)
			std::cout << "\n";
	}
	return out;
}
