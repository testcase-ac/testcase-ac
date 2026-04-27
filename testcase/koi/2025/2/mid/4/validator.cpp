#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 1000000, "Q");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readLong(-1000000000LL, 1000000000LL, "A_i");
        if (i < n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    for (int i = 1; i <= q; ++i) {
        inf.readLong(-1000000000LL, 1000000000LL, "X_i");
        if (i < q) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
