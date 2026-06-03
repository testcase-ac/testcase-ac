#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "N");
    inf.readSpace();
    int m = inf.readInt(1, 50, "M");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readToken(format("[01]{%d}", m), format("row_%d", i + 1));
        inf.readEoln();
    }

    inf.readInt(0, 1000, "K");
    inf.readEoln();
    inf.readEof();
}
