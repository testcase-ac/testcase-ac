#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

const int MAX_B = 1000;
const int MAX_SUM_N = 1000000;

int randomPrime() {
    static const vector<int> primes = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37,
        41, 43, 47, 53, 59, 61, 67, 71, 997
    };
    return rnd.any(primes);
}

int primePowerBase() {
    int p = rnd.any(vector<int>{2, 3, 5, 7, 11, 13, 17, 19, 31});
    int value = p;
    while (value * p <= MAX_B && rnd.next(0, 1)) value *= p;
    return value;
}

int compositeBase() {
    static const vector<int> bases = {
        6, 10, 12, 18, 24, 30, 36, 45, 60, 72, 84, 90,
        120, 180, 210, 360, 420, 504, 720, 840, 900, 960, 990, 1000
    };
    return rnd.any(bases);
}

int randomBase() {
    int mode = rnd.next(0, 4);
    if (mode == 0) return randomPrime();
    if (mode == 1) return primePowerBase();
    if (mode == 2) return compositeBase();
    if (mode == 3) return rnd.next(2, 30);
    return rnd.next(2, MAX_B);
}

int randomN(int remaining) {
    int mode = rnd.next(0, 5);
    int limit = min(remaining, 1000000);
    if (limit == 1) return 1;
    if (mode == 0) return 1;
    if (mode == 1) return rnd.next(2, min(limit, 20));
    if (mode == 2 && limit >= 21) return rnd.next(21, min(limit, 500));
    if (mode == 3 && limit >= 501) return rnd.next(501, min(limit, 20000));
    if (mode == 4) return rnd.next(max(1, limit - min(limit - 1, 5000)), limit);
    return rnd.next(1, limit);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int scenarios = rnd.next(1, mode == 5 ? 35 : 16);
    vector<pair<int, int>> cases;
    cases.reserve(scenarios);

    int remaining = MAX_SUM_N;
    for (int i = 0; i < scenarios; ++i) {
        int left = scenarios - i;
        int maxForCase = remaining - (left - 1);
        int b = randomBase();
        int n = randomN(maxForCase);

        if (mode == 0) {
            b = rnd.any(vector<int>{2, 4, 8, 16, 32, 64, 128, 256, 512});
            n = rnd.next(1, min(maxForCase, 1000));
        } else if (mode == 1) {
            b = compositeBase();
            n = rnd.next(1, min(maxForCase, 20000));
        } else if (mode == 2) {
            b = randomPrime();
            n = rnd.next(max(1, maxForCase - min(maxForCase - 1, 10000)), maxForCase);
        } else if (mode == 3) {
            b = rnd.any(vector<int>{999, 1000, 990, 997});
            n = rnd.next(1, min(maxForCase, 100000));
        } else if (mode == 4 && i + 1 == scenarios) {
            b = rnd.any(vector<int>{2, 10, 100, 1000});
            n = maxForCase;
        }

        cases.push_back({b, n});
        remaining -= n;
    }

    if (rnd.next(0, 1)) shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (auto [b, n] : cases) {
        println(b, n);
    }

    return 0;
}
