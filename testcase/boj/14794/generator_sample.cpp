#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using int64 = long long;

constexpr int64 kMaxN = 1000000000000000000LL;

int64 clampToN(int64 x, int64 n) {
    return max<int64>(1, min(x, n));
}

pair<int64, int64> randomCase(int mode) {
    if (mode == 0) {
        int64 n = rnd.next(1LL, 25LL);
        return {n, rnd.next(1LL, n)};
    }

    if (mode == 1) {
        int64 n = rnd.next(1LL, 1000000LL);
        int64 k = n - rnd.next(0LL, min<int64>(n - 1, 20));
        return {n, k};
    }

    if (mode == 2) {
        int exp = rnd.next(1, 60);
        int64 base = 1LL << exp;
        int64 n = clampToN(base + rnd.next(-3LL, 3LL), kMaxN);
        int64 k = clampToN((base >> rnd.next(0, exp)) + rnd.next(-3LL, 3LL), n);
        return {n, k};
    }

    if (mode == 3) {
        int64 n = rnd.next(kMaxN - 1000000LL, kMaxN);
        vector<int64> choices = {
            1LL,
            2LL,
            rnd.next(1LL, 1000LL),
            n / 2,
            n - rnd.next(0LL, 1000LL),
            n,
        };
        return {n, clampToN(rnd.any(choices), n)};
    }

    if (mode == 4) {
        int64 n = rnd.next(1LL, 1000000000000LL);
        int64 k = max<int64>(1, n / rnd.next(2LL, 1000000LL) + rnd.next(-5LL, 5LL));
        return {n, min(k, n)};
    }

    int64 n = rnd.next(1LL, kMaxN);
    int64 k = rnd.next(1LL, n);
    return {n, k};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(20, 100);
    vector<pair<int64, int64>> cases;

    cases.push_back({1, 1});
    cases.push_back({2, 1});
    cases.push_back({2, 2});
    cases.push_back({kMaxN, 1});
    cases.push_back({kMaxN, kMaxN});

    int modeCount = 6;
    while ((int)cases.size() < t) {
        cases.push_back(randomCase(rnd.next(0, modeCount - 1)));
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (auto [n, k] : cases) {
        println(n, k);
    }

    return 0;
}
