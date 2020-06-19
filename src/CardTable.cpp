#include "CardTable.h"

#include <cassert>

CardTable::CardTable()
{
	_cardTableData = new CardTableData();

	for (int i = CLUB; i != SUIT_COUNT; i++) {
		for (int j = ACE; j != RANK_COUNT; j++)
			this->_cardTableData->_table[Card::hash(i, j)] = nullptr;
	}
}

CardTable::~CardTable()
{
	if (_cardTableData != nullptr)
		delete _cardTableData;
}

void CardTable::addCard(Card* card)
{
	assert(card != nullptr);

	int hash = card->getHash();
	assert(this->_cardTableData->_table[hash] == nullptr && hash < CARD_COUNT);

	this->_cardTableData->_table[hash] = card;
}

void CardTable::clear(void)
{
	for (int i = 0; i < CARD_COUNT; i++)
		this->_cardTableData->_table[i] = nullptr;
}

std::ostream &operator<< (std::ostream& out, CardTable& table)
{
	for (int i = 0; i < SUIT_COUNT; i++) {
		std::cout << Card::getName((Suit)i) << ":";

		for (int j = 0; j < RANK_COUNT; j++) {
			if (table._cardTableData->_table[Card::hash(i, j)] != nullptr) {
				std::cout << " " << table._cardTableData->_table[Card::hash(i, j)]->getSymbol();
			}
		}
		if (i != SUIT_COUNT - 1)
			std::cout << "\n";
	}
	return out;
}
