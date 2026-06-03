#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int w = inf.readInt(1, 100, "W");
    inf.readSpace();
    int h = inf.readInt(1, 100, "H");
    inf.readSpace();
    int x = inf.readInt(-100, 100, "X");
    inf.readSpace();
    int y = inf.readInt(-100, 100, "Y");
    inf.readSpace();
    int p = inf.readInt(1, 50, "P");
    inf.readEoln();

    ensuref(h % 2 == 0, "H must be even: %d", h);

    for (int i = 0; i < p; ++i) {
        int px = inf.readInt(-300, 300, "x_i");
        inf.readSpace();
        int py = inf.readInt(-300, 300, "y_i");
        inf.readEoln();
    }

    inf.readEof();
}
