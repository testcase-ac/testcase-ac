#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "T");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        int l = inf.readInt(1, 1000000, "L_i");
        inf.readSpace();
        int r = inf.readInt(l, 1000000, "R_i");
        inf.readEoln();
    }

    inf.readEof();
}
