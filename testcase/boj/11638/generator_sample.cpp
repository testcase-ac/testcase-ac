#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using Card = pair<int, int>;

static void maybeFlip(Card& card) {
    if (rnd.next(2) == 1) {
        swap(card.first, card.second);
    }
}

static vector<Card> makePath(int n) {
    vector<Card> cards;
    for (int i = 1; i <= n; ++i) {
        cards.push_back({i, i + 1});
    }
    return cards;
}

static vector<Card> makeStar(int n) {
    vector<Card> cards;
    int center = rnd.next(1, 2 * n);
    for (int i = 1; i <= n; ++i) {
        int leaf = i;
        if (leaf >= center) {
            ++leaf;
        }
        cards.push_back({center, leaf});
    }
    return cards;
}

static vector<Card> makeSingleCycle(int n) {
    vector<Card> cards;
    int cycleSize = rnd.next(2, n);
    for (int i = 1; i <= cycleSize; ++i) {
        cards.push_back({i, i % cycleSize + 1});
    }
    for (int i = cycleSize + 1; i <= n; ++i) {
        cards.push_back({rnd.next(1, i), i + 1});
    }
    return cards;
}

static vector<Card> makeTwoCycleComponent(int n) {
    vector<Card> cards;
    cards.push_back({1, 2});
    cards.push_back({2, 3});
    cards.push_back({3, 1});
    cards.push_back({1, 4});
    cards.push_back({4, 5});
    cards.push_back({5, 1});
    for (int i = 7; i <= n; ++i) {
        cards.push_back({i, i + 1});
    }
    return cards;
}

static vector<Card> makeDuplicateEdges(int n) {
    vector<Card> cards;
    int a = rnd.next(1, 2 * n);
    int b = rnd.next(1, 2 * n);
    while (b == a) {
        b = rnd.next(1, 2 * n);
    }
    int copies = rnd.next(2, min(n, 5));
    for (int i = 0; i < copies; ++i) {
        cards.push_back({a, b});
    }
    for (int i = copies + 1; i <= n; ++i) {
        cards.push_back({i, 2 * n - i + 1});
    }
    return cards;
}

static vector<Card> makeSelfLoopMix(int n) {
    vector<Card> cards;
    int loops = rnd.next(1, max(1, n / 2));
    for (int i = 1; i <= loops; ++i) {
        cards.push_back({i, i});
    }
    for (int i = loops + 1; i <= n; ++i) {
        cards.push_back({rnd.next(1, 2 * n), rnd.next(1, 2 * n)});
    }
    return cards;
}

static vector<Card> makeNoisySmall(int n) {
    vector<Card> cards;
    int maxPicture = rnd.next(1, 2 * n);
    for (int i = 0; i < n; ++i) {
        cards.push_back({rnd.next(1, maxPicture), rnd.next(1, maxPicture)});
    }
    return cards;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 10);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(7);
        int n = rnd.next(1, 12);
        if (mode == 2) {
            n = rnd.next(2, 12);
        } else if (mode == 3) {
            n = rnd.next(6, 12);
        } else if (mode == 4) {
            n = rnd.next(2, 12);
        }

        vector<Card> cards;
        if (mode == 0) {
            cards = makePath(n);
        } else if (mode == 1) {
            cards = makeStar(n);
        } else if (mode == 2) {
            cards = makeSingleCycle(n);
        } else if (mode == 3) {
            cards = makeTwoCycleComponent(n);
        } else if (mode == 4) {
            cards = makeDuplicateEdges(n);
        } else if (mode == 5) {
            cards = makeSelfLoopMix(n);
        } else {
            cards = makeNoisySmall(n);
        }

        shuffle(cards.begin(), cards.end());
        for (Card& card : cards) {
            maybeFlip(card);
        }

        println(n);
        for (const Card& card : cards) {
            println(card.first, card.second);
        }
    }

    return 0;
}
