#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

using int64 = long long;

const int64 LIMIT = 1000000000000000000LL;

int64 randomSmall() {
    return rnd.next(1LL, 40LL);
}

int64 randomLarge() {
    return rnd.next(900000000000000000LL, LIMIT);
}

int64 randomValue() {
    int mode = rnd.next(0, 3);
    if (mode == 0) return randomSmall();
    if (mode == 1) return rnd.next(1LL, 1000000LL);
    return randomLarge();
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(12, 35);
    vector<pair<int64, int64>> cases;

    cases.push_back({1, 1});
    cases.push_back({2, rnd.next(1LL, 4LL)});
    cases.push_back({3, 1});
    cases.push_back({31, 3});
    cases.push_back({LIMIT, LIMIT});

    while ((int)cases.size() < t) {
        int mode = rnd.next(0, 6);
        int64 n, k;

        if (mode <= 2) {
            k = randomSmall();
            vector<int64> targets = {1, 2, k + 1, k + 2, 2 * k + 2, 2 * k + 3};
            n = rnd.any(targets);
        } else if (mode == 3) {
            k = rnd.next(1LL, 1000000LL);
            int64 period = 2 * k + 2;
            int64 base = rnd.next(0LL, 1000000LL) * period;
            int64 offset = rnd.next(1LL, min(period, LIMIT - base));
            n = base + offset;
        } else if (mode == 4) {
            k = randomLarge();
            n = rnd.next(1LL, LIMIT);
        } else {
            n = randomValue();
            k = randomValue();
        }

        cases.push_back({n, k});
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (auto [n, k] : cases) {
        println(n, k);
    }

    return 0;
}
