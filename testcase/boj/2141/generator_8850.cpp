#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<long long, long long>> v;

    int type = rnd.next(0, 7);

    auto add = [&](long long x, long long a) {
        v.push_back({x, a});
    };

    switch (type) {
        case 0: {
            // Single village, possibly extreme coordinate / weight
            long long X0;
            int c = rnd.next(0, 2);
            if (c == 0) X0 = -1000000000LL;
            else if (c == 1) X0 = 0LL;
            else X0 = 1000000000LL;

            long long A0;
            if (rnd.next(0, 1) == 0) A0 = 1LL;
            else A0 = 1000000000LL;
            add(X0, A0);
            break;
        }
        case 1: {
            // Two villages with very unbalanced populations
            long long base = rnd.next(-20, 20);
            long long dist = rnd.next(1, 20);
            long long x1 = base;
            long long x2 = base + dist;

            long long big = 1000000000LL - rnd.next(0, 100000);
            long long small = rnd.next(1, 5);

            if (rnd.next(0, 1) == 0) {
                add(x1, big);
                add(x2, small);
            } else {
                add(x1, small);
                add(x2, big);
            }

            if (rnd.next(0, 1)) {
                // shuffle order
                ::shuffle(v.begin(), v.end());
            }
            break;
        }
        case 2: {
            // Four villages with equal weight: tests strict '>' vs '>=' bugs
            long long offset = rnd.next(-5, 5);
            for (int i = 0; i < 4; ++i) {
                add(offset + i, 1LL);
            }
            if (rnd.next(0, 1)) {
                ::shuffle(v.begin(), v.end());
            }
            break;
        }
        case 3: {
            // Weighted vs unweighted median divergence
            // Positions: 0, 1, 2, 100 with weights 1,1,1,100
            add(0LL, 1LL);
            add(1LL, 1LL);
            add(2LL, 1LL);
            add(100LL, 100LL);
            if (rnd.next(0, 1)) {
                ::shuffle(v.begin(), v.end());
            }
            break;
        }
        case 4: {
            // Small/medium random instance (readable)
            int N = rnd.next(5, 15);
            for (int i = 0; i < N; ++i) {
                long long x = rnd.next(-20, 20);
                long long a = rnd.next(1, 20);
                add(x, a);
            }
            if (rnd.next(0, 1)) {
                ::shuffle(v.begin(), v.end());
            }
            break;
        }
        case 5: {
            // Overflow-prone populations and coordinates near limits
            int N = 3 + rnd.next(0, 1); // 3 or 4
            for (int i = 0; i < N; ++i) {
                long long sign = (i % 2 == 0 ? 1LL : -1LL);
                long long x = sign * (1000000000LL - rnd.next(0, 100)); // near +/-1e9
                long long a = 1000000000LL - rnd.next(0, 1000000);      // ~1e9
                if (a < 1) a = 1; // safety
                add(x, a);
            }
            if (rnd.next(0, 1)) {
                ::shuffle(v.begin(), v.end());
            }
            break;
        }
        case 6: {
            // All villages at the same coordinate
            int N = rnd.next(3, 8);
            long long x = rnd.next(-100, 100);
            for (int i = 0; i < N; ++i) {
                long long a;
                if (rnd.next(0, 1) == 0)
                    a = rnd.next(1, 100);
                else
                    a = 1000000000LL - rnd.next(0, 1000000); // some large
                if (a < 1) a = 1;
                add(x, a);
            }
            if (rnd.next(0, 1)) {
                ::shuffle(v.begin(), v.end());
            }
            break;
        }
        case 7: {
            // Two equal-population villages: tie interval, smallest position should be chosen
            long long base = rnd.next(-10, 10);
            long long dist = rnd.next(1, 20);
            add(base, 1LL);
            add(base + dist, 1LL);
            if (rnd.next(0, 1)) {
                ::shuffle(v.begin(), v.end());
            }
            break;
        }
    }

    int N = (int)v.size();
    println(N);
    for (int i = 0; i < N; ++i) {
        println(v[i].first, v[i].second);
    }

    return 0;
}
