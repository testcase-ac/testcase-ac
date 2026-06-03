#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int evenInRange(int lo, int hi) {
    int value = rnd.next(lo / 2, hi / 2) * 2;
    return max(lo, min(hi, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    if (mode == 0) {
        n = 2;
    } else if (mode == 1) {
        n = 4;
    } else if (mode == 5) {
        n = evenInRange(40, 120);
    } else {
        n = evenInRange(6, 30);
    }

    vector<int> cards(n);

    if (mode == 0) {
        cards[0] = rnd.next(1, 10000);
        cards[1] = rnd.next(1, 10000);
    } else if (mode == 1) {
        int low = rnd.next(1, 100);
        int high = rnd.next(9900, 10000);
        for (int i = 0; i < n; ++i) {
            cards[i] = (i % 2 == 0 ? high : low);
        }
        if (rnd.next(2) == 0) {
            reverse(cards.begin(), cards.end());
        }
    } else if (mode == 2) {
        int base = rnd.next(1, 10000);
        fill(cards.begin(), cards.end(), base);
    } else if (mode == 3) {
        int start = rnd.next(1, 500);
        int step = rnd.next(1, 200);
        for (int i = 0; i < n; ++i) {
            cards[i] = min(10000, start + i * step);
        }
        if (rnd.next(2) == 0) {
            reverse(cards.begin(), cards.end());
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            cards[i] = rnd.next(1, 50);
        }
        int spikes = rnd.next(1, min(4, n));
        for (int i = 0; i < spikes; ++i) {
            cards[rnd.next(n)] = rnd.next(9000, 10000);
        }
    } else {
        int lo = rnd.next(1, 5000);
        int hi = rnd.next(lo, 10000);
        for (int i = 0; i < n; ++i) {
            cards[i] = rnd.next(lo, hi);
        }
    }

    println(n);
    println(cards);

    return 0;
}
