#include "testlib.h"

#include <algorithm>
#include <cstdint>
#include <vector>

using namespace std;

struct Case {
    uint64_t a;
    uint64_t b;
    uint64_t c;
    int k;
};

static uint64_t modFor(int k) {
    return 1ULL << k;
}

static uint64_t randomValue(int k) {
    uint64_t mod = modFor(k);
    if (k <= 30) {
        return rnd.next(0, static_cast<int>(mod - 1));
    }
    return rnd.next(0LL, static_cast<long long>(mod - 1));
}

static Case makeReachable(int k) {
    uint64_t mod = modFor(k);
    uint64_t a = randomValue(k);
    uint64_t c = rnd.next(1LL, static_cast<long long>(mod - 1));
    uint64_t steps = rnd.next(0LL, static_cast<long long>(min<uint64_t>(mod - 1, 200)));
    uint64_t b = (a + (static_cast<__uint128_t>(c) * steps) % mod) % mod;
    return {a, b, c, k};
}

static Case makeForever(int k) {
    uint64_t mod = modFor(k);
    uint64_t a = randomValue(k);
    uint64_t shift = rnd.next(1, k);
    uint64_t c = 1ULL << shift;
    if (c >= mod) {
        c = 0;
    }

    uint64_t delta;
    if (c == 0) {
        delta = rnd.next(1LL, static_cast<long long>(mod - 1));
    } else {
        uint64_t g = c;
        do {
            delta = rnd.next(1LL, static_cast<long long>(mod - 1));
        } while (delta % g == 0);
    }

    uint64_t b = (a + delta) % mod;
    return {a, b, c, k};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Case> cases;
    int n = rnd.next(8, 18);
    cases.push_back({0, 0, 1, 1});
    cases.push_back({4294967295ULL, 0, 1, 32});

    while (static_cast<int>(cases.size()) < n) {
        int mode = rnd.next(0, 5);
        int k = rnd.any(vector<int>{1, 2, 3, 4, 8, 16, 31, 32});
        uint64_t mod = modFor(k);

        if (mode == 0) {
            uint64_t a = randomValue(k);
            cases.push_back({a, a, randomValue(k), k});
        } else if (mode == 1) {
            cases.push_back(makeReachable(k));
        } else if (mode == 2) {
            cases.push_back(makeForever(k));
        } else if (mode == 3) {
            uint64_t a = rnd.next(0LL, static_cast<long long>(min<uint64_t>(mod - 1, 10)));
            uint64_t b = (mod + a - rnd.next(1LL, static_cast<long long>(min<uint64_t>(mod - 1, 10)))) % mod;
            uint64_t c = rnd.next(1LL, static_cast<long long>(min<uint64_t>(mod - 1, 7)));
            cases.push_back({a, b, c, k});
        } else {
            uint64_t a = randomValue(k);
            uint64_t b = randomValue(k);
            uint64_t c = randomValue(k);
            cases.push_back({a, b, c, k});
        }
    }

    shuffle(cases.begin(), cases.end());
    for (const Case& tc : cases) {
        println(tc.a, tc.b, tc.c, tc.k);
    }
    println(0, 0, 0, 0);
    return 0;
}
