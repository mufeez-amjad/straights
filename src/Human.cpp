#include <iostream>

#include "Human.h"
#include "Card.h"

Command Human::playTurn(std::unordered_set<Card*> &validTurns) {
    std::vector<Card*> myValidTurns = getValidTurns(validTurns);

    Command co;

    std::cin >> co;

    switch (co.type) {
        case PLAY:
            if (!isValidTurn(co.card, myValidTurns)) {
                throw InvalidMoveException("This is not a legal play.");
            }
            break;
        case DISCARD:
            if (myValidTurns.size()) {
                throw InvalidMoveException("You have a legal play. You may not discard.");
            }
            discardCard(co.card);
            break;
        default:
            break;
    }

    return co;
}

bool Human::isValidTurn(Card c, std::vector<Card*> &validTurns) {
    for (auto v: validTurns) {
        if (*v == c) {
            return true;
        }
    }

    return false;
}