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

        int equalAdjacent = 0;
        for (int i = 1; i < n; ++i) {
            if (h[i - 1] == h[i]) {
                ++equalAdjacent;
            }
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
                long long d = inf.readLong(LLONG_MIN, LLONG_MAX, "d");
                inf.readEoln();

                auto removePair = [&](int left) {
                    if (0 <= left && left + 1 < n && h[left] == h[left + 1]) {
                        --equalAdjacent;
                    }
                };
                auto addPair = [&](int left) {
                    if (0 <= left && left + 1 < n && h[left] == h[left + 1]) {
                        ++equalAdjacent;
                    }
                };

                removePair(p - 1);
                removePair(p);

                __int128 newH = (__int128)h[p] + d;
                ensuref(newH >= H_MIN && newH <= H_MAX,
                        "Height after update out of range at position %d (must be in [%lld, %lld])",
                        p, H_MIN, H_MAX);
                h[p] = (long long)newH;

                addPair(p - 1);
                addPair(p);

                ensuref(equalAdjacent == 0,
                        "Heights must satisfy h[i-1] != h[i] for all 0 < i < n after update %d",
                        qi + 1);
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
