#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read R, C
    int R = inf.readInt(1, 30000, "R");
    inf.readSpace();
    int C = inf.readInt(1, 30, "C");
    inf.readEoln();

    // Read initial grid
    vector<string> grid(R);
    for (int i = 0; i < R; i++) {
        // each row must be exactly C chars of '.' or 'X'
        string s = inf.readToken("[\\.X]{1,30}", "row");
        ensuref((int)s.size() == C,
                "Length of row %d is %d but expected %d", i+1, (int)s.size(), C);
        grid[i] = s;
        inf.readEoln();
    }

    // Read N throws
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();
    vector<int> throws(N);
    for (int i = 0; i < N; i++) {
        int col = inf.readInt(1, C, "col");
        throws[i] = col - 1;  // zero-index
        inf.readEoln();
    }

    // Prepare blocked sets per column: initial walls and bottom boundary
    vector< set<int> > blocked(C);
    for (int c = 0; c < C; c++) {
        for (int r = 0; r < R; r++) {
            if (grid[r][c] == 'X') {
                blocked[c].insert(r);
            }
        }
        blocked[c].insert(R); // sentinel for the bottom beyond last row
    }

    // Simulate each drop to enforce the "always drop into empty top" rule
    for (int i = 0; i < N; i++) {
        int col = throws[i];
        // Check that the top cell is empty at drop time
        ensuref(grid[0][col] == '.',
                "Drop %d: top cell (1,%d) is not empty, found '%c'",
                i+1, col+1, grid[0][col]);

        // Simulate the falling stone
        int row = 0;
        while (true) {
            // find the first blocked row strictly below current row
            auto it = blocked[col].lower_bound(row + 1);
            // must always exist because we inserted R
            int d = *it;
            int v = d - 1;  // candidate resting row if falling straight down
            if (v == row) {
                // no vertical move possible
                break;
            }
            // we fall to row = v
            row = v;
            // now because below is blocked, try sliding
            bool moved = false;
            // slide left
            if (col - 1 >= 0) {
                if (!blocked[col-1].count(row) && !blocked[col-1].count(row+1)) {
                    col = col - 1;
                    moved = true;
                }
            }
            // if not moved, slide right
            if (!moved && col + 1 < C) {
                if (!blocked[col+1].count(row) && !blocked[col+1].count(row+1)) {
                    col = col + 1;
                    moved = true;
                }
            }
            if (!moved) {
                // come to rest here
                break;
            }
            // else continue falling from new (row, col)
        }

        // Place the stone at (row, col)
        ensuref(grid[row][col] == '.',
                "Drop %d: trying to place stone at occupied cell (%d,%d) found '%c'",
                i+1, row+1, col+1, grid[row][col]);
        grid[row][col] = 'O';
        blocked[col].insert(row);
    }

    // Finally, ensure no extra data
    inf.readEof();

    return 0;
}
