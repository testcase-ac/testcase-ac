#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read grid size N
    int N = inf.readInt(2, 1500, "N");
    inf.readEoln();

    // Read initial grid values
    vector<vector<int>> grid(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            grid[i][j] = inf.readInt(0, 1000, "a_" + to_string(i+1) + "_" + to_string(j+1));
            if (j + 1 < N) inf.readSpace();
        }
        inf.readEoln();
    }

    // Process N update commands
    for (int k = 1; k <= N; k++) {
        // Read command type U or D
        string cmd = inf.readToken("[UD]", "cmd_type");
        inf.readSpace();
        // Read row and column indices
        int r = inf.readInt(1, N, "r_" + to_string(k));
        inf.readSpace();
        int c = inf.readInt(1, N, "c_" + to_string(k));
        inf.readEoln();

        // Apply update, ensuring no negative
        if (cmd == "U") {
            grid[r-1][c-1]++;
        } else {
            ensuref(grid[r-1][c-1] > 0,
                    "Update %d: decrement at cell (%d,%d) would make value negative", 
                    k, r, c);
            grid[r-1][c-1]--;
        }
    }

    inf.readEof();
    return 0;
}
