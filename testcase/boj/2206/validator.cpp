#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 1000, "M");
    inf.readEoln();

    // Prepare regex for each row: exactly M characters of '0' or '1'
    string rowRegex = "[01]{" + to_string(M) + "," + to_string(M) + "}";

    // Read the grid
    vector<string> grid(N);
    for (int i = 0; i < N; i++) {
        grid[i] = inf.readToken(rowRegex.c_str(), ("row" + to_string(i+1)).c_str());
        inf.readEoln();
    }

    // Check that start and end are open (0)
    ensuref(grid[0][0] == '0',
            "Start cell (1,1) must be '0', found '%c'", grid[0][0]);
    ensuref(grid[N-1][M-1] == '0',
            "End cell (N,M) must be '0', found '%c'", grid[N-1][M-1]);

    inf.readEof();
    return 0;
}
