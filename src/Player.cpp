#include "Player.h"

#include <iostream>

Player::~Player() noexcept
{
	if(_playerData != nullptr)
		delete _playerData;
}

Player::Player() {
	this->_playerData = new PlayerData();
}

Player::Player(std::vector<Card*> hand, std::vector<Card*> discards) {
	this->_playerData = new PlayerData();

	this->_playerData->_hand = hand;
	this->_playerData->_discards = discards;
}

void Player::removeCard(Card* c)
{

	// std::cout << "hand before removing a card: " << this->getHand() << "\n";

	for (auto i = _playerData->_hand.begin(); i != _playerData->_hand.end(); i++) {
		if (*i == c)
			_playerData->_hand.erase(i--);
	}

	// std::cout << "hand after removing a card: " << this->getHand() << "\n";
}

void Player::setHand(Deck& deck, unsigned int index)
{
	for (unsigned int i = index; i < index + RANK_COUNT; i++)
		_playerData->_hand.push_back(deck.at(i));
}

void Player::resetHand()
{
	std::vector<Card*> empty;
	_playerData->_hand = empty;
	_playerData->_discards = empty;
}

void Player::discardCard(Card c)
{
	Card* discardedCard;

	for (auto card: _playerData->_hand) {
		if (*card == c) {
			discardedCard = card;
			break;
		}
	}

	removeCard(discardedCard);
	_playerData->_discards.push_back(discardedCard);
}

std::vector<Card*> Player::getHand(void) const {
	return _playerData->_hand;
}

std::vector<Card*> Player::getDiscards(void) const {
	return _playerData->_discards;
}

PlayerType Player::getType(void) const {
	return _type;
}
