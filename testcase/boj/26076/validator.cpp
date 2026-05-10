#include "testlib.h"
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M
    int N = inf.readInt(1, 2000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 2000, "M");
    inf.readEoln();

    // Constraint: 3 <= N*M
    ensuref(1LL * N * M >= 3, "N*M must be at least 3, but got N=%d, M=%d", N, M);

    vector<vector<int>> grid(N, vector<int>(M));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            grid[i][j] = inf.readInt(0, 1, "cell");
            if (j + 1 < M) inf.readSpace();
        }
        inf.readEoln();
    }

    // (1,1) and (N,M) must be 0
    ensuref(grid[0][0] == 0, "(1,1) must be 0 (no obstacle)");
    ensuref(grid[N-1][M-1] == 0, "(N,M) must be 0 (no obstacle)");

    inf.readEof();
}
