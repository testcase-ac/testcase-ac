#include "testlib.h"

#include <map>
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

static vector<int> initialDeck(int n) {
    vector<int> deck(n);
    for (int i = 0; i < n; ++i) {
        deck[i] = i + 1;
    }
    return deck;
}

static int maxKFor(int n) {
    int maxK = 0;
    while ((1 << (maxK + 1)) < n) {
        ++maxK;
    }
    return maxK;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> nChoices;
    int mode = rnd.next(0, 5);
    if (mode == 0) {
        nChoices = {3, 4, 5, 6, 7, 8};
    } else if (mode == 1) {
        for (int n = 9; n <= 20; ++n) {
            nChoices.push_back(n);
        }
    } else if (mode == 2) {
        for (int n = 21; n <= 60; ++n) {
            nChoices.push_back(n);
        }
    } else if (mode == 3) {
        for (int n = 4; n <= 64; n *= 2) {
            nChoices.push_back(n);
            nChoices.push_back(n + 1);
        }
    } else if (mode == 4) {
        for (int n = 3; n <= 80; ++n) {
            if (n % 2 == 1) {
                nChoices.push_back(n);
            }
        }
    } else {
        for (int n = 3; n <= 80; ++n) {
            nChoices.push_back(n);
        }
    }

    shuffle(nChoices.begin(), nChoices.end());

    vector<int> answer;
    for (int n : nChoices) {
        int maxK = maxKFor(n);
        if (maxK < 1) {
            continue;
        }

        map<vector<int>, int> counts;
        vector<vector<int>> produced;
        vector<int> initial = initialDeck(n);

        for (int firstK = 1; firstK <= maxK; ++firstK) {
            vector<int> afterFirst = applyShuffle(initial, firstK);
            for (int secondK = 1; secondK <= maxK; ++secondK) {
                vector<int> deck = applyShuffle(afterFirst, secondK);
                ++counts[deck];
                produced.push_back(deck);
            }
        }

        shuffle(produced.begin(), produced.end());
        for (const vector<int>& deck : produced) {
            if (counts[deck] == 1) {
                answer = deck;
                break;
            }
        }

        if (!answer.empty()) {
            println(n);
            println(answer);
            return 0;
        }
    }

    println(3);
    println(1, 2, 3);
    return 0;
}
