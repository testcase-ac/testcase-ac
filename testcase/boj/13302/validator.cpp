#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    int m = inf.readInt(0, n, "M");
    inf.readEoln();

    int previous = 0;
    for (int i = 0; i < m; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int day = inf.readInt(1, n, "day");
        ensuref(previous < day, "unavailable days must be strictly increasing: %d after %d", day, previous);
        previous = day;
    }
    if (m > 0) {
        inf.readEoln();
    }

    inf.readEof();
}
