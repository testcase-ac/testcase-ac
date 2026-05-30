#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N: number of points
    int N = inf.readInt(1, 10000, "N");
    inf.readEoln();

    // Constraints for coordinates
    const int MINC = 1;
    const int MAXC = 500;

    for (int i = 0; i < N; ++i) {
        inf.readInt(MINC, MAXC, "x");
        inf.readSpace();
        inf.readInt(MINC, MAXC, "y");
        inf.readEoln();
    }

    inf.readEof();
}
