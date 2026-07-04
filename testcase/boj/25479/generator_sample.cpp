#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int valueWithParity(int parity) {
    int base = rnd.next(1, 500000);
    int value = base * 2 - (parity == 1 ? 1 : 0);
    return min(value, 1000000);
}

int randomValue(int mode) {
    if (mode == 0) {
        return rnd.next(1, 20);
    }
    if (mode == 1) {
        return rnd.next(999990, 1000000);
    }
    return valueWithParity(rnd.next(0, 1));
}

pair<int, int> randomRange(int n, int mode) {
    if (mode == 0) {
        return {1, n};
    }
    if (mode == 1) {
        int p = rnd.next(1, n);
        return {p, p};
    }
    int l = rnd.next(1, n);
    int maxLen = max(1, min(n - l + 1, rnd.next(1, max(1, n / 2))));
    int r = rnd.next(l, l + maxLen - 1);
    return {l, r};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = mode == 0 ? 1 : rnd.next(2, 30);
    int q = mode == 0 ? rnd.next(1, 6) : rnd.next(3, 45);

    vector<int> a(n);
    int valueMode = rnd.next(0, 2);
    for (int i = 0; i < n; ++i) {
        if (mode == 2) {
            a[i] = valueWithParity(i % 2);
        } else if (mode == 3) {
            a[i] = valueWithParity((i / 2) % 2);
        } else {
            a[i] = randomValue(valueMode);
        }
    }

    println(n, q);
    println(a);

    bool hasQuery = false;
    int forcedQueryAt = rnd.next(1, q);
    for (int i = 1; i <= q; ++i) {
        bool makeQuery = i == forcedQueryAt || (!hasQuery && i == q);
        if (!makeQuery) {
            if (mode == 4) {
                makeQuery = rnd.next(0, 99) < 15;
            } else if (mode == 5) {
                makeQuery = rnd.next(0, 99) < 70;
            } else {
                makeQuery = rnd.next(0, 99) < 45;
            }
        }

        int rangeMode;
        if (mode == 1) {
            rangeMode = 1;
        } else if (mode == 4) {
            rangeMode = rnd.next(0, 1);
        } else {
            rangeMode = rnd.next(0, 2);
        }
        auto [l, r] = randomRange(n, rangeMode);

        if (makeQuery) {
            println(2, l, r);
            hasQuery = true;
        } else {
            int v;
            if (mode == 2 || mode == 3) {
                v = valueWithParity(rnd.next(0, 1));
            } else {
                v = randomValue(valueMode);
            }
            println(1, l, r, v);
        }
    }

    return 0;
}
