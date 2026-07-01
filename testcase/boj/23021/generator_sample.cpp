#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

struct Case {
    int n;
    int m;
    int x;
    int c;
    int d;
    vector<int> a;
    vector<int> b;
};

vector<int> randomLengths(int count, int lo, int hi) {
    vector<int> values;
    values.reserve(count);
    for (int i = 0; i < count; ++i) values.push_back(rnd.next(lo, hi));
    return values;
}

vector<int> duplicateHeavyLengths(int count, int lo, int hi) {
    int distinct = rnd.next(1, min(count, 4));
    vector<int> pool = randomLengths(distinct, lo, hi);

    vector<int> values;
    values.reserve(count);
    for (int i = 0; i < count; ++i) values.push_back(rnd.any(pool));
    shuffle(values.begin(), values.end());
    return values;
}

int clampedWindowCenter(const vector<int>& a, const vector<int>& b, int x) {
    long long center = rnd.any(a);
    if (!b.empty() && rnd.next(0, 1)) center += rnd.any(b) + x;
    if ((int)a.size() >= 2 && rnd.next(0, 2) == 0) center += rnd.any(a) + rnd.any(b) + 2LL * x;
    return (int)max(1LL, min(1000000000LL, center));
}

Case makeCase(int mode) {
    Case tc{};

    if (mode == 0) {
        tc.n = rnd.next(1, 3);
        tc.m = rnd.next(1, 3);
        tc.x = rnd.next(1, 8);
        tc.a = randomLengths(tc.n, 1, 12);
        tc.b = randomLengths(tc.m, 1, 12);
    } else if (mode == 1) {
        tc.n = rnd.next(3, 8);
        tc.m = rnd.next(3, 8);
        tc.x = rnd.next(1, 20);
        tc.a = duplicateHeavyLengths(tc.n, 1, 30);
        tc.b = duplicateHeavyLengths(tc.m, 1, 30);
    } else if (mode == 2) {
        tc.n = rnd.next(6, 12);
        tc.m = rnd.next(6, 12);
        tc.x = rnd.next(1, 1000);
        int base = rnd.next(100, 10000);
        tc.a = randomLengths(tc.n, max(1, base - 50), min(100000000, base + 50));
        tc.b = randomLengths(tc.m, max(1, base - 50), min(100000000, base + 50));
    } else if (mode == 3) {
        tc.n = rnd.next(12, 18);
        tc.m = rnd.next(12, 18);
        tc.x = rnd.next(1, 100000000);
        tc.a = duplicateHeavyLengths(tc.n, 1, 100000000);
        tc.b = duplicateHeavyLengths(tc.m, 1, 100000000);
    } else {
        tc.n = rnd.next(1, 18);
        tc.m = rnd.next(1, 18);
        tc.x = rnd.next(1, 100000000);
        int lo = rnd.next(1, 1000000);
        int hi = rnd.next(lo, min(100000000, lo + rnd.next(0, 1000000)));
        tc.a = randomLengths(tc.n, lo, hi);
        tc.b = randomLengths(tc.m, lo, hi);
    }

    shuffle(tc.a.begin(), tc.a.end());
    shuffle(tc.b.begin(), tc.b.end());

    if (rnd.next(0, 4) == 0) {
        tc.c = 1;
        tc.d = 1000000000;
    } else {
        int center = clampedWindowCenter(tc.a, tc.b, tc.x);
        int width = rnd.next(0, min(1000000000 - center, 100000));
        int back = rnd.next(0, min(center - 1, 100000));
        tc.c = center - back;
        tc.d = center + width;
    }

    return tc;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 5);
    vector<Case> tests;
    tests.reserve(t);
    for (int i = 0; i < t; ++i) tests.push_back(makeCase(rnd.next(0, 4)));

    println(t);
    for (const Case& tc : tests) {
        println(tc.n, tc.m, tc.x, tc.c, tc.d);
        println(tc.a);
        println(tc.b);
    }

    return 0;
}
