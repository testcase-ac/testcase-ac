#include "testlib.h"

#include <vector>

using namespace std;

static vector<int> applyShuffle(vector<int> deck, int k) {
    int n = (int)deck.size();
    int topLen = 1 << k;

    vector<int> next;
    next.reserve(n);
    next.insert(next.end(), deck.end() - topLen, deck.end());
    next.insert(next.end(), deck.begin(), deck.end() - topLen);
    deck.swap(next);

    for (int i = 2; i <= k + 1; ++i) {
        int count = 1 << (k - i + 1);
        vector<int> moved(deck.begin() + topLen - count, deck.begin() + topLen);
        vector<int> rest;
        rest.reserve(n - count);
        rest.insert(rest.end(), deck.begin(), deck.begin() + topLen - count);
        rest.insert(rest.end(), deck.begin() + topLen, deck.end());

        deck.clear();
        deck.reserve(n);
        deck.insert(deck.end(), moved.begin(), moved.end());
        deck.insert(deck.end(), rest.begin(), rest.end());
        topLen = count;
    }

    return deck;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 1000, "N");
    inf.readEoln();

    vector<int> deck = inf.readInts(n, 1, n, "card");
    inf.readEoln();
    inf.readEof();

    vector<bool> seen(n + 1, false);
    for (int i = 0; i < n; ++i) {
        ensuref(!seen[deck[i]], "duplicate card %d at position %d", deck[i], i + 1);
        seen[deck[i]] = true;
    }

    vector<int> initial(n);
    for (int i = 0; i < n; ++i) {
        initial[i] = i + 1;
    }

    int matchingPairs = 0;
    for (int firstK = 1; (1 << firstK) < n; ++firstK) {
        vector<int> afterFirst = applyShuffle(initial, firstK);
        for (int secondK = 1; (1 << secondK) < n; ++secondK) {
            if (applyShuffle(afterFirst, secondK) == deck) {
                ++matchingPairs;
            }
        }
    }

    ensuref(matchingPairs == 1,
            "deck must be produced by a unique pair of valid (2, K)-shuffles, found %d",
            matchingPairs);

    return 0;
}
