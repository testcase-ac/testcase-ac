#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "N");
    inf.readSpace();
    int m = inf.readInt(0, 10000, "M");
    inf.readSpace();
    inf.readInt(1, 10000000, "k");
    inf.readEoln();

    inf.readInts(n, 1, 10000, "A_i");
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        inf.readInt(1, n, "v");
        inf.readSpace();
        inf.readInt(1, n, "w");
        inf.readEoln();
    }

    inf.readEof();
}
