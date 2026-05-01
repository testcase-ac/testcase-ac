#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAXN = 1000000000000000000LL;
    long long N = 1;
    int type = rnd.next(1, 10);

    switch (type) {
        case 1: {
            // Very small N: 1..10
            N = rnd.next(1LL, 10LL);
            break;
        }
        case 2: {
            // Small even N: 2,4,6,8,10
            vector<long long> v = {2, 4, 6, 8, 10};
            N = rnd.any(v);
            break;
        }
        case 3: {
            // Small odd N: 1..15 odd
            vector<long long> v = {1, 3, 5, 7, 9, 11, 13, 15};
            N = rnd.any(v);
            break;
        }
        case 4: {
            // Medium N: 11..1000
            N = rnd.next(11LL, 1000LL);
            break;
        }
        case 5: {
            // Medium/large N: 1000..1e6
            N = rnd.next(1000LL, 1000000LL);
            break;
        }
        case 6: {
            // Random in full range 1..1e18
            N = rnd.next(1LL, MAXN);
            break;
        }
        case 7: {
            // Large even N (stress, ensures even)
            long long half = rnd.next(1LL, MAXN / 2);
            N = 2 * half;
            break;
        }
        case 8: {
            // Large odd N (stress, ensures answer is 0)
            long long half = rnd.next(1LL, MAXN / 2);
            N = 2 * half - 1;
            if (N < 1) N = 1; // safety, though shouldn't happen
            break;
        }
        case 9: {
            // Powers of 2 up to MAXN (edgey structure)
            vector<long long> pw;
            long long cur = 1;
            while (cur <= MAXN) {
                pw.push_back(cur);
                if (cur > MAXN / 2) break;
                cur <<= 1;
            }
            N = rnd.any(pw);
            break;
        }
        case 10: {
            // Handpicked interesting edge cases
            vector<long long> special = {
                1LL, 2LL, 3LL, 4LL, 5LL, 6LL,
                7LL, 8LL, 9LL, 10LL, 11LL, 12LL,
                99LL, 100LL, 101LL,
                2147483646LL, 2147483647LL, 2147483648LL, // around 2^31
                1000000000000000000LL,                    // MAXN
                999999999999999999LL,
                999999999999999998LL,
                500000000000000000LL,
                500000000000000001LL
            };
            N = rnd.any(special);
            break;
        }
    }

    println(N);
    return 0;
}
