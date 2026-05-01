#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Grid size
    int N = rnd.next(5, 12);
    // Total virus candidate cells
    int maxK = min(10, N * N);
    int K = rnd.next(1, maxK);
    // Number to activate
    int M = rnd.next(1, K);
    // Wall density hyper-parameter
    double wallProb = rnd.next(10, 40) / 100.0;

    // Initialize all cells as empty (0)
    vector<vector<int>> grid(N, vector<int>(N, 0));

    // Prepare list of all positions
    vector<pair<int,int>> cells;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cells.emplace_back(i, j);

    // Shuffle and pick first K as virus-candidate cells
    shuffle(cells.begin(), cells.end());
    for (int i = 0; i < K; i++) {
        auto [r, c] = cells[i];
        grid[r][c] = 2;
    }
    // For remaining cells, randomly assign walls or leave empty
    for (int i = K; i < (int)cells.size(); i++) {
        auto [r, c] = cells[i];
        if (rnd.next() < wallProb)
            grid[r][c] = 1;
        // else remains 0
    }

    // Output
    println(N, M);
    for (int i = 0; i < N; i++) {
        println(grid[i]);
    }

    return 0;
}
