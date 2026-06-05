#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

const int MAX_VALUE = 10000000;

int clampValue(long long x) {
    return (int)max(1LL, min<long long>(MAX_VALUE, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> cases;

    cases.push_back({1, rnd.next(1, MAX_VALUE)});
    cases.push_back({MAX_VALUE, rnd.next(1, MAX_VALUE)});
    cases.push_back({rnd.next(1, MAX_VALUE), 1});
    cases.push_back({rnd.next(1, MAX_VALUE), MAX_VALUE});

    int smallCount = rnd.next(4, 10);
    for (int i = 0; i < smallCount; ++i) {
        cases.push_back({rnd.next(1, 80), rnd.next(1, 20)});
    }

    int turnCount = rnd.next(8, 16);
    for (int i = 0; i < turnCount; ++i) {
        int k = rnd.next(1, 200000);
        int step = rnd.next(1, 80);
        long long turnDistance = 1LL * k * step * (step + 1) / 2;
        int offset = rnd.next(-2, 2);
        int n = clampValue(turnDistance + 1 + offset);
        cases.push_back({n, k});
    }

    int largePatternCount = rnd.next(4, 8);
    for (int i = 0; i < largePatternCount; ++i) {
        int k = rnd.next(1, MAX_VALUE);
        long long n;
        if (rnd.next(0, 1) == 0) {
            n = MAX_VALUE - rnd.next(0, 25);
        } else {
            n = 1LL * k * rnd.next(1, 5) + rnd.next(1, 50);
        }
        cases.push_back({clampValue(n), k});
    }

    int randomCount = rnd.next(6, 18);
    for (int i = 0; i < randomCount; ++i) {
        int n = rnd.next(1, MAX_VALUE);
        int k = rnd.next(1, MAX_VALUE);
        cases.push_back({n, k});
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (auto [n, k] : cases) {
        println(n, k);
    }

    return 0;
}
