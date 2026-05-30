#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_TESTS = 100000;
    const int MAX_TOTAL_POINTS = 2500000; // CHECK: practical cap; statement has no testcase-count bound.
    int t = 0;
    int totalPoints = 0;

    while (true) {
        int n = inf.readInt(0, 2000, "n");
        inf.readEoln();

        if (n == 0) {
            // termination line must be last
            break;
        }

        ++t;
        ensuref(t <= MAX_TESTS, "number of test cases exceeds %d", MAX_TESTS);
        setTestCase(t);

        ensuref(n >= 3, "for non-zero test, n must be at least 3, got %d", n);
        totalPoints += n;
        ensuref(totalPoints <= MAX_TOTAL_POINTS,
                "total number of points exceeds %d", MAX_TOTAL_POINTS);

        set<pair<int,int>> seen;

        for (int i = 0; i < n; ++i) {
            int x = inf.readInt(-10000, 10000, "x");
            inf.readSpace();
            int y = inf.readInt(-10000, 10000, "y");
            inf.readEoln();

            pair<int,int> p = {x, y};
            ensuref(!seen.count(p),
                    "duplicate point at index %d: (%d, %d)", i + 1, x, y);
            seen.insert(p);
        }
    }

    inf.readEof();
}
