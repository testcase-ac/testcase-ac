#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int h = inf.readInt(1, 600, "H");
    inf.readSpace();
    int w = inf.readInt(1, 600, "W");
    inf.readEoln();

    vector<string> grid(h);
    for (int i = 0; i < h; ++i) {
        grid[i] = inf.readToken("[0-9]{" + to_string(w) + "}", "row");
        inf.readEoln();
    }

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            int rows = 1 + (i > 0) + (i + 1 < h);
            int cols = 1 + (j > 0) + (j + 1 < w);
            int limit = rows * cols;
            ensuref(grid[i][j] - '0' <= limit,
                    "cell (%d, %d) has count %c greater than local maximum %d",
                    i + 1, j + 1, grid[i][j], limit);
        }
    }

    // CHECK: The statement guarantees at least one solution exists. This
    // validator enforces the local numeric feasibility implied by the grid
    // boundary; full inverse-minesweeper existence is left to trusted providers.
    inf.readEof();
}
