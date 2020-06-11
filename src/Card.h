#ifndef _CARD_
#define _CARD_

#include <ostream>
#include <istream>

#define CARD_COUNT 52

enum Suit { CLUB, DIAMOND, HEART, SPADE, SUIT_COUNT };
enum Rank { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN,
			EIGHT, NINE, TEN, JACK, QUEEN, KING, RANK_COUNT };

class Card{
	friend std::istream &operator>> (std::istream& is, Card& card);

public:
	Card(Suit, Rank);
	Suit getSuit(void) const;
	Rank getRank(void) const;

private:
	Suit suit_;
	Rank rank_;
};

bool operator==(const Card& a, const Card& b);

// output/input Card in the format <rank><suit>
std::ostream &operator<<(std::ostream& out, const Card& c);
std::istream &operator>>(std::istream& in, Card& c);

#endif
