#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 50, "N");
    inf.readSpace();
    int m = inf.readInt(2, 50, "M");
    inf.readEoln();

    string rowPattern = "[A-Z]{" + to_string(m) + "," + to_string(m) + "}";
    for (int i = 0; i < n; ++i) {
        inf.readLine(rowPattern, "board_row");
    }

    inf.readEof();
}
