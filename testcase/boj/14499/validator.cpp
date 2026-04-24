#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read basic parameters
    int N = inf.readInt(1, 20, "N");
    inf.readSpace();
    int M = inf.readInt(1, 20, "M");
    inf.readSpace();
    int x = inf.readInt(0, N - 1, "x");
    inf.readSpace();
    int y = inf.readInt(0, M - 1, "y");
    inf.readSpace();
    int K = inf.readInt(1, 1000, "K");
    inf.readEoln();

    // Read the grid
    vector<vector<int>> grid(N, vector<int>(M));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            grid[i][j] = inf.readInt(0, 9, "grid");
            if (j + 1 < M) inf.readSpace();
        }
        inf.readEoln();
    }

    // Validate that the starting cell is zero
    ensuref(grid[x][y] == 0,
            "The starting cell (%d,%d) must be 0, found %d",
            x, y, grid[x][y]);

    // Read commands
    vector<int> cmds = inf.readInts(K, 1, 4, "command");
    inf.readEoln();

    inf.readEof();
    return 0;
}
