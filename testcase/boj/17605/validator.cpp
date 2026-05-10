#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int T_MIN = 1;
    const int T_MAX = 10;
    const int N_MIN = 1;
    const int N_MAX = 100000;
    const int Q_MIN = 1;
    const int Q_MAX = 100000;
    const long long H_MIN = 1LL;
    const long long H_MAX = 1000000000LL;

    int T = inf.readInt(T_MIN, T_MAX, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        int n = inf.readInt(N_MIN, N_MAX, "n");
        inf.readEoln();

        vector<long long> h(n);
        if (n > 0) {
            h = inf.readLongs(n, H_MIN, H_MAX, "h_i");
            inf.readEoln();
        }

        // Check the global property on heights: h_{i-1} != h_i for all 0 < i < n
        for (int i = 1; i < n; ++i) {
            ensuref(h[i - 1] != h[i],
                    "Initial heights must satisfy h[i-1] != h[i] for all 0 < i < n, but h[%d] == h[%d] == %lld",
                    i - 1, i, h[i]);
        }

        int q = inf.readInt(Q_MIN, Q_MAX, "q");
        inf.readEoln();

        // Process q operations, updating h and checking constraints after each update.
        for (int qi = 0; qi < q; ++qi) {
            int type = inf.readInt(1, 2, "type");
            inf.readSpace();
            if (type == 1) {
                // Update: "1 p d"
                int p = inf.readInt(0, n - 1, "p");
                inf.readSpace();
                long long d = inf.readLong(-H_MAX, H_MAX, "d"); // range on d is not specified; choose safe wide range
                inf.readEoln();

                long long newH = h[p] + d;
                ensuref(newH >= H_MIN && newH <= H_MAX,
                        "Height after update out of range at position %d: %lld (must be in [%lld, %lld])",
                        p, newH, H_MIN, H_MAX);
                h[p] = newH;

                // Re-check local neighbors for inequality as guaranteed by statement
                if (p - 1 >= 0) {
                    ensuref(h[p - 1] != h[p],
                            "Heights must satisfy h[i-1] != h[i] after each update, but h[%d] == h[%d] == %lld",
                            p - 1, p, h[p]);
                }
                if (p + 1 < n) {
                    ensuref(h[p] != h[p + 1],
                            "Heights must satisfy h[i-1] != h[i] after each update, but h[%d] == h[%d] == %lld",
                            p, p + 1, h[p]);
                }
            } else {
                // Query: "2 l r"
                int l = inf.readInt(0, n - 1, "l");
                inf.readSpace();
                int r = inf.readInt(0, n - 1, "r");
                inf.readEoln();
                ensuref(l <= r,
                        "Query must satisfy l <= r, but got l = %d, r = %d", l, r);
            }
        }
    }

    inf.readEof();
}
