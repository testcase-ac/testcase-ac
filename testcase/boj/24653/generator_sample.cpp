#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long pickDayInBucket(long long bucket, long long t, int style) {
    long long lo = bucket * t + 1;
    long long hi = min(1000000000LL, (bucket + 1) * t - 1);

    if (style == 0) return lo;
    if (style == 1) return hi;
    if (style == 2 && lo < hi) return rnd.next(lo, min(hi, lo + 3));
    if (style == 3 && lo < hi) return rnd.next(max(lo, hi - 3), hi);
    return rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(1, 30);
    long long t;
    vector<long long> days;

    if (mode == 0) {
        t = rnd.next(2LL, 20LL);
        int buckets = rnd.next(1, min(n, 10));
        for (int i = 0; i < n; ++i) {
            long long bucket = rnd.next(0, buckets - 1);
            days.push_back(pickDayInBucket(bucket, t, rnd.next(5)));
        }
    } else if (mode == 1) {
        t = rnd.next(2LL, 100LL);
        long long bucket = rnd.next(0LL, (1000000000LL - 1) / t);
        for (int i = 0; i < n; ++i) {
            days.push_back(pickDayInBucket(bucket, t, rnd.next(5)));
        }
    } else if (mode == 2) {
        t = rnd.next(2LL, 50LL);
        long long maxBucket = (1000000000LL - 1) / t;
        n = rnd.next(1, (int)min(25LL, maxBucket + 1));
        vector<long long> buckets;
        for (long long b = 0; b <= maxBucket && (int)buckets.size() < n * 3; ++b) {
            buckets.push_back(b);
        }
        shuffle(buckets.begin(), buckets.end());
        for (int i = 0; i < n; ++i) {
            days.push_back(pickDayInBucket(buckets[i], t, rnd.next(5)));
        }
    } else if (mode == 3) {
        t = rnd.next(2LL, 1000000000LL);
        n = rnd.next(1, 12);
        long long maxBucket = (1000000000LL - 1) / t;
        for (int i = 0; i < n; ++i) {
            long long bucket = rnd.next(0LL, maxBucket);
            days.push_back(pickDayInBucket(bucket, t, rnd.next(2)));
        }
    } else if (mode == 4) {
        t = rnd.next(500000000LL, 1000000000LL);
        n = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            long long bucket = rnd.next(0LL, (1000000000LL - 1) / t);
            days.push_back(pickDayInBucket(bucket, t, rnd.next(5)));
        }
    } else {
        t = rnd.next(2LL, 1000LL);
        n = rnd.next(1, 30);
        long long maxBucket = (1000000000LL - 1) / t;
        for (int i = 0; i < n; ++i) {
            long long bucket;
            if (rnd.next(2) == 0) {
                bucket = rnd.next(0LL, min(5LL, maxBucket));
            } else {
                bucket = rnd.next(max(0LL, maxBucket - 5), maxBucket);
            }
            days.push_back(pickDayInBucket(bucket, t, rnd.next(5)));
        }
    }

    if (rnd.next(2)) {
        shuffle(days.begin(), days.end());
    } else if (rnd.next(2)) {
        sort(days.begin(), days.end());
    }

    println((int)days.size());
    println(days);
    println(t);

    return 0;
}
