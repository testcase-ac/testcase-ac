#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

static const int N = 5;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int K = inf.readInt(0, 22, "K");
    inf.readEoln();
    ensuref(K % 2 == 0, "K must be even, got %d", K);

    bool usedCell[N + 1][N + 1] = {};

    for (int t = 0; t < K; ++t) {
        int x = inf.readInt(1, N, "i");
        inf.readSpace();
        int y = inf.readInt(1, N, "j");
        inf.readEoln();

        ensuref(!(x == 1 && y == 1), "(1,1) must always have a tree, cannot be rock");
        ensuref(!(x == 5 && y == 5), "(5,5) must always have a tree, cannot be rock");
        ensuref(!usedCell[x][y], "Duplicate rock position at (%d,%d)", x, y);
        usedCell[x][y] = true;
    }

    inf.readEof();
}
