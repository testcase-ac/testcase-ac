#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int r = inf.readInt(1, 29, "R");
    inf.readSpace();
    int c = inf.readInt(1, 29, "C");
    inf.readSpace();
    int w = inf.readInt(1, 29, "W");
    inf.readEoln();

    ensuref(c <= r, "C must be at most R: C=%d, R=%d", c, r);
    ensuref(r + w >= 2 && r + w <= 30, "R + W must be between 2 and 30: R=%d, W=%d", r, w);
    ensuref(c + w >= 2 && c + w <= 30, "C + W must be between 2 and 30: C=%d, W=%d", c, w);

    inf.readEof();
}
