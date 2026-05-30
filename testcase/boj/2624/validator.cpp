#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read T: the bill amount (0 < T ≤ 10,000)
    int T = inf.readInt(1, 10000, "T");
    inf.readEoln();

    // Read k: number of coin types (0 < k ≤ 100)
    int k = inf.readInt(1, 100, "k");
    inf.readEoln();

    const long long LIMIT = 2147483647LL;
    vector<long long> ways(T + 1, 0);
    ways[0] = 1;

    // Read each coin type: p_i (value) and n_i (count)
    for (int i = 0; i < k; i++) {
        // coin value p_i: 0 < p_i ≤ T
        int p = inf.readInt(1, T, "p_i");
        // exactly one space
        inf.readSpace();
        // coin count n_i: 0 < n_i ≤ 1000
        int n = inf.readInt(1, 1000, "n_i");
        inf.readEoln();

        vector<long long> next(T + 1, 0);
        for (int r = 0; r < p; ++r) {
            long long window = 0;
            for (int value = r, used = 0; value <= T; value += p, ++used) {
                window += ways[value];
                if (used > n) {
                    window -= ways[value - (n + 1) * p];
                }
                next[value] = min(window, LIMIT + 1);
            }
        }
        ways.swap(next);
    }

    ensuref(ways[T] <= LIMIT, "number of exchange methods exceeds 2^31 - 1");

    inf.readEof();
    return 0;
}
