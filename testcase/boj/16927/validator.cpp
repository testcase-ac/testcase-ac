#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 300, "n");
    inf.readSpace();
    int m = inf.readInt(2, 300, "m");
    inf.readSpace();
    int r = inf.readInt(1, 1000000000, "r");
    inf.readEoln();

    ensuref(min(n, m) % 2 == 0, "min(n, m) must be even: n=%d, m=%d", n, m);

    for (int i = 0; i < n; ++i) {
        inf.readInts(m, 1, 100000000, "a_ij");
        inf.readEoln();
    }

    inf.readEof();
}
