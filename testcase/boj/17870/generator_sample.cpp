#include "testlib.h"

#include <algorithm>
#include <cstdint>
#include <utility>
#include <vector>

using namespace std;

long long makeKey(long long a, long long b) {
    return a * b;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<long long> smallPrimes = {
        3, 5, 7, 11, 13, 17, 19, 23, 29, 31,
        37, 41, 43, 47, 53, 59, 61, 67, 71, 73
    };
    const vector<long long> mediumPrimes = {
        101, 131, 167, 193, 227, 263, 307, 359, 419, 467,
        521, 587, 653, 733, 809, 887, 977, 1069, 1181, 1297
    };
    const vector<long long> largePrimes = {
        32717, 32749, 32771, 32779, 65413, 65519, 65521
    };

    int mode = rnd.next(0, 4);
    int m;
    vector<pair<long long, long long>> pairs;

    auto addRandomPair = [&](const vector<long long>& left, const vector<long long>& right) {
        pairs.push_back({rnd.any(left), rnd.any(right)});
    };

    if (mode == 0) {
        m = rnd.next(2, 10);
        for (int i = 0; i < m; ++i) {
            addRandomPair(smallPrimes, smallPrimes);
        }
    } else if (mode == 1) {
        m = rnd.next(8, 24);
        long long shared = rnd.any(mediumPrimes);
        for (int i = 0; i < m; ++i) {
            pairs.push_back({shared, rnd.any(smallPrimes)});
        }
    } else if (mode == 2) {
        m = rnd.next(10, 35);
        for (int i = 0; i < m; ++i) {
            if (rnd.next(0, 2) == 0) {
                long long p = rnd.any(smallPrimes);
                pairs.push_back({p, p});
            } else {
                addRandomPair(smallPrimes, mediumPrimes);
            }
        }
    } else if (mode == 3) {
        m = rnd.next(6, 18);
        for (int i = 0; i < m; ++i) {
            addRandomPair(mediumPrimes, largePrimes);
        }
    } else {
        m = rnd.next(20, 100);
        for (int i = 0; i < m; ++i) {
            int band = rnd.next(0, 3);
            if (band == 0) {
                addRandomPair(smallPrimes, smallPrimes);
            } else if (band == 1) {
                addRandomPair(smallPrimes, mediumPrimes);
            } else if (band == 2) {
                addRandomPair(mediumPrimes, mediumPrimes);
            } else {
                addRandomPair(largePrimes, largePrimes);
            }
        }
    }

    shuffle(pairs.begin(), pairs.end());

    println(m);
    for (auto [a, b] : pairs) {
        println(makeKey(a, b));
    }

    return 0;
}
