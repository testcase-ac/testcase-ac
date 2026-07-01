#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const long long MIN_A = -1000000000LL;
const long long MAX_A = 1000000000LL;

long long clampPitch(long long value) {
    return max(MIN_A, min(MAX_A, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 30);
    vector<long long> a;
    a.reserve(n);

    long long cur = rnd.next(-20, 20);
    if (mode == 5) {
        cur = rnd.any(vector<long long>{MIN_A, MAX_A, MIN_A + 1, MAX_A - 1});
    }
    a.push_back(cur);

    if (mode == 0) {
        // Mostly equal runs with occasional small jumps.
        while ((int)a.size() < n) {
            int run = rnd.next(1, min(6, n - (int)a.size()));
            for (int i = 0; i < run; ++i) {
                a.push_back(cur);
            }
            if ((int)a.size() < n) {
                cur = clampPitch(cur + rnd.any(vector<long long>{-3, -2, -1, 1, 2, 3}));
                a.push_back(cur);
            }
        }
    } else if (mode == 1) {
        // Strictly monotone sequence.
        long long step = rnd.next(1, 12);
        int dir = rnd.any(vector<int>{-1, 1});
        for (int i = 1; i < n; ++i) {
            cur = clampPitch(cur + dir * step);
            a.push_back(cur);
        }
    } else if (mode == 2) {
        // Alternating high and low moves around a base value.
        long long base = rnd.next(-50, 50);
        long long lowGap = rnd.next(1, 15);
        long long highGap = rnd.next(1, 15);
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                a.push_back(base - lowGap);
            } else {
                a.push_back(base + highGap);
            }
        }
    } else if (mode == 3) {
        // Random walk with zero and nonzero deltas mixed.
        for (int i = 1; i < n; ++i) {
            long long delta = rnd.any(vector<long long>{-10, -5, -1, 0, 0, 1, 5, 10});
            cur = clampPitch(cur + delta);
            a.push_back(cur);
        }
    } else if (mode == 4) {
        // Piecewise trend changes, including plateaus.
        while ((int)a.size() < n) {
            int len = rnd.next(1, min(5, n - (int)a.size()));
            long long delta = rnd.any(vector<long long>{-4, -2, 0, 0, 2, 4});
            for (int i = 0; i < len; ++i) {
                cur = clampPitch(cur + delta);
                a.push_back(cur);
            }
        }
    } else {
        // Boundary-focused values near the allowed extremes.
        vector<long long> choices = {
            MIN_A, MIN_A + 1, MIN_A + 2,
            -1, 0, 1,
            MAX_A - 2, MAX_A - 1, MAX_A
        };
        for (int i = 1; i < n; ++i) {
            a.push_back(rnd.any(choices));
        }
    }

    if ((int)a.size() > n) {
        a.resize(n);
    }

    println(n);
    println(a);

    return 0;
}
