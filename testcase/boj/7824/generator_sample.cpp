#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

const long long MAX_A = 2000000000000000000LL;

long long clampStone(long long x) {
    return min(MAX_A, max(1LL, x));
}

long long nearPowerOfTwo() {
    int exponent = rnd.next(1, 60);
    long long base = 1LL << exponent;
    long long delta = rnd.next(-3, 3);
    return clampStone(base + delta);
}

long long randomLarge() {
    long long block = rnd.next(1LL, 2000000LL);
    long long offset = rnd.next(0LL, 999999999999LL);
    return clampStone(block * 1000000000000LL - offset);
}

long long randomPile(int mode) {
    if (mode == 0) {
        return rnd.next(1LL, 30LL);
    }
    if (mode == 1) {
        return nearPowerOfTwo();
    }
    if (mode == 2) {
        long long x = rnd.next(1LL, 1000000LL);
        return rnd.next(0, 1) == 0 ? 2 * x : 2 * x + 1;
    }
    if (mode == 3) {
        return randomLarge();
    }
    return rnd.any(vector<long long>{1, 2, 3, 4, 7, 8, 15, 16, 31, 32, MAX_A});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(3, 12);
    vector<vector<long long>> cases;

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 4);
        int n;
        if (mode == 3) {
            n = rnd.next(1, 6);
        } else if (mode == 4) {
            n = rnd.next(8, 24);
        } else {
            n = rnd.next(1, 12);
        }

        vector<long long> piles;
        for (int i = 0; i < n; ++i) {
            piles.push_back(randomPile(mode));
        }

        if (mode == 4) {
            for (int i = 0; i + 1 < n; i += 2) {
                piles[i + 1] = piles[i];
            }
        }

        shuffle(piles.begin(), piles.end());
        cases.push_back(piles);
    }

    println(t);
    for (const auto& piles : cases) {
        println((int)piles.size());
        println(piles);
    }

    return 0;
}
