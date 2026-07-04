#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

struct TestCase {
    int n;
    int a;
    int b;
    vector<int> u;
};

static vector<int> makeDemand(int n, int mode) {
    vector<int> u(n, 0);

    if (mode == 0) {
        u[n - 1] = rnd.next(1, 3);
        int extra = rnd.next(1, min(4, n));
        for (int i = 0; i < extra; ++i) {
            int pos = rnd.next(0, n - 1);
            u[pos] = min(20, u[pos] + rnd.next(1, 3));
        }
    } else if (mode == 1) {
        int lo = max(0, n - 5);
        for (int i = lo; i < n; ++i) {
            u[i] = rnd.next(0, 5);
        }
        u[n - 1] = max(1, u[n - 1]);
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            u[i] = rnd.next(0, 8);
        }
        u[n - 1] = rnd.next(1, 8);
    } else {
        u[n - 1] = rnd.next(1, 20);
        if (n >= 2) {
            u[rnd.next(0, n - 2)] = rnd.next(1, 20);
        }
    }

    while (accumulate(u.begin(), u.end(), 0) < 2) {
        int pos = rnd.next(0, n - 1);
        u[pos] = min(20, u[pos] + 1);
    }

    return u;
}

static TestCase makeCase(int mode) {
    TestCase tc;

    if (mode == 0) {
        tc.n = rnd.next(1, 8);
        tc.a = 1;
        tc.b = 2;
    } else if (mode == 1) {
        tc.n = rnd.next(2, 12);
        tc.a = rnd.next(1, min(6, tc.n + 2));
        tc.b = rnd.next(tc.a + 1, min(20, tc.a + 8));
    } else if (mode == 2) {
        tc.n = rnd.next(12, 20);
        tc.a = rnd.next(1, 19);
        tc.b = rnd.next(tc.a + 1, 20);
    } else {
        tc.n = rnd.next(1, 20);
        vector<pair<int, int>> pairs = {{1, 20}, {2, 20}, {7, 20}, {19, 20}};
        auto p = rnd.any(pairs);
        tc.a = p.first;
        tc.b = p.second;
    }

    tc.u = makeDemand(tc.n, mode);
    return tc;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(6, 18);
    println(t);

    for (int i = 0; i < t; ++i) {
        TestCase tc = makeCase(i % 4);
        println(tc.n, tc.a, tc.b);
        println(tc.u);
    }

    return 0;
}
