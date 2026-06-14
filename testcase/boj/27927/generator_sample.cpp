#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 14);
    long long m = rnd.next(1, 100);
    if (rnd.next(0, 9) == 0) m = 1000000000LL;

    vector<pair<long long, long long>> intervals;
    intervals.reserve(n);

    if (mode == 0) {
        long long center = rnd.next(1LL, m);
        long long radius = min<long long>(m - 1, rnd.next(0LL, min(20LL, m - 1)));
        for (int i = 0; i < n; ++i) {
            long long s = rnd.next(max(1LL, center - radius), center);
            long long e = rnd.next(center, min(m, center + radius));
            intervals.push_back({s, e});
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            long long day = 1 + (m - 1) * i / max(1, n - 1);
            long long wiggle = rnd.next(0LL, min(3LL, m - 1));
            long long s = max(1LL, day - wiggle);
            long long e = min(m, day + rnd.next(0LL, min(3LL, m - 1)));
            intervals.push_back({s, e});
        }
    } else if (mode == 2) {
        long long baseS = rnd.next(1LL, m);
        long long baseE = rnd.next(baseS, m);
        for (int i = 0; i < n; ++i) {
            long long s = rnd.next(baseS, baseE);
            long long e = rnd.next(s, baseE);
            intervals.push_back({s, e});
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 1) == 0) {
                long long e = rnd.next(1LL, min(m, 10LL));
                intervals.push_back({1, e});
            } else {
                long long s = rnd.next(max(1LL, m - 9), m);
                intervals.push_back({s, m});
            }
        }
    } else if (mode == 4) {
        long long sharedS = rnd.next(1LL, m);
        long long sharedE = rnd.next(sharedS, m);
        for (int i = 0; i < n; ++i) {
            if (i % 3 == 0) {
                intervals.push_back({sharedS, sharedE});
            } else {
                long long s = rnd.next(1LL, m);
                long long e = rnd.next(s, m);
                intervals.push_back({s, e});
            }
        }
    } else {
        for (int i = 0; i < n; ++i) {
            long long s = rnd.next(1LL, m);
            long long e = rnd.next(s, m);
            intervals.push_back({s, e});
        }
    }

    if (rnd.next(0, 3) == 0) {
        shuffle(intervals.begin(), intervals.end());
    }

    println(n, m);
    for (auto interval : intervals) {
        println(interval.first, interval.second);
    }

    return 0;
}
