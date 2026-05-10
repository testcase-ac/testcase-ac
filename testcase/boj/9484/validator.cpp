#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
};

long double area2(const Point &a, const Point &b, const Point &c) {
    // 2 * signed area (can be negative)
    long long x1 = b.x - a.x;
    long long y1 = b.y - a.y;
    long long x2 = c.x - a.x;
    long long y2 = c.y - a.y;
    long long cross = x1 * y2 - x2 * y1;
    if (cross < 0) cross = -cross;
    return (long double)cross;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_T = 100000;
    int t = 0;

    while (true) {
        int n = inf.readInt(0, 2000, "n");
        inf.readEoln();

        if (n == 0) {
            // termination line must be last
            break;
        }

        ++t;
        ensuref(t <= MAX_T, "number of test cases exceeds %d", MAX_T);
        setTestCase(t);

        ensuref(n >= 3, "for non-zero test, n must be at least 3, got %d", n);

        vector<Point> pts(n);
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
            pts[i] = {x, y};
        }

        // Global property: there exists at least one non-degenerate triangle.
        // Check by brute force (O(n^3)), but skip early when found.
        bool hasNonDegenerate = false;
        for (int i = 0; i < n && !hasNonDegenerate; ++i) {
            for (int j = i + 1; j < n && !hasNonDegenerate; ++j) {
                for (int k = j + 1; k < n; ++k) {
                    if (area2(pts[i], pts[j], pts[k]) > 0) {
                        hasNonDegenerate = true;
                        break;
                    }
                }
            }
        }
        ensuref(hasNonDegenerate,
                "all %d points in test %d are collinear; no valid triangle exists",
                n, t);
    }

    inf.readEof();
}
