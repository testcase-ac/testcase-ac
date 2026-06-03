#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int m = rnd.next(1, 30);
    int n = rnd.next(1, 80);
    int mode = rnd.next(0, 5);

    vector<pair<int, int>> intervals;
    intervals.reserve(n);

    if (mode == 0) {
        int value = rnd.next(0, m);
        for (int i = 0; i < n; ++i) {
            int a = rnd.next(0, m);
            if (rnd.next(0, 99) < 70) a = value;
            intervals.emplace_back(a, a);
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            int a = rnd.next(0, m);
            int b = rnd.next(a, m);
            if (rnd.next(0, 99) < 65) {
                a = 0;
                b = m;
            }
            intervals.emplace_back(a, b);
        }
    } else if (mode == 2) {
        int center = rnd.next(0, m);
        int radius = rnd.next(0, max(0, min(m, 4)));
        for (int i = 0; i < n; ++i) {
            int lo = max(0, center - radius - rnd.next(0, 2));
            int hi = min(m, center + radius + rnd.next(0, 2));
            int a = rnd.next(lo, hi);
            int b = rnd.next(a, hi);
            intervals.emplace_back(a, b);
        }
    } else if (mode == 3) {
        vector<pair<int, int>> patterns = {
            {0, 0}, {m, m}, {0, m}, {0, max(0, m / 2)}, {m / 2, m},
        };
        for (int i = 0; i < n; ++i) intervals.push_back(rnd.any(patterns));
    } else if (mode == 4) {
        int distinct = rnd.next(1, min(n, 8));
        vector<pair<int, int>> base;
        for (int i = 0; i < distinct; ++i) {
            int a = rnd.next(0, m);
            int b = rnd.next(a, m);
            base.emplace_back(a, b);
        }
        for (int i = 0; i < n; ++i) intervals.push_back(rnd.any(base));
    } else {
        for (int i = 0; i < n; ++i) {
            int a = rnd.next(0, m);
            int b = rnd.next(a, m);
            intervals.emplace_back(a, b);
        }
    }

    shuffle(intervals.begin(), intervals.end());

    println(n, m);
    for (auto [a, b] : intervals) println(a, b);

    return 0;
}
