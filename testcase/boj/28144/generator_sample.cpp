#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using int64 = long long;

const int64 LIMIT = 1000000000000000000LL;

int64 boundedMul(int64 a, int64 b) {
    if (a > LIMIT / b) return LIMIT;
    return a * b;
}

int64 randomAround(int64 x) {
    int64 lo = max<int64>(1, x - min<int64>(x - 1, rnd.next(0LL, 5LL)));
    int64 hi = min<int64>(LIMIT, x + rnd.next(0LL, 5LL));
    return rnd.next(lo, hi);
}

pair<int64, int64> thresholdCase() {
    int64 d;
    int mode = rnd.next(0, 3);
    if (mode == 0) {
        d = rnd.next(1LL, 5LL);
    } else if (mode == 1) {
        d = rnd.next(6LL, 1000000LL);
    } else {
        d = rnd.next(1000000000000LL, LIMIT);
    }

    int64 base = d + 1;
    int64 power = 1;
    int steps = rnd.next(1, 20);
    for (int i = 0; i < steps && power < LIMIT; ++i) {
        int64 next = boundedMul(power, base);
        if (next == power) break;
        power = next;
        if (rnd.next(0, 2) == 0) break;
    }

    return {randomAround(power), d};
}

pair<int64, int64> randomLargeCase() {
    int64 n = rnd.next(1LL, LIMIT);
    int64 d = rnd.next(1LL, LIMIT);
    return {n, d};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int64, int64>> cases = {
        {1, 1},
        {2, 1},
        {3, 1},
        {4, 1},
        {LIMIT, 1},
        {LIMIT, LIMIT},
        {42, LIMIT},
        {LIMIT - 1, LIMIT / 2},
    };

    int randomCount = rnd.next(12, 32);
    for (int i = 0; i < randomCount; ++i) {
        int mode = rnd.next(0, 4);
        if (mode <= 2) {
            cases.push_back(thresholdCase());
        } else if (mode == 3) {
            int64 n = rnd.next(1LL, 1000LL);
            int64 d = rnd.next(1LL, 1000LL);
            cases.push_back({n, d});
        } else {
            cases.push_back(randomLargeCase());
        }
    }

    shuffle(cases.begin(), cases.end());

    println(static_cast<int>(cases.size()));
    for (auto [n, d] : cases) {
        println(n, d);
    }

    return 0;
}
