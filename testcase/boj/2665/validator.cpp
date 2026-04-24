#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(1, 50, "n");
    inf.readEoln();

    // Read the grid
    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        // Read a line of 0/1
        grid[i] = inf.readLine("[01]+", "grid_row");
        // Check length is exactly n
        ensuref((int)grid[i].length() == n,
                "Row %d length must be %d, but got %d",
                i+1, n, (int)grid[i].length());
    }

    // Check start and end are white (1)
    ensuref(grid[0][0] == '1',
            "Start cell (1,1) must be '1', but got '%c'",
            grid[0][0]);
    ensuref(grid[n-1][n-1] == '1',
            "End cell (%d,%d) must be '1', but got '%c'",
            n, n, grid[n-1][n-1]);

    // No extra data
    inf.readEof();
    return 0;
}
