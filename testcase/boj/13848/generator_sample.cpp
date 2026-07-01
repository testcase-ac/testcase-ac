#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

static vector<int> makeFullDeck() {
    vector<int> deck;
    for (int rank = 1; rank <= 13; ++rank) {
        for (int copy = 0; copy < 4; ++copy) {
            deck.push_back(rank);
        }
    }
    return deck;
}

static vector<int> randomSubset(int n, const vector<int>& deck) {
    vector<int> cards = deck;
    shuffle(cards.begin(), cards.end());
    cards.resize(n);
    shuffle(cards.begin(), cards.end());
    return cards;
}

static vector<int> duplicateHeavyCase() {
    vector<int> ranks;
    int distinct = rnd.next(2, 5);
    vector<int> deckRanks;
    for (int rank = 1; rank <= 13; ++rank) {
        deckRanks.push_back(rank);
    }
    shuffle(deckRanks.begin(), deckRanks.end());

    for (int i = 0; i < distinct; ++i) {
        int copies = rnd.next(1, 4);
        for (int j = 0; j < copies; ++j) {
            ranks.push_back(deckRanks[i]);
        }
    }
    shuffle(ranks.begin(), ranks.end());
    return ranks;
}

static vector<int> divisorFocusedCase() {
    vector<int> cards;
    vector<int> smallRanks = {1, 2, 3, 4, 6, 12};
    int n = rnd.next(4, 18);
    vector<int> countByRank(14, 0);

    while (static_cast<int>(cards.size()) < n) {
        int rank = rnd.any(smallRanks);
        if (countByRank[rank] == 4) {
            continue;
        }
        ++countByRank[rank];
        cards.push_back(rank);
    }

    shuffle(cards.begin(), cards.end());
    return cards;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> deck = makeFullDeck();
    int caseCount = rnd.next(4, 8);

    for (int tc = 0; tc < caseCount; ++tc) {
        vector<int> cards;
        int mode = rnd.next(0, 4);

        if (mode == 0) {
            cards = randomSubset(rnd.next(1, 8), deck);
        } else if (mode == 1) {
            cards = randomSubset(rnd.next(9, 24), deck);
        } else if (mode == 2) {
            cards = duplicateHeavyCase();
        } else if (mode == 3) {
            cards = divisorFocusedCase();
        } else {
            cards = randomSubset(rnd.next(40, 52), deck);
        }

        println(static_cast<int>(cards.size()));
        println(cards);
    }

    println(0);
    return 0;
}
