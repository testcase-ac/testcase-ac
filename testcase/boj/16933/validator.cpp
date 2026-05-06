#include "testlib.h"
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, K
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 1000, "M");
    inf.readSpace();
    int K = inf.readInt(1, 10, "K");
    inf.readEoln();

    // Build the regex for each row: exactly M characters, each '0' or '1'
    string row_regex = string("[01]{") + to_string(M) + "," + to_string(M) + "}";
    vector<string> grid;
    grid.reserve(N);

    // Read the map
    for (int i = 0; i < N; i++) {
        string row = inf.readLine(row_regex.c_str(), "row");
        grid.push_back(row);
    }

    // Check that start and end are open cells ('0')
    ensuref(grid[0][0] == '0',
            "Cell (1,1) must be 0, found '%c'", grid[0][0]);
    ensuref(grid[N-1][M-1] == '0',
            "Cell (N,M) must be 0, found '%c'", grid[N-1][M-1]);

    inf.readEof();
    return 0;
}
