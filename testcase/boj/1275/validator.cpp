#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int Q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    inf.readLongs(N, -2147483648LL, 2147483647LL, "initial");
    inf.readEoln();

    for (int i = 0; i < Q; i++) {
        inf.readInt(1, N, "x_i");
        inf.readSpace();
        inf.readInt(1, N, "y_i");
        inf.readSpace();
        inf.readInt(1, N, "a_i");
        inf.readSpace();
        inf.readLong(-2147483648LL, 2147483647LL, "b_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
