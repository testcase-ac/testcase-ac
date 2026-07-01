#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Segment {
    long long a;
    long long b;
};

long long randomPoint(long long n) {
    if (n <= 60) {
        return rnd.next(1LL, n);
    }

    int bucket = rnd.next(0, 4);
    if (bucket == 0) return rnd.next(1LL, min(30LL, n));
    if (bucket == 1) return n - rnd.next(0LL, min(29LL, n - 1));
    if (bucket == 2) return rnd.next(1LL, min(n, 1000000LL));
    return rnd.next(1LL, n);
}

Segment makeSegment(long long n, int mode) {
    if (mode == 0) {
        long long a = randomPoint(n);
        long long span = rnd.next(0LL, min(12LL, n - a));
        return {a, a + span};
    }

    if (mode == 1) {
        long long b = randomPoint(n);
        long long span = rnd.next(0LL, min(12LL, b - 1));
        return {b - span, b};
    }

    long long a = randomPoint(n);
    long long b = randomPoint(n);
    if (a > b) swap(a, b);
    return {a, b};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 5);
    long long n;
    if (sizeMode == 0) {
        n = rnd.next(1LL, 8LL);
    } else if (sizeMode <= 2) {
        n = rnd.next(9LL, 80LL);
    } else if (sizeMode == 3) {
        n = rnd.next(1000LL, 1000000LL);
    } else {
        n = 1000000000000000000LL - rnd.next(0LL, 1000LL);
    }

    int k = rnd.next(1, 30);
    vector<Segment> segments;
    segments.reserve(k);

    int pattern = rnd.next(0, 5);
    if (pattern == 0) {
        for (int i = 0; i < k; ++i) {
            segments.push_back(makeSegment(n, rnd.next(0, 2)));
        }
    } else if (pattern == 1) {
        long long start = 1;
        for (int i = 0; i < k; ++i) {
            if (start > n) start = rnd.next(1LL, n);
            long long len = rnd.next(1LL, min(10LL, n - start + 1));
            long long end = start + len - 1;
            segments.push_back({start, end});
            start = end + rnd.next(1LL, min(5LL, max(1LL, n - end)));
        }
    } else if (pattern == 2) {
        long long center = randomPoint(n);
        for (int i = 0; i < k; ++i) {
            long long left = rnd.next(0LL, min(20LL, center - 1));
            long long right = rnd.next(0LL, min(20LL, n - center));
            segments.push_back({center - left, center + right});
        }
    } else if (pattern == 3) {
        long long a = randomPoint(n);
        long long b = randomPoint(n);
        if (a > b) swap(a, b);
        for (int i = 0; i < k; ++i) {
            if (rnd.next(0, 3) == 0) {
                segments.push_back({a, b});
            } else {
                segments.push_back(makeSegment(n, rnd.next(0, 2)));
            }
        }
    } else {
        for (int i = 0; i < k; ++i) {
            long long p = randomPoint(n);
            segments.push_back({p, p});
        }
    }

    shuffle(segments.begin(), segments.end());

    println(n, k);
    for (const Segment& segment : segments) {
        println(segment.a, segment.b);
    }

    return 0;
}
