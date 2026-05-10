#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    // Read N
    int N = inf.readInt(3, 16, "N");
    inf.readEoln();
    // Read grid
    vector< vector<int> > grid(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        vector<int> row = inf.readInts(N, 0, 1, "cell");
        for (int j = 0; j < N; j++) {
            grid[i][j] = row[j];
        }
        inf.readEoln();
    }
    // Check initial pipe position is empty
    ensuref(grid[0][0] == 0,
        "Cell (1,1) must be empty (0), found %d", grid[0][0]);
    ensuref(grid[0][1] == 0,
        "Cell (1,2) must be empty (0), found %d", grid[0][1]);
    inf.readEof();
    return 0;
}
