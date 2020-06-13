#include "Computer.h"

Command Computer::playTurn(std::unordered_set<int> &validTurns) {
    Command co;

    if (validTurns.size()) {
        int hash = *validTurns.begin();
        Card c = Card(hash);

        co.card = c;
        co.type = PLAY;
    } else {
        std::vector<Card*> hand = getHand();
        Card c = *hand[0];

        co.card = c;
        co.type = DISCARD;
        discardCard(c);
    }

    return co;
}
