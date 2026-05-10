#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXN = 100000;
    const int MAXQ = 100000;
    const long long MINH = 1LL;
    const long long MAXH = 1000000000LL;

    int n = inf.readInt(1, MAXN, "n");
    inf.readEoln();

    // Read heights h_1..h_n
    vector<long long> h = inf.readLongs(n, MINH, MAXH, "h_i");
    inf.readEoln();

    int Q = inf.readInt(1, MAXQ, "Q");
    inf.readEoln();

    for (int qi = 0; qi < Q; ++qi) {
        int l = inf.readInt(1, n, "l");
        inf.readSpace();
        int r = inf.readInt(1, n, "r");
        inf.readSpace();
        int w = inf.readInt(1, n, "w");
        inf.readEoln();

        ensuref(l <= r, "Query %d: l (%d) must be <= r (%d)", qi + 1, l, r);
        int maxWidth = r - l + 1;
        ensuref(w <= maxWidth,
                "Query %d: w (%d) must be <= r-l+1 (%d)", qi + 1, w, maxWidth);
    }

    inf.readEof();
}
