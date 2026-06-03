#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 5) {
        n = rnd.next(12, 25);
    } else {
        n = rnd.next(2, 10);
    }
    int m = rnd.next(1, n);

    vector<int> fees(n);
    int feeMode = rnd.next(0, 4);
    for (int i = 0; i < n; ++i) {
        if (feeMode == 0) {
            fees[i] = rnd.next(0, 20);
        } else if (feeMode == 1) {
            fees[i] = rnd.next(0, 1) ? 0 : 10000;
        } else if (feeMode == 2) {
            fees[i] = rnd.next(9990, 10000);
        } else if (feeMode == 3) {
            fees[i] = i * rnd.next(0, 10000 / max(1, n - 1));
        } else {
            fees[i] = rnd.next(0, 10000);
        }
    }
    shuffle(fees.begin(), fees.end());

    vector<pair<long long, long long>> intervals;
    if (mode == 0) {
        long long s = rnd.next(1LL, 1000000000LL);
        long long e = rnd.next(s, 1000000000LL);
        intervals.push_back({s, e});
    } else if (mode == 1) {
        long long left = rnd.next(1LL, 100LL);
        long long right = rnd.next(left + m, left + m + 40);
        for (int i = 0; i < m; ++i) {
            long long s = left + rnd.next(0, i);
            long long e = right - rnd.next(0, m - 1 - i);
            intervals.push_back({s, e});
        }
    } else if (mode == 2) {
        long long day = rnd.next(1LL, 60LL);
        for (int i = 0; i < m; ++i) {
            long long len = rnd.next(1LL, 8LL);
            intervals.push_back({day, day + len - 1});
            day += len + rnd.next(1LL, 5LL);
        }
    } else if (mode == 3) {
        long long start = rnd.next(1LL, 1000000000LL - 100);
        long long pivot = start + rnd.next(0LL, 30LL);
        for (int i = 0; i < m; ++i) {
            if (rnd.next(0, 1) == 0) {
                long long s = rnd.next(start, pivot);
                intervals.push_back({s, pivot});
            } else {
                long long e = rnd.next(pivot, start + 100);
                intervals.push_back({pivot, e});
            }
        }
    } else if (mode == 4) {
        for (int i = 0; i < m; ++i) {
            long long s = rnd.next(0, 1) ? rnd.next(1LL, 20LL) : rnd.next(999999980LL, 1000000000LL);
            long long e = rnd.next(s, 1000000000LL);
            intervals.push_back({s, e});
        }
    } else {
        for (int i = 0; i < m; ++i) {
            long long s = rnd.next(1LL, 200LL);
            long long e = rnd.next(s, min(1000000000LL, s + rnd.next(0LL, 60LL)));
            intervals.push_back({s, e});
        }
    }
    shuffle(intervals.begin(), intervals.end());

    println(n, m);
    println(fees);
    for (auto interval : intervals) {
        println(interval.first, interval.second);
    }

    return 0;
}
