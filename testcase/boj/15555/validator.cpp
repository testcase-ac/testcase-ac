#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 3000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 3000, "M");
    inf.readEoln();

    // Read grid: N lines, each exactly M chars of R/G/W
    for (int i = 0; i < N; ++i) {
        string row = inf.readToken("[RGW]{1,3000}", "row");
        inf.readEoln();
        ensuref((int)row.size() == M,
                "Row %d length mismatch: expected %d, got %d",
                i + 1, M, (int)row.size());
    }

    inf.readEof();
}
