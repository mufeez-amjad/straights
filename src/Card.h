#ifndef _CARD_
#define _CARD_

#include <iostream>
#include <vector>

#define CARD_COUNT 52

enum Suit { CLUB, DIAMOND, HEART, SPADE, SUIT_COUNT };
enum Rank { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN,
		    EIGHT, NINE, TEN, JACK, QUEEN, KING, RANK_COUNT };

class Card
{
	friend std::istream &operator>> (std::istream&, Card&);

public:
	Card(Suit, Rank);
	Card(int);

	Card(const Card&) noexcept;

	Suit getSuit(void) const;
		// returns: the card's suit

	Rank getRank(void) const;
		// returns: the card's rank

	int getValue(void) const;
		// returns: the card's numeric value

	char getSymbol(void) const;
		// returns: the card's symbol

	int getHash(void) const;
		// returns: the card's hash = (13 * Suit) + Rank

	static int hash(Suit, Rank);
	static int hash(int, int);
	static std::string& getName(Suit);

private:
	Suit suit_;
	Rank rank_;
};

bool operator==(const Card&, const Card&);

// output/input Card in the format <rank><suit>
std::ostream &operator<<(std::ostream&, const Card&);
std::istream &operator>>(std::istream&, Card&);

std::ostream &operator<<(std::ostream&, const std::vector<Card*>&);

#endif
