#include "testlib.h"

#include <algorithm>
#include <array>
#include <utility>
#include <vector>
using namespace std;

using int64 = long long;

constexpr int64 MAX_VALUE = 1000000000000000LL;

int64 randValue(int64 lo, int64 hi) {
    return rnd.next(lo, hi);
}

int64 randCost() {
    int mode = rnd.next(0, 4);
    if (mode == 0) return 1;
    if (mode == 1) return randValue(1, 20);
    if (mode == 2) return randValue(1000, 1000000);
    if (mode == 3) return randValue(MAX_VALUE - 1000, MAX_VALUE);
    return randValue(1, MAX_VALUE);
}

pair<int64, int64> fibonacciPair() {
    vector<int64> fib = {1, 1};
    while (fib.back() <= 1000000000LL) {
        fib.push_back(fib[fib.size() - 1] + fib[fib.size() - 2]);
    }
    int idx = rnd.next(3, (int)fib.size() - 1);
    int64 scale = randValue(1, max<int64>(1, MAX_VALUE / fib[idx]));
    return {fib[idx] * scale, fib[idx - 1] * scale};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 25);
    vector<array<int64, 4>> tests;

    auto add = [&](int64 a, int64 b, int64 p, int64 q) {
        tests.push_back({a, b, p, q});
    };

    add(1, 1, randCost(), randCost());
    add(MAX_VALUE, MAX_VALUE, randCost(), randCost());

    while ((int)tests.size() < t) {
        int mode = rnd.next(0, 6);
        int64 a, b;

        if (mode == 0) {
            a = randValue(1, 1000);
            b = a;
        } else if (mode == 1) {
            b = randValue(1, 1000000);
            int64 multiplier = randValue(1, max<int64>(1, MAX_VALUE / b));
            a = b * multiplier;
        } else if (mode == 2) {
            a = randValue(2, 1000000000LL);
            b = a - 1;
        } else if (mode == 3) {
            tie(a, b) = fibonacciPair();
        } else if (mode == 4) {
            int64 g = randValue(1, 1000000);
            int64 x = randValue(1, 1000000);
            int64 y = randValue(1, 1000000);
            a = min(MAX_VALUE, g * x);
            b = min(MAX_VALUE, g * y);
        } else if (mode == 5) {
            a = randValue(MAX_VALUE - 1000000, MAX_VALUE);
            b = randValue(1, 1000000);
        } else {
            a = randValue(1, MAX_VALUE);
            b = randValue(1, MAX_VALUE);
        }

        int64 p = randCost();
        int64 q = randCost();
        if (rnd.next(0, 1) == 1) swap(a, b);
        add(a, b, p, q);
    }

    shuffle(tests.begin(), tests.end());

    println((int)tests.size());
    for (auto test : tests) {
        println(test[0], test[1], test[2], test[3]);
    }

    return 0;
}
