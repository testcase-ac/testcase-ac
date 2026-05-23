#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    inf.readInt(1, 1000, "l");
    inf.readEoln();

    // CHECK: leak positions may plausibly be distinct, but the statement does not say so.
    inf.readInts(n, 1, 1000, "position");
    inf.readEoln();

    inf.readEof();
}
