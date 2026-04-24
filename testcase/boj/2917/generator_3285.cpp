#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for grid dimensions with weighted bias
    int tN = rnd.next(-2, 2);
    int tM = rnd.next(-2, 2);
    int N, M;
    // Ensure enough cells for V, J, and at least one '+'
    do {
        N = rnd.wnext(10, tN) + 1;  // [1,10]
        M = rnd.wnext(10, tM) + 1;  // [1,10]
    } while (N * M < 3);

    // Initialize grid with empty cells
    vector<string> grid(N, string(M, '.'));

    // Choose distinct positions for V and J
    vector<pair<int,int>> cells;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cells.emplace_back(i, j);
    shuffle(cells.begin(), cells.end());
    auto [vi, vj] = cells[0];
    auto [ji, jj] = cells[1];
    grid[vi][vj] = 'V';
    grid[ji][jj] = 'J';

    // Hyper-parameter for tree density
    double plusRate = rnd.next(0.0, 1.0);
    int plusCnt = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if ((i == vi && j == vj) || (i == ji && j == jj)) continue;
            if (rnd.next() < plusRate) {
                grid[i][j] = '+';
                plusCnt++;
            }
        }
    }
    // Guarantee at least one tree
    if (plusCnt == 0) {
        vector<pair<int,int>> others;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                if (grid[i][j] == '.')
                    others.emplace_back(i, j);
        auto [pi, pj] = rnd.any(others);
        grid[pi][pj] = '+';
    }

    // Output the generated test
    println(N, M);
    for (int i = 0; i < N; i++)
        println(grid[i]);

    return 0;
}
