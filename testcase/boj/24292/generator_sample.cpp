#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int randomValue(int n) {
    if (n == 1) return 1;
    int mode = rnd.next(0, 4);
    if (mode == 0) return 1;
    if (mode == 1) return n;
    return rnd.next(1, n);
}

int cappedPower(int base, int limit) {
    int value = 1;
    while (value <= limit / base && rnd.next(0, 1)) value *= base;
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int nMode = rnd.next(0, 4);
    if (nMode == 0) {
        n = rnd.next(1, 12);
    } else if (nMode == 1) {
        n = rnd.next(13, 200);
    } else if (nMode == 2) {
        n = rnd.next(1000, 50000);
    } else {
        n = rnd.next(1900000, 2000000);
    }

    int q = rnd.next(1, 25);
    vector<pair<int, int>> pairs;
    pairs.reserve(q);

    vector<pair<int, int>> seeds = {
        {1, 1},
        {1, n},
        {n, 1},
        {n, n},
    };
    shuffle(seeds.begin(), seeds.end());

    for (int i = 0; i < q; ++i) {
        int mode = rnd.next(0, 5);
        int a = 1;
        int b = 1;

        if (i < (int)seeds.size() && rnd.next(0, 1)) {
            a = seeds[i].first;
            b = seeds[i].second;
        } else if (mode == 0) {
            a = randomValue(n);
            b = randomValue(n);
        } else if (mode == 1) {
            int x = rnd.next(1, n);
            a = x;
            b = x;
        } else if (mode == 2) {
            int rootLimit = max(1, min(n, 1500));
            int x = rnd.next(1, rootLimit);
            int square = x * x;
            if (square > n) square = x;
            a = square;
            b = 1;
            if (rnd.next(0, 1)) swap(a, b);
        } else if (mode == 3) {
            int base = rnd.any(vector<int>{2, 3, 5, 7, 11});
            int x = cappedPower(base, n);
            int y = cappedPower(base, n);
            a = x;
            b = y;
        } else if (mode == 4) {
            int g = rnd.next(1, n);
            int maxMul = n / g;
            a = g * rnd.next(1, maxMul);
            b = g * rnd.next(1, maxMul);
        } else {
            a = rnd.next(max(1, n - 30), n);
            b = rnd.next(max(1, n - 30), n);
        }

        pairs.push_back({a, b});
    }

    println(n, q);
    for (auto [a, b] : pairs) println(a, b);

    return 0;
}
