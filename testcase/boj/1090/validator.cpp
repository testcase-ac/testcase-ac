#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N: number of checkers
    int N = inf.readInt(1, 50, "N");
    inf.readEoln();

    vector<long long> xs(N), ys(N);

    for (int i = 0; i < N; ++i) {
        xs[i] = inf.readLong(1LL, 1000000LL, "x_i");
        inf.readSpace();
        ys[i] = inf.readLong(1LL, 1000000LL, "y_i");
        inf.readEoln();
    }

    inf.readEof();
}
