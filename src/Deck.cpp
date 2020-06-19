#include "Deck.h"

#include <random>

int seed = 0;

Deck::Deck()
{
	this->_deckData = new DeckData();

	for (int suit = CLUB; suit != SUIT_COUNT; suit++) {
		for (int rank = ACE; rank != RANK_COUNT; rank++) {
			int index = (RANK_COUNT*suit) + rank;
			this->_deckData->_cards[index] = new Card((Suit)suit, (Rank)rank);
			this->_deckData->_orderedCards[index] = nullptr;
		}
	}
}

Deck::~Deck() noexcept
{
	if (this->_deckData != nullptr) {
		if (this->_deckData->_cards != nullptr) {
			for (int i = 0; i < CARD_COUNT; ++i)
				delete this->_deckData->_cards[i];
		}
		delete this->_deckData;
	}
}

Deck::Deck(const Deck& d)
{
	this->_deckData = new DeckData();

	for (int i = 0; i != CARD_COUNT; i++) {
		this->_deckData->_cards[i] = new Card(*d._deckData->_cards[i]);
		this->_deckData->_orderedCards[i] = nullptr;
	}
	this->_orderCards();
}

Deck& Deck::operator=(const Deck& d)
{
	Deck d_copy = Deck(d);

	DeckData* temp_deck = this->_deckData;
	this->_deckData = d_copy._deckData;
	d_copy._deckData = temp_deck;

	return *this;
}

Deck::Deck(Deck&& d)
{
	this->_deckData = d._deckData;
	d._deckData = nullptr;
}

Deck& Deck::operator=(Deck&& d)
{
	DeckData* temp_deck = this->_deckData;
	this->_deckData = d._deckData;
	d._deckData = temp_deck;

	return *this;
}

Card* Deck::at(unsigned int index)
{
	if (index >= CARD_COUNT)
		throw std::out_of_range("Deck index out of range");

	return this->_deckData->_cards[index];
}

Card* Deck::lookup(Card card)
{
	int hash = card.getHash();
	if (hash >= CARD_COUNT)
		return nullptr;

	return this->_deckData->_orderedCards[hash];
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
		Card *c = this->_deckData->_cards[n];
		this->_deckData->_cards[n] = this->_deckData->_cards[k];
		this->_deckData->_cards[k] = c;
	}

	this->_orderCards();
}

void Deck::_orderCards(void)
{
	for (int i = 0; i < CARD_COUNT; i++) {
		Card* card = this->_deckData->_cards[i];
		this->_deckData->_orderedCards[card->getHash()] = card;
	}
}

std::ostream &operator<<(std::ostream& out, const Deck& deck)
{
	for (int i = 0; i < SUIT_COUNT; i++) {
		for (int j = 0; j < RANK_COUNT; j++) {
			std::cout << *deck._deckData->_cards[Card::hash(i, j)];
			if (j != RANK_COUNT - 1)
				std::cout << " ";
			else if (i != SUIT_COUNT - 1)
				std::cout << "\n";
		}
	}
	return out;
}
