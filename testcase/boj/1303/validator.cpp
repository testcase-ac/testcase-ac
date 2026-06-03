#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100, "m");
    inf.readEoln();

    int white = 0;
    int blue = 0;
    for (int y = 0; y < m; ++y) {
        string row = inf.readToken(format("[WB]{%d}", n), "row");
        inf.readEoln();

        for (char cell : row) {
            if (cell == 'W') {
                ++white;
            } else {
                ++blue;
            }
        }
    }

    ensuref(white > 0, "at least one W soldier is required");
    ensuref(blue > 0, "at least one B soldier is required");

    inf.readEof();
}
