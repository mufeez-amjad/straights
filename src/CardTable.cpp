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

CardTable::~CardTable() noexcept
{
	if (_cardTableData != nullptr)
		delete _cardTableData;
}

CardTable::CardTable(const CardTable& c) noexcept
{
	this->_cardTableData = new CardTableData();

	// Note that we do not want to perform a deep copy of the data members
	// as the pointers in _table are simply pointing to objects that exist
	// in an instance of the Deck class, so we want a shallow copy to these
	// same Card objects in the instance of the Deck class.
	for (int i = 0; i < CARD_COUNT; i++)
		this->_cardTableData->_table[i] = c._cardTableData->_table[i];
}

CardTable& CardTable::operator=(const CardTable& c) noexcept
{
	if (this == &c)
		return *this;

	CardTable c_copy = CardTable(c);

	CardTableData* temp_table = this->_cardTableData;
	this->_cardTableData = c_copy._cardTableData;
	c_copy._cardTableData = temp_table;

	return *this;
}

CardTable::CardTable(CardTable&& c) noexcept
{
	this->_cardTableData = c._cardTableData;
	c._cardTableData = nullptr;
}

CardTable& CardTable::operator=(CardTable&& c) noexcept
{
	if (this == &c)
		return *this;

	CardTableData* temp_table = this->_cardTableData;
	this->_cardTableData = c._cardTableData;
	c._cardTableData = temp_table;

	return *this;
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
