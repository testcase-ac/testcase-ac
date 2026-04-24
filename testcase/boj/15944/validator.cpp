#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, D
    int N = inf.readInt(1, 500, "N");
    inf.readSpace();
    int M = inf.readInt(1, 500, "M");
    inf.readSpace();
    int D = inf.readInt(1, 100, "D");
    inf.readEoln();

    // Check D does not exceed dimensions
    ensuref(D <= N, "D (%d) must be <= N (%d)", D, N);
    ensuref(D <= M, "D (%d) must be <= M (%d)", D, M);

    // Read grid
    vector<string> grid;
    grid.reserve(N);
    for (int i = 0; i < N; i++) {
        // Read a token consisting of . and #
        string row = inf.readToken("[\\.\\#]+", (string("row_") + to_string(i)).c_str());
        inf.readEoln();
        // Check row length
        ensuref((int)row.length() == M,
                "Length of row %d is %d but expected %d", i, (int)row.length(), M);
        // Characters are already validated by regex
        grid.push_back(row);
    }

    // Check start and end are free of obstacles
    ensuref(grid[0][0] == '.',
            "Start cell (1,1) must be '.', found '%c'", grid[0][0]);
    ensuref(grid[N-1][M-1] == '.',
            "End cell (N,M) must be '.', found '%c'", grid[N-1][M-1]);

    inf.readEof();
    return 0;
}
