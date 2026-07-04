#include "testlib.h"

#include <algorithm>
#include <cstdint>
#include <vector>

using namespace std;

uint64_t randomMask(int n, int maxBits) {
    int bits = rnd.next(1, maxBits);
    vector<int> cards(n);
    for (int i = 0; i < n; ++i) cards[i] = i;
    shuffle(cards.begin(), cards.end());

    uint64_t mask = 0;
    for (int i = 0; i < bits; ++i) mask |= (1ULL << cards[i]);
    return mask;
}

vector<int> maskToCards(uint64_t mask, int n) {
    vector<int> cards;
    for (int i = 0; i < n; ++i) {
        if (mask & (1ULL << i)) cards.push_back(i + 1);
    }
    return cards;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n;
    int m;
    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 4);
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        m = rnd.next(1, min(10, n + 4));
    } else if (mode == 2) {
        n = rnd.next(8, 18);
        m = rnd.next(4, 14);
    } else if (mode == 3) {
        n = rnd.next(20, 35);
        m = rnd.next(8, 14);
    } else {
        n = rnd.next(50, 60);
        m = rnd.next(10, 14);
    }

    uint64_t target = n == 64 ? ~0ULL : ((1ULL << n) - 1);
    vector<uint64_t> spells;

    if (mode == 1 && m >= n) {
        vector<uint64_t> singletons;
        for (int i = 0; i < n; ++i) singletons.push_back(1ULL << i);
        shuffle(singletons.begin(), singletons.end());
        spells.insert(spells.end(), singletons.begin(), singletons.end());
    } else {
        int chosen = rnd.next(1, min({m, n, 6}));
        vector<int> cards(n);
        for (int i = 0; i < n; ++i) cards[i] = i;
        shuffle(cards.begin(), cards.end());

        vector<uint64_t> selected(chosen, 0);
        for (int i = 0; i < n; ++i) {
            selected[i % chosen] |= (1ULL << cards[i]);
        }
        spells.insert(spells.end(), selected.begin(), selected.end());
    }

    while ((int)spells.size() < m) {
        if (rnd.next(4) == 0 && !spells.empty()) {
            spells.push_back(spells[rnd.next((int)spells.size())]);
        } else if (rnd.next(4) == 0) {
            spells.push_back(target);
        } else {
            spells.push_back(randomMask(n, min(n, rnd.next(1, 10))));
        }
    }

    shuffle(spells.begin(), spells.end());

    println(n, m);
    for (uint64_t mask : spells) {
        vector<int> cards = maskToCards(mask, n);
        if (rnd.next(2) == 0) shuffle(cards.begin(), cards.end());
        cout << cards.size();
        for (int card : cards) cout << ' ' << card;
        cout << '\n';
    }

    return 0;
}
