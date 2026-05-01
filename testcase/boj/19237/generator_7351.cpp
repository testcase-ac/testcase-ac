#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Grid size N, small enough for manual verification
    int N = rnd.next(2, 10);
    // Smell duration k
    int k = rnd.next(1, 1000);

    // Use a checkerboard pattern to place sharks so no two are adjacent,
    // guaranteeing each has at least one empty neighboring cell.
    int parity = rnd.next(0, 1);
    vector<pair<int,int>> allowed;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if ((i + j) % 2 == parity) {
                allowed.emplace_back(i, j);
            }
        }
    }
    int maxM = allowed.size();
    // Number of sharks M, at least 2
    int M = rnd.next(2, maxM);

    // Randomly pick M positions from the allowed set
    shuffle(allowed.begin(), allowed.end());
    vector<pair<int,int>> sharks(allowed.begin(), allowed.begin() + M);

    // Build the grid
    vector<vector<int>> grid(N, vector<int>(N, 0));
    for (int i = 0; i < M; i++) {
        auto [x, y] = sharks[i];
        grid[x][y] = i + 1;  // shark numbers 1..M
    }

    // Output N, M, k
    println(N, M, k);
    // Output the grid
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d%c", grid[i][j], j + 1 == N ? '\n' : ' ');
        }
    }

    // Initial directions for each shark (1=up,2=down,3=left,4=right)
    vector<int> initDir(M);
    for (int i = 0; i < M; i++) {
        initDir[i] = rnd.next(1, 4);
    }
    println(initDir);

    // Priority tables: for each shark 1..M, for directions 1..4 (up,down,left,right)
    // we output a random permutation of [1,2,3,4]
    for (int i = 0; i < M; i++) {
        for (int d = 1; d <= 4; d++) {
            vector<int> p = {1, 2, 3, 4};
            shuffle(p.begin(), p.end());
            println(p);
        }
    }

    return 0;
}
