#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

struct Case {
    int n;
    long long s;
    int k;
};

long long minSum(int k) {
    return 1LL * k * (k + 1) / 2;
}

long long maxSum(int n, int k) {
    return 1LL * k * (2 * n - k + 1) / 2;
}

long long clampSum(long long value) {
    return max(0LL, min(1000000000LL, value));
}

void addCase(vector<Case>& cases, int n, long long s, int k) {
    cases.push_back({n, clampSum(s), k});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Case> cases;

    int smallCount = rnd.next(8, 16);
    for (int i = 0; i < smallCount; ++i) {
        int n = rnd.next(1, 30);
        int k = rnd.next(1, n);
        long long lo = minSum(k);
        long long hi = maxSum(n, k);

        int mode = rnd.next(0, 6);
        long long s;
        if (mode == 0) {
            s = lo;
        } else if (mode == 1) {
            s = hi;
        } else if (mode == 2) {
            s = rnd.next(lo, hi);
        } else if (mode == 3) {
            s = lo - rnd.next(1, 5);
        } else if (mode == 4) {
            s = hi + rnd.next(1, 5);
        } else if (mode == 5) {
            s = rnd.next(0, 100);
        } else {
            s = rnd.next(900000000, 1000000000);
        }
        addCase(cases, n, s, k);
    }

    int mediumCount = rnd.next(3, 7);
    for (int i = 0; i < mediumCount; ++i) {
        int n = rnd.next(31, 500);
        int k = rnd.next(1, n);
        long long lo = minSum(k);
        long long hi = maxSum(n, k);

        int mode = rnd.next(0, 5);
        long long s;
        if (mode == 0) {
            s = lo + rnd.next(0LL, min(20LL, hi - lo));
        } else if (mode == 1) {
            s = hi - rnd.next(0LL, min(20LL, hi - lo));
        } else if (mode == 2) {
            s = rnd.next(lo, hi);
        } else if (mode == 3) {
            s = lo - rnd.next(1, 100);
        } else if (mode == 4) {
            s = hi + rnd.next(1, 100);
        } else {
            s = rnd.next(0, 1000000000);
        }
        addCase(cases, n, s, k);
    }

    addCase(cases, 1, rnd.next(0, 1), 1);
    addCase(cases, 2, rnd.next(0, 3), rnd.next(1, 2));
    addCase(cases, 40000, minSum(40000), 40000);
    addCase(cases, 40000, maxSum(40000, 1), 1);
    addCase(cases, 40000, rnd.next(999900000, 1000000000), rnd.next(1, 40000));
    addCase(cases, 40000, 0, rnd.next(1, 40000));

    shuffle(cases.begin(), cases.end());
    if (cases.size() > 8000) cases.resize(8000);

    println(static_cast<int>(cases.size()));
    for (const Case& tc : cases) {
        println(tc.n, tc.s, tc.k);
    }

    return 0;
}
