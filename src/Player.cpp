#include "Player.h"

#include <iostream>

Player::~Player()
{

}

Player::Player(std::vector<Card*> hand, std::vector<Card*> discards) {
	_hand = hand;
	_discards = discards;
}

void Player::removeCard(Card* c)
{

	// std::cout << "hand before removing a card: " << this->getHand() << "\n";

	for (auto i = _hand.begin(); i != _hand.end(); i++) {
		if (*i == c)
			_hand.erase(i--);
	}

	// std::cout << "hand after removing a card: " << this->getHand() << "\n";
}

void Player::setHand(Card** c)
{
	for (Card** i = c; i < c + RANK_COUNT; i++)
		_hand.push_back(*i);
}

void Player::resetHand()
{
	std::vector<Card*> empty;
	_hand = empty;
	_discards = empty;
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

PlayerType Player::getType(void) const {
	return _type;
}
