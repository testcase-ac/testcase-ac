#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 20, "N");
        inf.readEoln();

        vector<int> coins = inf.readInts(n, 1, 10000, "coin");
        inf.readEoln();

        for (int i = 1; i < n; ++i) {
            ensuref(coins[i - 1] < coins[i],
                    "coin values must be strictly increasing: coin[%d]=%d, coin[%d]=%d",
                    i, coins[i - 1], i + 1, coins[i]);
        }

        int m = inf.readInt(1, 10000, "M");
        inf.readEoln();
    }

    inf.readEof();
}
