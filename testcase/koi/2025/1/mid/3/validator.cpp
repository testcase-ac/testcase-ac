#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 300000, "Q");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readLong(1, 1000000000LL, "D_i");
        if (i < n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    for (int j = 1; j <= q; ++j) {
        inf.readInt(1, n, "X_j");
        inf.readSpace();
        inf.readLong(1, 1000000000LL, "P_j");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
