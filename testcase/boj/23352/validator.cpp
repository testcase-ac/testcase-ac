#include "testlib.h"
#include <vector>
#include <queue>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M
    int N = inf.readInt(1, 50, "N");
    inf.readSpace();
    int M = inf.readInt(1, 50, "M");
    inf.readEoln();

    // Read grid
    vector<vector<int>> grid(N, vector<int>(M));
    for (int i = 0; i < N; ++i) {
        grid[i] = inf.readInts(M, 0, 9, "A_i");
        inf.readEoln();
    }

    // Check that all lines are read
    inf.readEof();

    // --- Global property: nothing is implied except the grid constraints ---
    // The problem does not guarantee that there is at least one non-zero cell,
    // nor that all non-zero cells are connected, nor any other global property.
    // The only constraints are:
    // - N, M in [1, 50]
    // - Each A[i][j] in [0, 9]
    // - Input format

    // No further validation is needed.

    return 0;
}
