#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MIN_N = 3, MAX_N = 10;
    const int MIN_M = 3, MAX_M = 10;
    const int MIN_K = 1, MAX_K = 1000;
    const int MIN_LEN = 1, MAX_LEN = 5;

    int N = inf.readInt(MIN_N, MAX_N, "N");
    inf.readSpace();
    int M = inf.readInt(MIN_M, MAX_M, "M");
    inf.readSpace();
    int K = inf.readInt(MIN_K, MAX_K, "K");
    inf.readEoln();

    vector<string> grid(N);
    for (int i = 0; i < N; ++i) {
        grid[i] = inf.readToken("[a-z]{1,10}", "grid_row");
        inf.readEoln();
        ensuref((int)grid[i].size() == M,
                "Row %d must have exactly %d characters, but has %d",
                i + 1, M, (int)grid[i].size());
    }

    // Precompute total string length upper bound to avoid overflow concerns.
    // Each answer can be as large as (N*M) * 8^(L-1) where L<=5, N,M<=10
    // => max 100 * 8^4 = 409600, well within 64-bit.
    // No extra global simulation constraints are specified beyond movement
    // rules, which are inherently always possible on a toroidal grid.

    for (int qi = 0; qi < K; ++qi) {
        string s = inf.readToken("[a-z]{1,5}", "query_string");
        inf.readEoln();
        int len = (int)s.size();
        ensuref(len >= MIN_LEN && len <= MAX_LEN,
                "Query string %d length must be between %d and %d, got %d",
                qi + 1, MIN_LEN, MAX_LEN, len);
    }

    inf.readEof();
}
