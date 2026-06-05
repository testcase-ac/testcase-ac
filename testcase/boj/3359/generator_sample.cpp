#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

pair<int, int> makePair(int a, int b) {
    if (a > b) swap(a, b);
    if (a == b) {
        if (b < 999) ++b;
        else --a;
    }
    return {a, b};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    vector<pair<int, int>> rects;

    if (mode == 0) {
        n = rnd.next(1, 8);
        int lo = rnd.next(1, 20);
        int hi = rnd.next(lo + 1, min(999, lo + 80));
        for (int i = 0; i < n; ++i) {
            int a = rnd.next(lo, hi - 1);
            int b = rnd.next(a + 1, hi);
            rects.push_back({a, b});
        }
    } else if (mode == 1) {
        n = rnd.next(4, 16);
        int low = rnd.next(1, 12);
        int high = rnd.next(100, 999);
        for (int i = 0; i < n; ++i) {
            int a = rnd.next(low, min(998, low + 8));
            int b = rnd.next(max(a + 1, high - 30), high);
            rects.push_back({a, b});
        }
    } else if (mode == 2) {
        n = rnd.next(3, 20);
        int base = rnd.next(1, 980);
        for (int i = 0; i < n; ++i) {
            int gap = rnd.next(1, 18);
            int a = min(998, base + rnd.next(0, 12));
            rects.push_back(makePair(a, min(999, a + gap)));
        }
    } else if (mode == 3) {
        n = rnd.next(2, 18);
        vector<pair<int, int>> choices = {{1, 2}, {1, 999}, {2, 999}, {500, 501}, {998, 999}};
        for (int i = 0; i < n; ++i) {
            rects.push_back(rnd.any(choices));
        }
    } else if (mode == 4) {
        n = rnd.next(6, 24);
        for (int i = 0; i < n; ++i) {
            int a, b;
            if (i % 2 == 0) {
                a = rnd.next(1, 40);
                b = rnd.next(700, 999);
            } else {
                a = rnd.next(450, 998);
                b = rnd.next(a + 1, 999);
            }
            rects.push_back({a, b});
        }
    } else {
        n = rnd.next(20, 40);
        int a = rnd.next(1, 998);
        int b = rnd.next(a + 1, 999);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                int delta = rnd.next(-5, 5);
                rects.push_back(makePair(max(1, min(998, a + delta)), max(2, min(999, b + delta))));
            } else {
                rects.push_back({a, b});
            }
        }
    }

    if (rnd.next(0, 1)) shuffle(rects.begin(), rects.end());

    println(n);
    for (auto [a, b] : rects) println(a, b);

    return 0;
}
