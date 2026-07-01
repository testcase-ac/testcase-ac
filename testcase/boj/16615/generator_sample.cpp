#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

namespace {

const int kMaxPile = 100000;

vector<int> randomStateFromOperations(int n) {
    vector<int> piles(n, 0);
    int operations = rnd.next(0, min(kMaxPile, 3 * n + 20));
    for (int op = 0; op < operations; ++op) {
        int k = rnd.next(0, n - 1);
        bool left = rnd.next(0, 1) == 0;
        if (left) {
            for (int i = 0; i <= k; ++i) {
                ++piles[i];
            }
        } else {
            for (int i = k; i < n; ++i) {
                ++piles[i];
            }
        }
    }
    return piles;
}

vector<int> randomWalk(int n, int limit) {
    vector<int> piles(n);
    piles[0] = rnd.next(0, limit);
    for (int i = 1; i < n; ++i) {
        int step = rnd.next(-limit / 4 - 1, limit / 4 + 1);
        piles[i] = max(0, min(limit, piles[i - 1] + step));
    }
    return piles;
}

vector<int> mountainOrValley(int n, int limit, bool mountain) {
    vector<int> piles(n);
    int pivot = rnd.next(0, n - 1);
    int current = mountain ? rnd.next(limit / 2, limit) : rnd.next(0, limit / 2);

    for (int i = pivot; i >= 0; --i) {
        piles[i] = current;
        if (mountain) {
            current = max(0, current - rnd.next(0, 5));
        } else {
            current = min(limit, current + rnd.next(0, 5));
        }
    }

    current = piles[pivot];
    for (int i = pivot + 1; i < n; ++i) {
        if (mountain) {
            current = max(0, current - rnd.next(0, 5));
        } else {
            current = min(limit, current + rnd.next(0, 5));
        }
        piles[i] = current;
    }
    return piles;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 5);
    } else if (mode == 5) {
        n = rnd.next(40, 120);
    } else {
        n = rnd.next(2, 25);
    }

    int limit = rnd.next(0, 1) == 0 ? rnd.next(0, 30) : rnd.next(1000, kMaxPile);
    vector<int> piles;

    if (mode == 0) {
        piles.assign(n, rnd.next(0, limit));
    } else if (mode == 1) {
        piles = randomStateFromOperations(n);
    } else if (mode == 2) {
        piles = randomWalk(n, limit);
    } else if (mode == 3) {
        piles = mountainOrValley(n, limit, false);
    } else if (mode == 4) {
        piles = mountainOrValley(n, limit, true);
    } else {
        piles.resize(n);
        for (int& value : piles) {
            value = rnd.next(0, limit);
        }
    }

    println(n);
    println(piles);
    return 0;
}
