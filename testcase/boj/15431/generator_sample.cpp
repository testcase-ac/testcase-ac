#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

namespace {
const long long MAX_TIME = 10000000000000000LL;

long long bounded(long long value) {
    return min(max(value, 0LL), MAX_TIME - 1);
}

vector<long long> increasingTimes(int n, long long lo, long long hi) {
    vector<long long> pool;
    for (long long x = lo; x <= hi; ++x) {
        pool.push_back(x);
    }
    shuffle(pool.begin(), pool.end());
    pool.resize(n);
    sort(pool.begin(), pool.end());
    return pool;
}

void printCase(int n,
               int k,
               long long t1,
               long long t2,
               const vector<long long>& measurements,
               const vector<pair<long long, long long>>& intervals) {
    println(n, k, t1, t2);
    println(measurements);
    for (const auto& interval : intervals) {
        println(interval.first, interval.second);
    }
}
}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int n = rnd.next(1, 8);
    int k = rnd.next(1, 8);

    long long t1 = 0;
    long long t2 = 1;
    vector<long long> measurements;
    vector<pair<long long, long long>> intervals;

    if (mode == 0) {
        t1 = rnd.next(0, 40);
        t2 = t1 + rnd.next(1, 80);
        measurements = increasingTimes(n, 0, 120);

        for (int i = 0; i < k; ++i) {
            long long b = rnd.next(0, 220);
            long long e = b + rnd.next(1, 35);
            intervals.push_back({b, e});
        }
    } else if (mode == 1) {
        long long base = MAX_TIME - rnd.next(250, 900);
        t1 = base + rnd.next(0, 120);
        t2 = min(MAX_TIME, t1 + rnd.next(1, 180));
        measurements = increasingTimes(n, base - 150, base + 160);

        for (int i = 0; i < k; ++i) {
            long long b = bounded(base + rnd.next(-220, 180));
            b = min(b, MAX_TIME - 2);
            long long e = min(MAX_TIME - 1, b + rnd.next(1, 80));
            intervals.push_back({b, e});
        }
    } else if (mode == 2) {
        t1 = rnd.next(0, 30);
        t2 = t1 + rnd.next(20, 140);
        measurements = increasingTimes(n, 0, 150);

        for (int i = 0; i < k; ++i) {
            long long start = rnd.next(t1, t2 - 1);
            long long m = rnd.any(measurements);
            long long b = bounded(start + m - rnd.next(0, 4));
            long long e = min(MAX_TIME - 1, b + rnd.next(1, 12));
            intervals.push_back({b, e});
        }
    } else {
        t1 = rnd.next(10, 120);
        t2 = t1 + rnd.next(1, 60);
        measurements = increasingTimes(n, 0, 80);

        long long offset = t2 + measurements.back() + rnd.next(20, 100);
        for (int i = 0; i < k; ++i) {
            long long b = min(MAX_TIME - 2, offset + i * rnd.next(2, 8));
            long long e = min(MAX_TIME - 1, b + rnd.next(1, 20));
            intervals.push_back({b, e});
        }
    }

    printCase(n, k, t1, t2, measurements, intervals);
    return 0;
}
