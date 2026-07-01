#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using Interval = pair<int, int>;

Interval makeInterval(int a, int len) {
    return {a, a + max(1, len)};
}

vector<Interval> makeCase(int mode, int n) {
    vector<Interval> intervals;

    if (mode == 0) {
        int cur = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            int len = rnd.next(1, 5);
            intervals.push_back(makeInterval(cur, len));
            cur += len + rnd.next(0, 3);
        }
    } else if (mode == 1) {
        int start = rnd.next(1, 15);
        for (int i = 0; i < n; ++i) {
            int len = rnd.next(2, 12);
            intervals.push_back(makeInterval(start, len));
            start += rnd.next(0, 2);
        }
    } else if (mode == 2) {
        int base = rnd.next(1, 20);
        int outerLen = rnd.next(n + 5, n + 25);
        intervals.push_back(makeInterval(base, outerLen));
        for (int i = 1; i < n; ++i) {
            int a = rnd.next(base, base + outerLen - 1);
            int b = rnd.next(a + 1, base + outerLen);
            intervals.push_back({a, b});
        }
    } else if (mode == 3) {
        int cur = rnd.next(1, 10);
        for (int i = 0; i < n; ++i) {
            int len = rnd.next(1, 6);
            intervals.push_back(makeInterval(cur, len));
            cur += len;
        }
    } else {
        for (int i = 0; i < n; ++i) {
            int a = rnd.next(1, 60);
            int b = rnd.next(a + 1, a + rnd.next(1, 25));
            intervals.push_back({a, b});
        }
    }

    shuffle(intervals.begin(), intervals.end());
    return intervals;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int cases = rnd.next(3, 8);
    int firstN = rnd.next(1, 12);
    println(firstN);
    vector<Interval> first = makeCase(rnd.next(0, 4), firstN);
    for (const auto& interval : first) {
        println(interval.first, interval.second);
    }

    for (int tc = 1; tc < cases; ++tc) {
        int n;
        if (tc == cases - 1 && rnd.next(0, 4) == 0) {
            n = rnd.next(1, 50);
        } else {
            n = rnd.next(1, 14);
        }

        println(n);
        vector<Interval> intervals;
        if (rnd.next(0, 9) == 0) {
            int right = 1000000000;
            for (int i = 0; i < n; ++i) {
                int len = rnd.next(1, 200);
                int b = right - rnd.next(0, 1000);
                int a = max(1, b - len);
                intervals.push_back({a, b});
            }
            shuffle(intervals.begin(), intervals.end());
        } else {
            intervals = makeCase(rnd.next(0, 4), n);
        }

        for (const auto& interval : intervals) {
            println(interval.first, interval.second);
        }
    }

    println(0);
    return 0;
}
