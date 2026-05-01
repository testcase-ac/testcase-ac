#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    long long N = 1;
    int type = rnd.next(1, 7);

    switch (type) {
        case 1: { // very small N
            if (rnd.next(0, 1) == 0) {
                // bias towards small edge-ish values
                vector<long long> v = {
                    1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                    11, 12, 13, 14, 15, 16, 17, 18, 19, 20
                };
                N = rnd.any(v);
            } else {
                N = rnd.next(1LL, 30LL);
            }
            break;
        }
        case 2: { // random medium-small
            N = rnd.next(10LL, 1000000LL);
            break;
        }
        case 3: { // random medium-large
            N = rnd.next(1000000LL, 1000000000000LL); // 1e6 .. 1e12
            break;
        }
        case 4: { // near powers of two
            int k = rnd.next(1, 47); // 2^47 < 2^63
            long long base = 1LL << k;
            long long delta = rnd.next(-5LL, 5LL);
            long long cand = base + delta;
            if (cand < 1) cand = 1;
            if (cand > 100000000000000LL) cand = 100000000000000LL; // 1e14
            N = cand;
            break;
        }
        case 5: { // perfect square or near
            long long k = rnd.next(1LL, 10000000LL); // k^2 <= 1e14
            long long sq = k * k;
            long long delta = rnd.next(-3LL, 3LL);
            long long cand = sq + delta;
            if (cand < 1) cand = 1;
            if (cand > 100000000000000LL) cand = 100000000000000LL;
            N = cand;
            break;
        }
        case 6: { // around maximum N
            long long base = 100000000000000LL; // 1e14
            long long delta = rnd.next(-1000LL, 0LL);
            long long cand = base + delta;
            if (cand < 1) cand = 1;
            N = cand;
            break;
        }
        case 7: { // handpicked interesting values
            vector<long long> v = {
                1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                13, 14, 15, 16, 25, 26, 27, 30, 31, 32,
                49, 50, 51, 97, 98, 99, 100, 101, 102,
                9973, 99991,
                1000000007LL, 9999999967LL,
                99999999999LL, 100000000000000LL
            };
            N = rnd.any(v);
            break;
        }
    }

    println(N);
    return 0;
}
