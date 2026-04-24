#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read M and N: 1 ≤ M, N ≤ 100
    vector<int> MN = inf.readInts(2, 1, 100, "MN");
    int M = MN[0];
    int N = MN[1];
    inf.readEoln();

    // Read the grid: N lines, each exactly M characters '0' or '1'
    vector<string> grid(N);
    for (int i = 0; i < N; i++) {
        string row = inf.readLine("[01]{1,100}", "row");
        // enforce exact length M
        ensuref((int)row.size() == M,
                "Length of row %d is %d but expected %d", i+1, (int)row.size(), M);
        grid[i] = row;
    }

    // (1,1) and (N,M) must be open rooms ('0')
    ensuref(grid[0][0] == '0',
            "Start cell (1,1) must be '0', found '%c'", grid[0][0]);
    ensuref(grid[N-1][M-1] == '0',
            "End cell (%d,%d) must be '0', found '%c'", N, M, grid[N-1][M-1]);

    inf.readEof();
    return 0;
}
