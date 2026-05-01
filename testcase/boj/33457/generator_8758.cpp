#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose number of test cases, small enough for manual checking
    int T = rnd.next(4, 10);

    vector<array<int, 4>> tests;

    // Some fixed edge / sample-like tests
    tests.push_back({0, 0, 0, 0});
    tests.push_back({0, 0, 3, 6});
    tests.push_back({1, 0, 1, 0});
    tests.push_back({1, 1, 1, 1});

    auto randKL = [&]() -> pair<int,int> {
        while (true) {
            int k = rnd.next(0, 44);
            int l = rnd.next(0, 44);
            if (1LL * k * k + 1LL * l * l <= 2023)
                return {k, l};
        }
    };

    auto randKL_small = [&]() -> pair<int,int> {
        while (true) {
            int k = rnd.next(0, 10);
            int l = rnd.next(0, 10);
            if (1LL * k * k + 1LL * l * l <= 2023)
                return {k, l};
        }
    };

    auto randKL_border = [&]() -> pair<int,int> {
        while (true) {
            int k = rnd.next(20, 44);
            int l = rnd.next(20, 44);
            long long s = 1LL * k * k + 1LL * l * l;
            if (s <= 2023 && s >= 1700)
                return {k, l};
        }
    };

    while ((int)tests.size() < T) {
        int type = rnd.next(0, 4);
        int n = 0, m = 0, k = 0, l = 0;

        if (type == 0) {
            // Very small n, m and small exponents
            n = rnd.next(0, 5);
            m = rnd.next(0, 5);
            auto p = randKL_small();
            k = p.first;
            l = p.second;
        } else if (type == 1) {
            // One of n, m is zero, the other moderate
            if (rnd.next(0, 1) == 0) {
                n = 0;
                m = rnd.next(1, 100);
            } else {
                n = rnd.next(1, 100);
                m = 0;
            }
            auto p = randKL();
            k = p.first;
            l = p.second;
        } else if (type == 2) {
            // Both moderate n, m and random exponents
            n = rnd.next(10, 100);
            m = rnd.next(10, 100);
            auto p = randKL();
            k = p.first;
            l = p.second;
        } else if (type == 3) {
            // Small n, m but large exponents near the radius limit
            n = rnd.next(0, 20);
            m = rnd.next(0, 20);
            auto p = randKL_border();
            k = p.first;
            l = p.second;
        } else {
            // Mixed: maxed n or m, one of k or l zero
            if (rnd.next(0, 1) == 0) {
                n = 100;
                m = rnd.next(0, 100);
            } else {
                m = 100;
                n = rnd.next(0, 100);
            }
            if (rnd.next(0, 1) == 0) {
                k = 0;
                l = rnd.next(0, 44);
                while (1LL * l * l > 2023) l = rnd.next(0, 44);
            } else {
                l = 0;
                k = rnd.next(0, 44);
                while (1LL * k * k > 2023) k = rnd.next(0, 44);
            }
        }

        // Ensure constraints 0 <= n,m <= 300 and k^2 + l^2 <= 2023 (already ensured),
        // and n,m <= 100 by construction (to satisfy total sum constraint easily).
        tests.push_back({n, m, k, l});
    }

    // Optional shuffle to randomize order, keeping them diverse
    shuffle(tests.begin(), tests.end());

    println(T);
    for (auto &tc : tests) {
        println(tc[0], tc[1], tc[2], tc[3]);
    }

    return 0;
}
