#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

struct TestCase {
    int n;
    int k;
    vector<long long> a;
    vector<long long> b;
};

long long randomNumerator(long long denominator, int mode) {
    if (mode == 0) {
        return 0;
    }
    if (mode == 1) {
        return denominator;
    }
    if (mode == 2) {
        return rnd.next(0LL, min(denominator, 20LL));
    }
    return rnd.next(0LL, denominator);
}

TestCase makeCase(int mode) {
    TestCase tc;

    if (mode == 0) {
        tc.n = rnd.next(1, 3);
    } else if (mode == 1) {
        tc.n = rnd.next(4, 8);
    } else {
        tc.n = rnd.next(2, 10);
    }

    tc.k = rnd.next(0, tc.n - 1);
    if (mode == 2) {
        tc.k = tc.n - 1;
    }

    tc.a.resize(tc.n);
    tc.b.resize(tc.n);

    if (mode == 0) {
        for (int i = 0; i < tc.n; ++i) {
            tc.b[i] = rnd.next(1LL, 12LL);
            tc.a[i] = randomNumerator(tc.b[i], rnd.next(0, 3));
        }
    } else if (mode == 1) {
        long long common = rnd.next(1LL, 100LL);
        for (int i = 0; i < tc.n; ++i) {
            tc.b[i] = common;
            tc.a[i] = rnd.next(0LL, common);
        }
    } else if (mode == 2) {
        for (int i = 0; i < tc.n; ++i) {
            tc.b[i] = rnd.next(1LL, 1000LL);
            tc.a[i] = rnd.next(0LL, tc.b[i]);
        }
    } else if (mode == 3) {
        for (int i = 0; i < tc.n; ++i) {
            tc.b[i] = rnd.next(999999900LL, 1000000000LL);
            tc.a[i] = rnd.next(0LL, tc.b[i]);
        }
    } else {
        for (int i = 0; i < tc.n; ++i) {
            tc.b[i] = rnd.next(10LL, 500LL);
            if (i < tc.n / 2) {
                tc.a[i] = rnd.next(0LL, tc.b[i] / 5);
            } else {
                tc.a[i] = tc.b[i] - rnd.next(0LL, tc.b[i] / 5);
            }
        }
        shuffle(tc.a.begin(), tc.a.end());
        shuffle(tc.b.begin(), tc.b.end());
        for (int i = 0; i < tc.n; ++i) {
            tc.a[i] = min(tc.a[i], tc.b[i]);
        }
    }

    return tc;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int caseCount = rnd.next(3, 6);
    vector<int> modes = {0, 1, 2, 3, 4};
    shuffle(modes.begin(), modes.end());

    for (int caseIndex = 0; caseIndex < caseCount; ++caseIndex) {
        TestCase tc = makeCase(modes[caseIndex % static_cast<int>(modes.size())]);
        println(tc.n, tc.k);
        println(tc.a);
        println(tc.b);
    }
    println(0, 0);

    return 0;
}
