#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Case {
    int p;
    int q;
    int a;
    int b;
    int c;
    int d;
};

int nearValue(int base, int lo, int hi) {
    int delta = rnd.next(-3, 3);
    return max(lo, min(hi, base + delta));
}

Case randomSmall() {
    int cap = rnd.next(8, 80);
    return {
        rnd.next(0, cap),
        rnd.next(0, cap),
        rnd.next(1, cap),
        rnd.next(1, cap),
        rnd.next(1, cap),
        rnd.next(1, cap),
    };
}

Case randomBoundary() {
    vector<int> pqs = {0, 1, 2, 9998, 9999, 10000};
    vector<int> vals = {1, 2, 3, 9998, 9999, 10000};
    return {
        rnd.any(pqs),
        rnd.any(pqs),
        rnd.any(vals),
        rnd.any(vals),
        rnd.any(vals),
        rnd.any(vals),
    };
}

Case randomBalanced() {
    int a = rnd.next(1, 120);
    int b = rnd.next(1, 120);
    int c = rnd.next(1, 120);
    int d = rnd.next(1, 120);
    int bitBlocks = rnd.next(0, 50);
    int berryBlocks = rnd.next(0, 50);
    int p = min(10000, bitBlocks * a + rnd.next(0, max(1, a) - 1));
    int q = min(10000, berryBlocks * c + rnd.next(0, max(1, c) - 1));

    if (rnd.next(2) == 0) {
        int coins = bitBlocks * b + berryBlocks * d;
        p = nearValue(coins, 0, 10000);
    }

    return {p, q, a, b, c, d};
}

Case randomSkewedRates() {
    bool bigYield = rnd.next(2);
    int small = rnd.next(1, 20);
    int large = rnd.next(8000, 10000);
    int a = bigYield ? small : large;
    int b = bigYield ? large : small;
    int c = rnd.next(1, 200);
    int d = rnd.next(1, 10000);

    if (rnd.next(2)) {
        swap(a, c);
        swap(b, d);
    }

    return {
        rnd.next(0, 10000),
        rnd.next(0, 10000),
        a,
        b,
        c,
        d,
    };
}

Case randomRemainder() {
    int a = rnd.next(2, 300);
    int c = rnd.next(2, 300);
    int b = rnd.next(1, 300);
    int d = rnd.next(1, 300);
    int p = min(10000, rnd.next(0, 30) * a + rnd.next(0, a - 1));
    int q = min(10000, rnd.next(0, 30) * c + rnd.next(0, c - 1));
    return {p, q, a, b, c, d};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 30);
    vector<Case> cases;
    cases.reserve(t);

    cases.push_back({0, 0, 1, 1, 1, 1});
    cases.push_back({10000, 10000, 10000, 10000, 10000, 10000});

    while ((int)cases.size() < t) {
        int mode = rnd.next(5);
        if (mode == 0) cases.push_back(randomSmall());
        if (mode == 1) cases.push_back(randomBoundary());
        if (mode == 2) cases.push_back(randomBalanced());
        if (mode == 3) cases.push_back(randomSkewedRates());
        if (mode == 4) cases.push_back(randomRemainder());
    }

    shuffle(cases.begin(), cases.end());

    println(t);
    for (const Case& tc : cases) {
        println(tc.p, tc.q, tc.a, tc.b, tc.c, tc.d);
    }

    return 0;
}
