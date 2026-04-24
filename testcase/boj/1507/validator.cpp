#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of cities
    int N = inf.readInt(1, 20, "N");
    inf.readEoln();

    // Read the distance matrix
    vector<vector<int>> d(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        // Read exactly N integers in [0,2500]
        vector<int> row = inf.readInts(N, 0, 2500, "d");
        inf.readEoln();
        d[i] = row;
    }

    // Check diagonal elements are zero, off-diagonals are positive, and symmetry
    for (int i = 0; i < N; i++) {
        ensuref(d[i][i] == 0,
                "Diagonal element d[%d][%d] must be 0, found %d",
                i+1, i+1, d[i][i]);
        for (int j = i+1; j < N; j++) {
            ensuref(d[i][j] >= 1,
                    "Distance d[%d][%d] must be at least 1, found %d",
                    i+1, j+1, d[i][j]);
            ensuref(d[i][j] == d[j][i],
                    "Matrix not symmetric at (%d,%d) vs (%d,%d): %d vs %d",
                    i+1, j+1, j+1, i+1, d[i][j], d[j][i]);
        }
    }

    inf.readEof();
    return 0;
}
