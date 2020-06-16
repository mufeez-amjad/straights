#include "Deck.h"

#include <random>

int seed = 0;

Deck::Deck()
{
	for (int suit = CLUB; suit != SUIT_COUNT; suit++) {
		for (int rank = ACE; rank != RANK_COUNT; rank++) {
			int index = (RANK_COUNT*suit) + rank;
			this->_cards[index] = new Card((Suit)suit, (Rank)rank);
			this->_orderedCards[index] = nullptr;
		}
	}
}

Deck::~Deck()
{
	if (this->_cards != nullptr) {
		for (int i = 0; i < CARD_COUNT; ++i)
			delete this->_cards[i];
	}
}

Card* Deck::at(unsigned int index)
{
	if (index >= CARD_COUNT)
		return nullptr;

	return this->_cards[index];
}

Card* Deck::lookup(Card card)
{
	int hash = card.getHash();
	if (hash >= CARD_COUNT)
		return nullptr;

	return this->_orderedCards[hash];
}

Card* Deck::lookup(Card* card)
{
	return this->lookup(*card);
}

void Deck::shuffle(void)
{
	static std::mt19937 rng(seed);
	int n = CARD_COUNT;

	while (n > 1) {
		int k = (int) (rng() % n);
		--n;
		Card *c = this->_cards[n];
		this->_cards[n] = this->_cards[k];
		this->_cards[k] = c;
	}

	this->_orderCards();
}

void Deck::_orderCards(void)
{
	for (int i = 0; i < CARD_COUNT; i++) {
		Card* card = this->_cards[i];
		this->_orderedCards[card->getHash()] = card;
	}
}

std::ostream &operator<<(std::ostream& out, const Deck& deck)
{
	for (int i = 0; i < SUIT_COUNT; i++) {
		for (int j = 0; j < RANK_COUNT; j++) {
			std::cout << *deck._cards[Card::hash(i, j)];
			if (j != RANK_COUNT - 1)
				std::cout << " ";
			else
				std::cout << "\n";
		}
	}
	return out;
}
