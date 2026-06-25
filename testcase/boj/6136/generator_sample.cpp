#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;
    int r;
    vector<tuple<int, int, int>> intervals;

    if (mode == 0) {
        n = rnd.next(1, 12);
        m = rnd.next(1, 18);
        r = rnd.next(1, n);
    } else if (mode == 1) {
        n = rnd.next(20, 80);
        m = rnd.next(20, 45);
        r = rnd.next(1, 15);
    } else if (mode == 2) {
        n = rnd.next(60, 200);
        m = rnd.next(20, 50);
        r = rnd.next(n / 3, n);
    } else if (mode == 3) {
        n = rnd.next(2, 1000000);
        m = rnd.next(1, 12);
        r = rnd.next(max(1, n - 20), n);
    } else if (mode == 4) {
        n = rnd.next(30, 120);
        m = rnd.next(25, 60);
        r = rnd.next(1, n);
    } else {
        n = rnd.next(2, 1000000);
        m = rnd.next(10, 35);
        r = rnd.next(1, n);
    }

    int efficiencyLimit = rnd.next(0, 4) == 0 ? 1000000 : rnd.next(20, 5000);

    auto addInterval = [&](int start, int end, int efficiency) {
        intervals.emplace_back(start, end, efficiency);
    };

    if (mode == 0 || mode == 1) {
        while ((int)intervals.size() < m) {
            int start = rnd.next(0, n - 1);
            int maxLen = min(n - start, max(1, n / 2));
            int end = start + rnd.next(1, maxLen);
            addInterval(start, end, rnd.next(1, efficiencyLimit));
        }
    } else if (mode == 2) {
        while ((int)intervals.size() < m) {
            int center = rnd.next(0, n - 1);
            int start = max(0, center - rnd.next(0, min(center, 12)));
            int end = min(n, center + rnd.next(1, min(n - center, 12)));
            addInterval(start, end, rnd.next(1, efficiencyLimit));
        }
    } else if (mode == 3) {
        addInterval(0, n, efficiencyLimit);
        while ((int)intervals.size() < m) {
            int start = rnd.next(0, n - 1);
            int end = rnd.next(start + 1, n);
            addInterval(start, end, rnd.next(1, efficiencyLimit));
        }
    } else if (mode == 4) {
        int start = rnd.next(0, n - 2);
        int end = rnd.next(start + 1, n);
        for (int i = 0; i < min(m, 4); ++i) {
            addInterval(start, end, rnd.next(1, efficiencyLimit));
        }
        while ((int)intervals.size() < m) {
            int base = rnd.next(0, n - 2);
            int len = rnd.next(1, min(n - base, 10));
            addInterval(base, base + len, rnd.next(1, efficiencyLimit));
        }
    } else {
        int current = rnd.next(0, min(n - 1, 20));
        while ((int)intervals.size() < m && current < n) {
            int maxLen = min(n - current, rnd.next(1, 25));
            int len = rnd.next(1, maxLen);
            addInterval(current, current + len, rnd.next(1, efficiencyLimit));
            current += len + rnd.next(0, min(r + 2, 25));
        }
        while ((int)intervals.size() < m) {
            int start = rnd.next(0, n - 1);
            int end = rnd.next(start + 1, n);
            addInterval(start, end, rnd.next(1, efficiencyLimit));
        }
    }

    shuffle(intervals.begin(), intervals.end());

    println(n, (int)intervals.size(), r);
    for (auto [start, end, efficiency] : intervals) {
        println(start, end, efficiency);
    }

    return 0;
}
