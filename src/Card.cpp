#include "Card.h"

#include <string>
#include <cassert>
#include <vector>

// Suit titles for printing cards on the table
std::string suitNames[4] =
{
	"Clubs", "Diamonds", "Hearts", "Spades"
};

Card::Card(const Card &c) noexcept
{
	suit_ = c.suit_;
	rank_ = c.rank_;
}

std::string& Card::getName(Suit suit)
{
	assert((int)suit < SUIT_COUNT);
	return suitNames[(int)suit];
}

int Card::hash(Suit suit, Rank rank)
{
	return suit * 13 + rank;
}

int Card::hash(int i, int j)
{
	assert(i < SUIT_COUNT && j < RANK_COUNT);
	return Card::hash((Suit)i, (Rank)j);
}

Card::Card(Suit s, Rank r)
{
	suit_ = s;
	rank_ = r;
}

Card::Card(int hash)
{
	suit_ = (Suit) (hash / RANK_COUNT);
	rank_ = (Rank) (hash % RANK_COUNT);
}

Suit Card::getSuit(void) const
{
	return suit_;
}

Rank Card::getRank(void) const
{
	return rank_;
}

int Card::getHash(void) const
{
	return Card::hash(this->suit_, this->rank_);
}

bool operator== (const Card& a, const Card& b)
{
	return a.getSuit() == b.getSuit() && a.getRank() == b.getRank();
}

std::ostream &operator<< (std::ostream& out, const Card& c)
{

	std::string suits[SUIT_COUNT] =
	{
		"C", "D", "H", "S"
	};

	std::string ranks[RANK_COUNT] =
	{
		"A", "2", "3", "4", "5", "6",
		"7", "8", "9", "10", "J", "Q", "K"
	};

	out << ranks[c.getRank()] << suits[c.getSuit()];
	return out;
}

std::istream &operator>>(std::istream& in, Card& c)
{
	std::string suits = "CDHS", ranks = "A234567891JQK";

	std::string str;
	in >> str;
	assert(!in.fail());

	// Read in the rank, make sure it's valid
	c.rank_ = (Rank)ranks.find(str.at(0));
	assert(c.rank_ != std::string::npos);

	// If it's a 10, make sure the 2nd character is a 0
	if (c.rank_ == TEN) {
		assert(str.at(1) == '0');
		str.at(1) = str.at(2);
	}

	// Read in the suit, make sure it's valid
	c.suit_ = (Suit)suits.find(str.at(1));
	assert(c.suit_ != std::string::npos);

	return in;
}

std::ostream &operator<<(std::ostream& out, const std::vector<Card*>& cards)
{
	for (size_t i = 0; i < cards.size(); i++) {
		out << *cards.at(i);
		if (i != cards.size() - 1)
			out << " ";
	}
	return out;
}
