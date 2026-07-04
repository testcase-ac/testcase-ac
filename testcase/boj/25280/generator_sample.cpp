#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Interval {
    int a;
    int b;
};

static void normalize(Interval& interval) {
    if (interval.a > interval.b) {
        swap(interval.a, interval.b);
    }
}

static Interval pointNear(int center, int radius) {
    int value = rnd.next(max(0, center - radius), min(1000000, center + radius));
    return {value, value};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 16);
    vector<Interval> intervals;
    intervals.reserve(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            int center = rnd.any(vector<int>{0, 5, 10, 500000, 999990, 1000000});
            intervals.push_back(pointNear(center, rnd.next(0, 20)));
        }
    } else if (mode == 1) {
        int base = rnd.next(0, 999900);
        int span = rnd.next(1, 1000);
        for (int i = 0; i < n; ++i) {
            int left = rnd.next(base, min(1000000, base + span));
            int right = rnd.next(left, min(1000000, base + span + rnd.next(0, 300)));
            intervals.push_back({left, right});
        }
    } else if (mode == 2) {
        int cursor = rnd.next(0, 20);
        for (int i = 0; i < n; ++i) {
            int width = rnd.next(0, 25);
            int gap = rnd.next(0, 40);
            int left = min(1000000, cursor);
            int right = min(1000000, left + width);
            intervals.push_back({left, right});
            cursor = min(1000000, right + gap + 1);
        }
    } else if (mode == 3) {
        int anchor = rnd.next(0, 1000000);
        for (int i = 0; i < n; ++i) {
            int left = rnd.next(0, anchor);
            int right = rnd.next(anchor, 1000000);
            intervals.push_back({left, right});
        }
    } else {
        n = rnd.next(8, 24);
        for (int i = 0; i < n; ++i) {
            Interval interval{rnd.next(0, 1000000), rnd.next(0, 1000000)};
            normalize(interval);
            intervals.push_back(interval);
        }
    }

    shuffle(intervals.begin(), intervals.end());

    println(static_cast<int>(intervals.size()));
    for (const Interval& interval : intervals) {
        printf("%.1f %.1f\n", interval.a / 10.0, interval.b / 10.0);
    }

    return 0;
}
