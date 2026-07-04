#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using Interval = pair<int, int>;

int clampCoord(long long x) {
    if (x < 0) return 0;
    if (x > 1000000000LL) return 1000000000;
    return static_cast<int>(x);
}

int nearby(int base, int radius) {
    return clampCoord(static_cast<long long>(base) + rnd.next(-radius, radius));
}

Interval orderedInterval(int center, int radius) {
    int a = nearby(center, radius);
    int b = nearby(center, radius);
    if (a > b) swap(a, b);
    return {a, b};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(2, 18);
    vector<Interval> intervals;

    if (mode == 0) {
        int center = rnd.any(vector<int>{0, 1, 10, 100, 999999990, 1000000000});
        int radius = rnd.next(0, 15);
        for (int i = 0; i < n; ++i) {
            intervals.push_back(orderedInterval(center, radius));
        }
    } else if (mode == 1) {
        int left = rnd.next(0, 80);
        int right = left + rnd.next(5, 40);
        for (int i = 0; i < n; ++i) {
            int s = clampCoord(static_cast<long long>(left) + rnd.next(0, i + 4));
            int e = clampCoord(static_cast<long long>(right) - rnd.next(0, i + 4));
            intervals.push_back({s, e});
        }
    } else if (mode == 2) {
        int step = rnd.next(2, 20);
        int width = rnd.next(0, 12);
        for (int i = 0; i < n; ++i) {
            int s = rnd.next(0, 50) + i * step;
            int e = s + rnd.next(0, width);
            intervals.push_back({s, e});
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            int a = rnd.any(vector<int>{0, 1, 2, 999999998, 999999999, 1000000000});
            int b = rnd.any(vector<int>{0, 1, 2, 999999998, 999999999, 1000000000});
            intervals.push_back({a, b});
        }
    } else if (mode == 4) {
        int base = rnd.next(0, 1000);
        for (int i = 0; i < n; ++i) {
            int s = base + rnd.next(0, 30);
            int e = base + rnd.next(0, 30);
            intervals.push_back({s, e});
        }
    } else {
        int commonLeft = rnd.next(0, 100);
        int commonRight = commonLeft + rnd.next(1, 60);
        for (int i = 0; i < n; ++i) {
            if (i % 3 == 0) {
                intervals.push_back({commonLeft, commonRight});
            } else if (i % 3 == 1) {
                intervals.push_back({rnd.next(0, commonLeft), commonRight + rnd.next(0, 20)});
            } else {
                intervals.push_back({commonLeft + rnd.next(0, 20), rnd.next(commonRight, commonRight + 40)});
            }
        }
    }

    if (rnd.next(4) == 0) {
        int extra = rnd.next(1, 5);
        for (int i = 0; i < extra; ++i) {
            int x = rnd.any(vector<int>{0, rnd.next(0, 100), 1000000000});
            intervals.push_back({x, x});
        }
    }

    shuffle(intervals.begin(), intervals.end());
    println(static_cast<int>(intervals.size()));
    for (auto [s, e] : intervals) {
        println(s, e);
    }

    return 0;
}
