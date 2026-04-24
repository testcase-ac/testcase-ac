#include "testlib.h"
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(3, 50, "N");
    inf.readSpace();
    int M = inf.readInt(3, 50, "M");
    inf.readEoln();

    // Read starting position (r, c) and direction d
    int r = inf.readInt(0, N - 1, "r");
    inf.readSpace();
    int c = inf.readInt(0, M - 1, "c");
    inf.readSpace();
    int d = inf.readInt(0, 3, "d");
    inf.readEoln();

    // Read grid
    vector<vector<int>> grid(N, vector<int>(M));
    for (int i = 0; i < N; i++) {
        vector<int> row = inf.readInts(M, 0, 1, "grid");
        for (int j = 0; j < M; j++) {
            grid[i][j] = row[j];
        }
        inf.readEoln();
    }

    // Check that all border cells are walls (1)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (i == 0 || i == N - 1 || j == 0 || j == M - 1) {
                ensuref(grid[i][j] == 1,
                        "Border cell (%d, %d) must be a wall, found %d",
                        i, j, grid[i][j]);
            }
        }
    }

    // Check that starting cell is empty (0)
    ensuref(grid[r][c] == 0,
            "Starting cell (%d, %d) must be empty, found %d",
            r, c, grid[r][c]);

    inf.readEof();
    return 0;
}
