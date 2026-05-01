#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int LIM = 1 << 30;
    vector<pair<int, int>> tests;

    auto add = [&](int a, int b) {
        if (a == b) return;
        if (a < 0 || a >= LIM || b < 0 || b >= LIM) return;
        tests.push_back({a, b});
    };

    // Hand-crafted diverse cases
    add(0, 1);
    add(1, 0);
    add(0, LIM - 1);
    add(LIM - 1, 0);
    add(3, 4);          // from sample, impossible
    add(3, 5);          // from sample, possible in 1 step
    add(5, 7);
    add(10, 12);
    add(42, 24);
    add((1 << 29) - 1, (1 << 29));
    add(1 << 29, (1 << 29) + 1);

    // Some bit-pattern specific cases
    for (int k = 0; k < 5; ++k) {
        int a = (1 << k) - 1;        // 0,1,3,7,15
        int b = a ^ (1 << (k + 1));  // flip next bit
        add(a, b);
    }

    // Random extra cases
    int extra = rnd.next(0, 10);
    for (int i = 0; i < extra; ++i) {
        int type = rnd.next(1, 5);
        int a, b;
        if (type == 1) {
            // both small
            a = rnd.next(0, 30);
            do {
                b = rnd.next(0, 30);
            } while (b == a);
        } else if (type == 2) {
            // near maximum
            a = rnd.next(LIM - 100, LIM - 1);
            do {
                b = rnd.next(LIM - 100, LIM - 1);
            } while (b == a);
        } else if (type == 3) {
            // one is zero
            a = 0;
            b = rnd.next(1, LIM - 1);
            if (rnd.next(0, 1)) swap(a, b);
        } else if (type == 4) {
            // one is power of two
            a = 1 << rnd.next(0, 29);
            do {
                b = rnd.next(0, LIM - 1);
            } while (b == a);
            if (rnd.next(0, 1)) swap(a, b);
        } else {
            // XOR differs by power of two
            int k = rnd.next(0, 29);
            int bit = 1 << k;
            a = rnd.next(0, LIM - 1);
            b = a ^ bit;
        }
        add(a, b);
    }

    // Ensure at least one test exists
    if (tests.empty()) {
        add(0, 1);
    }

    // Shuffle and choose random subset size for variability
    shuffle(tests.begin(), tests.end());
    int maxT = (int)tests.size();
    int T = rnd.next(1, maxT);
    tests.resize(T);

    println(T);
    for (auto &pr : tests) {
        println(pr.first, pr.second);
    }

    return 0;
}
