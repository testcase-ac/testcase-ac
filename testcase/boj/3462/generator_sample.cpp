#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

static int clampToLimit(long long x) {
    return static_cast<int>(max(1LL, min(1000000000LL, x)));
}

static pair<int, int> makeCase(int mode) {
    if (mode == 0) {
        int n = rnd.next(1, 80);
        int m = rnd.next(1, n);
        return {n, m};
    }

    if (mode == 1) {
        int n = rnd.next(1, 1000000000);
        return {n, rnd.next(1, min(n, 8))};
    }

    if (mode == 2) {
        int n = rnd.next(1, 1000000000);
        int gap = rnd.next(0, min(n - 1, 8));
        return {n, n - gap};
    }

    if (mode == 3) {
        int bit = rnd.next(0, 29);
        int base = clampToLimit(1LL << bit);
        int n = clampToLimit(base + rnd.next(0, min(base - 1, 200000)));
        int m = rnd.next(1, n);
        return {n, m};
    }

    if (mode == 4) {
        int n = rnd.next(999999900, 1000000000);
        int m = rnd.next(1, n);
        return {n, m};
    }

    int n = rnd.next(1, 1000000000);
    int m = rnd.next(1, n);
    return {n, m};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> cases = {
        {1, 1},
        {2, 1},
        {2, 2},
        {4, 2},
        {1000000000, 1},
        {1000000000, 1000000000},
    };

    int d = rnd.next(12, 40);
    while (static_cast<int>(cases.size()) < d) {
        cases.push_back(makeCase(rnd.next(0, 5)));
    }

    shuffle(cases.begin(), cases.end());

    println(static_cast<int>(cases.size()));
    for (auto [n, m] : cases) {
        println(n, m);
    }

    return 0;
}
