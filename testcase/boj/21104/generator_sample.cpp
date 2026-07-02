#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long LIMIT = 1000000000LL;
    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 12);
    int m = rnd.next(1, 12);

    vector<pair<long long, long long>> intervals;
    vector<long long> points;

    if (mode == 0) {
        long long base = rnd.next(1LL, 40LL);
        for (int i = 0; i < n; ++i) {
            long long l = base + rnd.next(0LL, 20LL);
            long long r = l + rnd.next(0LL, 12LL);
            intervals.push_back({l, r});
        }
        for (int i = 0; i < m; ++i) {
            points.push_back(base + rnd.next(0LL, 35LL));
        }
    } else if (mode == 1) {
        long long center = rnd.next(10LL, 80LL);
        for (int i = 0; i < n; ++i) {
            long long left = rnd.next(0LL, 9LL);
            long long right = rnd.next(0LL, 9LL);
            intervals.push_back({center - left, center + right});
        }
        for (int i = 0; i < m; ++i) {
            points.push_back(max(1LL, center + rnd.next(-12LL, 12LL)));
        }
    } else if (mode == 2) {
        long long cursor = rnd.next(1LL, 20LL);
        for (int i = 0; i < n; ++i) {
            long long len = rnd.next(0LL, 6LL);
            intervals.push_back({cursor, cursor + len});
            cursor += len + rnd.next(0LL, 5LL) + 1;
        }
        for (int i = 0; i < m; ++i) {
            points.push_back(rnd.next(1LL, cursor + 5));
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            long long x = rnd.next(1LL, 30LL);
            intervals.push_back({x, x});
        }
        for (int i = 0; i < m; ++i) {
            points.push_back(rnd.next(1LL, 30LL));
        }
    } else {
        long long base = LIMIT - rnd.next(220LL, 400LL);
        for (int i = 0; i < n; ++i) {
            long long l = base + rnd.next(0LL, 120LL);
            long long r = min(LIMIT, l + rnd.next(0LL, 80LL));
            intervals.push_back({l, r});
        }
        for (int i = 0; i < m; ++i) {
            points.push_back(min(LIMIT, base + rnd.next(0LL, 220LL)));
        }
    }

    if (rnd.next(0, 1) == 1) {
        shuffle(intervals.begin(), intervals.end());
    }
    if (rnd.next(0, 1) == 1) {
        shuffle(points.begin(), points.end());
    }

    println(n, m);
    for (auto interval : intervals) {
        println(interval.first, interval.second);
    }
    for (long long point : points) {
        println(point);
    }

    return 0;
}
