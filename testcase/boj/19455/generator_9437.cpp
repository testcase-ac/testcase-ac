#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

struct Query {
    char type;
    int l, r;
    int x;
    bool hasX;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 5);

    int n, m;
    if (scenario == 0) {
        n = rnd.next(1, 4);
        m = rnd.next(1, 8);
    } else if (scenario == 1) {
        n = rnd.next(5, 10);
        m = rnd.next(5, 15);
    } else if (scenario == 2) {
        n = rnd.next(8, 15);
        m = rnd.next(8, 20);
    } else if (scenario == 3) {
        n = rnd.next(3, 15);
        m = rnd.next(n, min(3 * n, 25));
    } else if (scenario == 4) { // mostly queries
        n = rnd.next(5, 12);
        m = rnd.next(5, 20);
    } else { // scenario 5: more AND/OR mixing
        n = rnd.next(5, 15);
        m = rnd.next(10, 25);
    }

    // Bit limits for values and x
    int maxBit = rnd.next(3, 10);              // bits 3..10 -> values up to < 2^10
    int maxVal = (1 << maxBit) - 1;            // < 2^30 guaranteed

    // Generate initial array a
    vector<int> a(n);
    int pat = rnd.next(0, 3);
    if (pat == 0) {
        // random
        for (int i = 0; i < n; ++i)
            a[i] = rnd.next(0, maxVal);
    } else if (pat == 1) {
        // all same
        int base = rnd.next(0, maxVal);
        for (int i = 0; i < n; ++i)
            a[i] = base;
    } else if (pat == 2) {
        // simple increasing-ish pattern
        int mul = rnd.next(1, 3);
        for (int i = 0; i < n; ++i)
            a[i] = (i * mul) & maxVal;
    } else {
        // alternating among 0, maxVal, mid
        int midBit = (maxBit + 1) / 2;
        int mid = (1 << midBit) - 1;
        vector<int> vals = {0, maxVal, mid};
        for (int i = 0; i < n; ++i)
            a[i] = vals[i % (int)vals.size()];
    }

    // Generate queries
    vector<Query> qs;
    qs.reserve(m);
    int countQ = 0;

    for (int i = 0; i < m; ++i) {
        Query q;
        // Decide type
        if (scenario == 4) {
            q.type = '?';
        } else {
            int prob = rnd.next(0, 99);
            if (scenario == 3) {
                // many full-range updates
                if (prob < 60)
                    q.type = (rnd.next(0, 1) == 0 ? '&' : '|');
                else
                    q.type = '?';
            } else if (scenario == 5) {
                // more ANDs, some ORs, few queries
                if (prob < 70)
                    q.type = '&';
                else if (prob < 90)
                    q.type = '|';
                else
                    q.type = '?';
            } else {
                // balanced
                if (prob < 45)
                    q.type = '&';
                else if (prob < 90)
                    q.type = '|';
                else
                    q.type = '?';
            }
        }

        // Decide range [l, r]
        int l, r;
        if (scenario == 3 && i < m / 2) {
            // first half: full range operations
            l = 1;
            r = n;
        } else {
            int style = rnd.next(0, 3);
            if (style == 0) {
                // single element
                l = rnd.next(1, n);
                r = l;
            } else if (style == 1) {
                // full or near full
                if (rnd.next(0, 1) == 0) {
                    l = 1; r = n;
                } else {
                    l = rnd.next(1, n);
                    r = n;
                }
            } else if (style == 2) {
                // small segment
                l = rnd.next(1, n);
                int len = rnd.next(1, min(4, n - l + 1));
                r = l + len - 1;
            } else {
                // arbitrary segment
                l = rnd.next(1, n);
                r = rnd.next(l, n);
            }
        }

        q.l = l;
        q.r = r;

        if (q.type == '?') {
            q.hasX = false;
            q.x = 0;
            ++countQ;
        } else {
            q.hasX = true;
            int choice = rnd.next(0, 4);
            if (choice == 0) {
                q.x = rnd.next(0, maxVal);
            } else if (choice == 1) {
                q.x = 0;
            } else if (choice == 2) {
                q.x = maxVal;
            } else if (choice == 3) {
                int bit = rnd.next(0, maxBit - 1);
                q.x = (1 << bit);
            } else {
                int bit = rnd.next(0, maxBit - 1);
                q.x = maxVal ^ (1 << bit);
            }
        }

        qs.push_back(q);
    }

    // Ensure at least one '?' query exists (for output checking)
    if (countQ == 0) {
        int idx = rnd.next(0, m - 1);
        qs[idx].type = '?';
        qs[idx].hasX = false;
        // l, r unchanged
    }

    // Output
    println(n);
    println(a);
    println(m);
    for (const auto &q : qs) {
        if (q.type == '?') {
            printf("%c %d %d\n", q.type, q.l, q.r);
        } else {
            printf("%c %d %d %d\n", q.type, q.l, q.r, q.x);
        }
    }

    return 0;
}
