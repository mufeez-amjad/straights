#include "Player.h"

void Player::removeCard(Card* c) {
    for (auto i = hand.begin(); i != hand.end(); i++) {
        if (*i == c) {
            hand.erase(i--);
        }
    }
}

void Player::setHand(Card* c) {
    for (Card* i = c; i < c + 13; i++) {
        hand.push_back(i);
    }
}

void Player::discardCard(Card c) {
    Card* discardedCard;

    for (auto card: hand) {
        if (*card == c) {
            discardedCard = card;
            break;
        }
    }

    removeCard(discardedCard);
    discards.push_back(discardedCard);
}

std::vector<Card*> Player::getValidTurns(std::unordered_set<Card*>& validTurns) {
    std::vector<Card*> myValidTurns;

    for (auto c: hand) {
        if (validTurns.find(c) != validTurns.end()) {
            myValidTurns.push_back(c);
        }
    }

    return myValidTurns;
}