#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 150, "N");
    inf.readSpace();
    int M = inf.readInt(1, 150, "M");
    inf.readEoln();

    vector<string> grid(N);
    for (int i = 0; i < N; ++i) {
        grid[i] = inf.readLine("[\\.\\^-]{1,150}", "row");
        ensuref((int)grid[i].size() == M,
                "Row %d length is %d, expected %d", i + 1, (int)grid[i].size(), M);
    }

    // No further global constraints stated that must be enforced by validator.

    inf.readEof();
}
