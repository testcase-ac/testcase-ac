#include "testlib.h"

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;

using u64 = uint64_t;
using u128 = __uint128_t;

constexpr u64 kLimit = 1000000000000000000ULL;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<u64> smallPrimes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
    const vector<u64> largePrimes = {
        999999937ULL,
        1000000007ULL,
        1000000009ULL,
    };

    auto printFactorization = [](const vector<u64>& factors) {
        cout << factors.size();
        for (u64 factor : factors) {
            cout << ' ' << factor;
        }
        cout << '\n';
    };

    int q = rnd.next(1, 8);
    println(q);

    for (int query = 0; query < q; ++query) {
        vector<u64> primes = smallPrimes;
        if (rnd.next(0, 3) == 0) {
            primes.push_back(rnd.any(largePrimes));
        }
        shuffle(primes.begin(), primes.end());

        vector<u64> gFactors;
        vector<u64> lFactors;
        u128 lProduct = 1;

        int distinct = rnd.next(1, min<int>(6, primes.size()));
        for (int i = 0; i < distinct; ++i) {
            u64 p = primes[i];
            int gExp = rnd.next(0, 3);
            int extraExp = rnd.next(0, 4);

            for (int e = 0; e < gExp; ++e) {
                if (lProduct * p > kLimit) break;
                gFactors.push_back(p);
                lFactors.push_back(p);
                lProduct *= p;
            }
            for (int e = 0; e < extraExp && lProduct * p <= kLimit; ++e) {
                lFactors.push_back(p);
                lProduct *= p;
            }
        }

        if (lFactors.empty()) {
            lFactors.push_back(2);
        }

        if (rnd.next(0, 1) == 1) {
            shuffle(gFactors.begin(), gFactors.end());
            shuffle(lFactors.begin(), lFactors.end());
        }

        printFactorization(gFactors);
        printFactorization(lFactors);
    }

    return 0;
}
