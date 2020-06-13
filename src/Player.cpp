#include "Player.h"

Player::~Player()
{

}

void Player::removeCard(Card* c)
{
	for (auto i = _hand.begin(); i != _hand.end(); i++) {
		if (*i == c)
			_hand.erase(i--);
	}
}

void Player::setHand(Card** c)
{
	for (Card** i = c; i < c + RANK_COUNT; i++)
		_hand.push_back(*i);
}

void Player::setHand(std::vector<Card*> hand)
{
	_hand = hand;
}

void Player::setDiscards(std::vector<Card*> discards)
{
	_discards = discards;
}

void Player::discardCard(Card c)
{
	Card* discardedCard;

	for (auto card: _hand) {
		if (*card == c) {
			discardedCard = card;
			break;
		}
	}

	removeCard(discardedCard);
	_discards.push_back(discardedCard);
}

std::vector<Card*> Player::getHand(void) const {
	return _hand;
}

std::vector<Card*> Player::getDiscards(void) const {
	return _discards;
}
