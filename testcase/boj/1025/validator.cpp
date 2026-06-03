#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 9, "n");
    inf.readSpace();
    int m = inf.readInt(1, 9, "m");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readLine(format("[0-9]{%d}", m), format("row_%d", i + 1));
    }

    inf.readEof();
}
