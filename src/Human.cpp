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

void Human::printTurn(std::unordered_set<Card*> &validTurns) {
    std::vector<Card*> clubs;
    std::vector<Card*> diamonds;
    std::vector<Card*> hearts;
    std::vector<Card*> spades;
    std::vector<Card*> myValidTurns = getValidTurns(validTurns);

    for (auto c: hand) {
        Suit s = c->getSuit();

        switch (s) {
            case CLUB:
                clubs.push_back(c);
                break;
            case DIAMOND:
                diamonds.push_back(c);
                break;
            case HEART:
                hearts.push_back(c);
                break;
            case SPADE:
                spades.push_back(c);
                break;
            default:
                break;
        }
    }

    std::cout << "Cards on the table:" << std::endl;
    std::cout << "Clubs: " << clubs << std::endl;
    std::cout << "Diamonds: " << diamonds << std::endl;
    std::cout << "Hearts: " << hearts << std::endl;
    std::cout << "Spades: " << spades << std::endl;
    std::cout << "Your hand: " << hand << std::endl;
    std::cout << "Legal plays: " << myValidTurns << std::endl;
}