#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long LIM = 100000000000000000LL;

    int n = inf.readInt(1, 300000, "N");
    inf.readEoln();

    long long prevX = -LIM - 1;
    for (int i = 1; i <= n; ++i) {
        long long x = inf.readLong(-LIM, LIM, "X_i");
        inf.readSpace();
        inf.readLong(1, LIM, "P_i");
        inf.readEoln();
        ensuref(prevX < x, "X_%d must be greater than previous X: previous=%lld current=%lld", i, prevX, x);
        prevX = x;
    }

    int q = inf.readInt(1, 300000, "Q");
    inf.readEoln();

    for (int j = 1; j <= q; ++j) {
        inf.readLong(-LIM, LIM, "S_j");
        inf.readSpace();
        inf.readLong(1, LIM, "T_j");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
