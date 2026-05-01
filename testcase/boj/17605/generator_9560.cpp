#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Op {
    int type;          // 1 = update, 2 = query
    int a, b;          // p for update; l,r for query
    long long d;       // delta for update
};

long long pickNewHeight(int p, const vector<long long>& h) {
    int n = (int)h.size();
    while (true) {
        long long val = rnd.next(1, 20);
        if (val == h[p]) continue;
        if (p > 0 && val == h[p - 1]) continue;
        if (p + 1 < n && val == h[p + 1]) continue;
        return val;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = 1;
    println(T);

    // Single test case with small/medium size for readability
    int n = rnd.next(3, 12);
    vector<long long> h(n);

    // Choose a pattern for initial heights
    int patternType = rnd.next(0, 4);
    if (patternType == 0) {
        // Strictly increasing
        long long base = rnd.next(1, 5);
        h[0] = base;
        for (int i = 1; i < n; ++i) {
            h[i] = h[i - 1] + rnd.next(1, 5);
        }
    } else if (patternType == 1) {
        // Strictly decreasing
        long long base = n + 20;
        for (int i = 0; i < n; ++i) {
            h[i] = base - i; // difference 1
        }
    } else if (patternType == 2) {
        // Single peak near the center
        int peak = n / 2;
        for (int i = 0; i <= peak; ++i) {
            h[i] = i + 1;
        }
        for (int i = peak + 1; i < n; ++i) {
            h[i] = 2 * peak - i + 1;
            if (h[i] < 1) h[i] = 1;
        }
    } else if (patternType == 3) {
        // Alternating high/low (many valleys and peaks)
        long long lowVal = rnd.next(1, 3);
        long long highVal = lowVal + rnd.next(2, 4);
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) h[i] = highVal;
            else h[i] = lowVal;
        }
    } else {
        // Random but fix to avoid equal neighbors
        h[0] = rnd.next(1, 20);
        for (int i = 1; i < n; ++i) {
            long long val = rnd.next(1, 20);
            while (val == h[i - 1]) {
                val = rnd.next(1, 20);
            }
            h[i] = val;
        }
    }

    println(n);
    println(h);

    int qMin = max(1, n - 1);
    int qMax = min(40, n + 10);
    int q = rnd.next(qMin, qMax);
    println(q);

    vector<Op> ops;
    ops.reserve(q);

    int mode = rnd.next(0, 2); // 0: query-heavy, 1: balanced, 2: update-heavy
    int queryCount = 0;

    for (int i = 0; i < q; ++i) {
        int type;
        if (mode == 0) {
            // query-heavy
            type = (rnd.next(100) < 70 ? 2 : 1);
        } else if (mode == 1) {
            // balanced
            type = (rnd.next(100) < 50 ? 2 : 1);
        } else {
            // update-heavy
            type = (rnd.next(100) < 30 ? 2 : 1);
        }

        Op op;
        if (type == 1) {
            // Update: 1 p d
            int p = rnd.next(0, n - 1);
            long long oldVal = h[p];
            long long newVal = pickNewHeight(p, h);
            long long d = newVal - oldVal;
            h[p] = newVal;

            op.type = 1;
            op.a = p;
            op.b = 0;
            op.d = d;
        } else {
            // Query: 2 l r
            int l, r;
            if (rnd.next(0, 3) == 0) {
                // Sometimes single-point segment
                int pos = rnd.next(0, n - 1);
                l = r = pos;
            } else {
                l = rnd.next(0, n - 2);
                r = rnd.next(l + 1, n - 1);
            }
            op.type = 2;
            op.a = l;
            op.b = r;
            op.d = 0;
            ++queryCount;
        }
        ops.push_back(op);
    }

    // Ensure at least one query exists
    if (queryCount == 0) {
        Op &last = ops.back();
        last.type = 2;
        if (rnd.next(0, 1) == 0) {
            int pos = rnd.next(0, n - 1);
            last.a = pos;
            last.b = pos;
        } else {
            int l = rnd.next(0, n - 2);
            int r = rnd.next(l + 1, n - 1);
            last.a = l;
            last.b = r;
        }
        last.d = 0;
        queryCount = 1;
    }

    // Output operations
    for (const Op &op : ops) {
        if (op.type == 1) {
            println(1, op.a, op.d);
        } else {
            println(2, op.a, op.b);
        }
    }

    return 0;
}
