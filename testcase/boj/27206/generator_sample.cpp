#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

constexpr int kMaxValue = 100000000;

int nearValue(int center, int radius) {
    int lo = max(1, center - radius);
    int hi = min(kMaxValue, center + radius);
    return rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(3, 30);
    vector<pair<int, int>> runners;

    if (mode == 0) {
        n = rnd.next(3, 8);
        int aBase = rnd.next(1, 100);
        int bBase = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) {
            runners.push_back({nearValue(aBase, 3), nearValue(bBase, 3)});
        }
    } else if (mode == 1) {
        n = rnd.next(3, 25);
        int commonA = rnd.any(vector<int>{1, rnd.next(10, 1000), kMaxValue});
        for (int i = 0; i < n; ++i) {
            int b = rnd.next(1, 1000);
            if (rnd.next(100) < 25) b = rnd.any(vector<int>{1, kMaxValue});
            runners.push_back({commonA, b});
        }
    } else if (mode == 2) {
        n = rnd.next(3, 25);
        int commonB = rnd.any(vector<int>{1, rnd.next(10, 1000), kMaxValue});
        for (int i = 0; i < n; ++i) {
            int a = rnd.next(1, 1000);
            if (rnd.next(100) < 25) a = rnd.any(vector<int>{1, kMaxValue});
            runners.push_back({a, commonB});
        }
    } else if (mode == 3) {
        n = rnd.next(6, 24);
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                runners.push_back({rnd.next(1, 30), nearValue(kMaxValue, 30)});
            } else {
                runners.push_back({nearValue(kMaxValue, 30), rnd.next(1, 30)});
            }
        }
    } else if (mode == 4) {
        n = rnd.next(3, 30);
        vector<int> aChoices = {1, 2, rnd.next(3, 20), rnd.next(90, 120), kMaxValue};
        vector<int> bChoices = {1, 2, rnd.next(3, 20), rnd.next(90, 120), kMaxValue};
        for (int i = 0; i < n; ++i) {
            runners.push_back({rnd.any(aChoices), rnd.any(bChoices)});
        }
    } else {
        n = rnd.next(3, 40);
        int aLo = rnd.next(1, 1000);
        int aHi = rnd.next(aLo, min(kMaxValue, aLo + rnd.next(0, 100000)));
        int bLo = rnd.next(1, 1000);
        int bHi = rnd.next(bLo, min(kMaxValue, bLo + rnd.next(0, 100000)));
        for (int i = 0; i < n; ++i) {
            runners.push_back({rnd.next(aLo, aHi), rnd.next(bLo, bHi)});
        }
    }

    shuffle(runners.begin(), runners.end());

    println(n);
    for (auto [a, b] : runners) {
        println(a, b);
    }

    return 0;
}
