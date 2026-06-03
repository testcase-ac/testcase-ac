#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int clampValue(int value) {
    return max(1, min(3000, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    int k;

    if (mode == 0) {
        n = 1;
        k = rnd.next(0, 3000);
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        k = 0;
    } else if (mode == 2) {
        n = rnd.next(2, 12);
        k = rnd.next(1, 3);
    } else if (mode == 3) {
        n = rnd.next(6, 20);
        k = rnd.next(4, 30);
    } else if (mode == 4) {
        n = rnd.next(3, 15);
        k = rnd.next(1000, 3000);
    } else {
        n = rnd.next(10, 35);
        k = rnd.next(0, 3000);
    }

    vector<pair<int, int>> ranges;
    ranges.reserve(n);

    int center = rnd.next(1, 3000);
    for (int i = 0; i < n; ++i) {
        int a;
        int b;

        if (mode == 0) {
            a = rnd.next(1, 3000);
            b = rnd.next(a, 3000);
        } else if (mode == 1) {
            int value = rnd.next(1, 25);
            int width = rnd.next(0, 4);
            a = value;
            b = min(3000, value + width);
        } else if (mode == 2) {
            int drift = rnd.next(-2, 2);
            center = clampValue(center + drift);
            int width = rnd.next(0, 6);
            a = clampValue(center - rnd.next(0, width));
            b = clampValue(center + rnd.next(0, width));
            if (a > b) swap(a, b);
        } else if (mode == 3) {
            int base = (i % 2 == 0) ? rnd.next(1, 200) : rnd.next(2800, 3000);
            int width = rnd.next(0, 50);
            a = clampValue(base - width / 2);
            b = clampValue(base + width);
        } else if (mode == 4) {
            a = rnd.next(1, 3000);
            b = rnd.next(a, 3000);
        } else {
            int bucket = rnd.next(0, 3);
            int lo = bucket == 0 ? 1 : bucket == 1 ? 900 : bucket == 2 ? 1800 : 2700;
            int hi = min(3000, lo + rnd.next(10, 250));
            a = rnd.next(lo, hi);
            b = rnd.next(a, min(3000, a + rnd.next(0, 300)));
        }

        ranges.emplace_back(a, b);
    }

    println(n, k);
    for (const auto& range : ranges) {
        println(range.first, range.second);
    }

    return 0;
}
