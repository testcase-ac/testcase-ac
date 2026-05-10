#include "testlib.h"
#include <vector>
#include <string>
#include <queue>
#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read H, W
    int H = inf.readInt(1, 1000, "H");
    inf.readSpace();
    int W = inf.readInt(1, 1000, "W");
    inf.readEoln();

    // 2. Read grid
    vector<string> grid(H);
    for (int i = 0; i < H; ++i) {
        grid[i] = inf.readLine("[1-9\\.]{"+to_string(W)+","+to_string(W)+"}", "grid row");
        ensuref((int)grid[i].size() == W, "Row %d length is %d, expected %d", i+1, (int)grid[i].size(), W);
    }

    // 3. Check that sandcastle does not touch the border
    // That is, for all i==0 or i==H-1 or j==0 or j==W-1, grid[i][j] == '.'
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if (i == 0 || i == H-1 || j == 0 || j == W-1) {
                ensuref(grid[i][j] == '.', 
                    "Sandcastle at border cell (%d, %d) is not empty (value: '%c')", i+1, j+1, grid[i][j]);
            }
        }
    }

    // 4. Check all characters are either '.' or '1'-'9'
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            char c = grid[i][j];
            ensuref((c == '.' || (c >= '1' && c <= '9')),
                "Invalid character '%c' at (%d, %d)", c, i+1, j+1);
        }
    }

    inf.readEof();
}
