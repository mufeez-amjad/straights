#include "Computer.h"

Command Computer::playTurn(std::unordered_set<Card*> &validTurns) {
    std::vector<Card*> myValidTurns = getValidTurns(validTurns);

    Command co;

    if (myValidTurns.size()) {
        Card c = *myValidTurns[0];

        co.card = c;
        co.type = PLAY;
    } else {
        Card c = *hand[0];

        co.card = c;
        co.type = DISCARD;
        discardCard(c);
    }

    return co;
}