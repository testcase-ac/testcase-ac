#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using Interval = pair<long long, long long>;

const long long kMaxValue = 1000000000LL;

long long boundedStart(long long value) {
    return max(0LL, min(kMaxValue, value));
}

long long boundedLength(long long value) {
    return max(1LL, min(kMaxValue, value));
}

void addInterval(vector<Interval>& intervals, long long start, long long length) {
    intervals.push_back({boundedStart(start), boundedLength(length)});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Interval> intervals;
    int mode = rnd.next(0, 6);

    if (mode == 0) {
        int n = rnd.next(2, 20);
        long long cur = rnd.next(0, 20);
        for (int i = 0; i < n; ++i) {
            long long len = rnd.next(1, 9);
            addInterval(intervals, cur, len);
            cur += len + rnd.next(1, 8);
        }
    } else if (mode == 1) {
        int n = rnd.next(2, 24);
        long long cur = rnd.next(0, 30);
        for (int i = 0; i < n; ++i) {
            long long len = rnd.next(1, 12);
            addInterval(intervals, cur, len);
            cur += len;
        }
    } else if (mode == 2) {
        int n = rnd.next(3, 28);
        long long base = rnd.next(0, 60);
        for (int i = 0; i < n; ++i) {
            long long len = rnd.next(2, 15);
            addInterval(intervals, base + i * rnd.next(1, 4), len);
        }
    } else if (mode == 3) {
        int clusters = rnd.next(2, 5);
        long long base = rnd.next(0, 20);
        for (int c = 0; c < clusters; ++c) {
            int sz = rnd.next(2, 10);
            long long center = base + c * rnd.next(25, 45);
            long long span = rnd.next(8, 18);
            for (int i = 0; i < sz; ++i) {
                long long start = center + rnd.next(0LL, span / 2);
                long long end = center + span + rnd.next(0LL, span / 2);
                addInterval(intervals, start, end - start);
            }
        }
    } else if (mode == 4) {
        int n = rnd.next(3, 24);
        long long base = rnd.next(0, 50);
        long long outerLen = rnd.next(30, 80);
        addInterval(intervals, base, outerLen);
        for (int i = 1; i < n; ++i) {
            long long leftPad = rnd.next(0LL, outerLen / 2);
            long long right = rnd.next(leftPad + 1, outerLen);
            addInterval(intervals, base + leftPad, right - leftPad);
        }
    } else if (mode == 5) {
        addInterval(intervals, 0, 1);
        addInterval(intervals, 0, kMaxValue);
        addInterval(intervals, kMaxValue, 1);
        addInterval(intervals, kMaxValue - rnd.next(1, 20), rnd.next(1, 20));
        int extra = rnd.next(0, 12);
        for (int i = 0; i < extra; ++i) {
            long long start = rnd.next(0LL, kMaxValue);
            long long maxLen = kMaxValue - start + 1;
            addInterval(intervals, start, rnd.next(1LL, min(1000LL, maxLen)));
        }
    } else {
        int n = rnd.next(6, 36);
        for (int i = 0; i < n; ++i) {
            int family = rnd.next(0, 2);
            if (family == 0) {
                long long start = i * 10 + rnd.next(0, 3);
                addInterval(intervals, start, rnd.next(1, 8));
            } else if (family == 1) {
                long long start = 100 + rnd.next(0, 20);
                addInterval(intervals, start, rnd.next(10, 35));
            } else {
                long long start = 200 + i * rnd.next(1, 3);
                addInterval(intervals, start, rnd.next(2, 10));
            }
        }
    }

    shuffle(intervals.begin(), intervals.end());

    if ((int)intervals.size() > 200) {
        intervals.resize(200);
    }

    println((int)intervals.size());
    for (auto [start, length] : intervals) {
        println(start, length);
    }

    return 0;
}
