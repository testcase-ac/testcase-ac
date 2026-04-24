#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, K
    int N = inf.readInt(1, 10, "N");
    inf.readSpace();
    int M = inf.readInt(1, N * N, "M");
    inf.readSpace();
    int K = inf.readInt(1, 1000, "K");
    inf.readEoln();

    // Read nutrient addition A[r][c]
    for (int i = 0; i < N; i++) {
        inf.readInts(N, 1, 100, "A");
        inf.readEoln();
    }

    // Read initial trees, ensure distinct positions
    set<pair<int,int>> seen;
    for (int i = 0; i < M; i++) {
        int x = inf.readInt(1, N, "tree_x");
        inf.readSpace();
        int y = inf.readInt(1, N, "tree_y");
        inf.readSpace();
        int age = inf.readInt(1, 10, "tree_age");
        inf.readEoln();
        pair<int,int> pos = {x, y};
        ensuref(!seen.count(pos),
                "Duplicate tree position at index %d: (%d, %d)", i+1, x, y);
        seen.insert(pos);
    }

    inf.readEof();
    return 0;
}
