#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N_MAX = 200000;
    const int Q_MAX = 200000;
    const int A_MAX = 100000000;
    const int X_MAX = 1000;

    int n = inf.readInt(1, N_MAX, "N");
    inf.readSpace();
    int q = inf.readInt(1, Q_MAX, "Q");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(0, A_MAX, "a_i");
        if (i + 1 < n) {
            inf.readSpace();
        }
    }
    inf.readEoln();

    for (int i = 0; i < q; ++i) {
        int t = inf.readInt(0, 2, "t_i");
        inf.readSpace();
        int l = inf.readInt(0, n - 1, "l_i");
        inf.readSpace();
        int r = inf.readInt(l, n - 1, "r_i");
        inf.readSpace();

        if (t == 2) {
            inf.readInt(0, 0, "x_i");
        } else {
            inf.readInt(1, X_MAX, "x_i");
        }
        inf.readEoln();
    }

    inf.readEof();
}
