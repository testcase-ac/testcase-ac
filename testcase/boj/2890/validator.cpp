#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read R and C
    int R = inf.readInt(10, 50, "R");
    inf.readSpace();
    int C = inf.readInt(10, 50, "C");
    inf.readEoln();

    // Read grid
    vector<string> grid(R);
    for (int i = 0; i < R; i++) {
        grid[i] = inf.readLine("[^]+", "row");
        // Check length
        ensuref((int)grid[i].size() == C,
                "Row %d has length %d but expected %d", i+1, (int)grid[i].size(), C);
        // Check characters and positions of S and F
        for (int j = 0; j < C; j++) {
            char ch = grid[i][j];
            if (j == 0) {
                ensuref(ch == 'S', "Row %d, col %d: expected 'S' but found '%c'", i+1, j+1, ch);
            } else if (j == C-1) {
                ensuref(ch == 'F', "Row %d, col %d: expected 'F' but found '%c'", i+1, j+1, ch);
            } else {
                // Middle columns must be '.' or '1'..'9'
                bool ok = (ch == '.' || (ch >= '1' && ch <= '9'));
                ensuref(ok,
                        "Row %d, col %d: invalid character '%c'", i+1, j+1, ch);
            }
        }
    }

    // Collect positions of each team digit
    vector<vector<int>> posRow(10), posCol(10);
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            char ch = grid[i][j];
            if (ch >= '1' && ch <= '9') {
                int d = ch - '0';
                posRow[d].push_back(i);
                posCol[d].push_back(j);
            }
        }
    }

    // Prepare for overlap check and per-row kayak count
    vector<vector<bool>> used(R, vector<bool>(C, false));
    vector<int> rowKayakCount(R, 0);

    // Validate each team's kayak
    for (int d = 1; d <= 9; d++) {
        // Must have exactly 3 cells
        ensuref((int)posRow[d].size() == 3,
                "Team %d has %d cells but expected 3", d, (int)posRow[d].size());
        // All cells must be in the same row
        int r0 = posRow[d][0];
        for (int k = 1; k < 3; k++) {
            ensuref(posRow[d][k] == r0,
                    "Team %d cells are not all in the same row: rows %d and %d",
                    d, r0+1, posRow[d][k]+1);
        }
        // No more than one kayak per row
        rowKayakCount[r0]++;
        ensuref(rowKayakCount[r0] == 1,
                "Multiple kayaks found in row %d", r0+1);

        // Check for overlaps and mark used
        for (int k = 0; k < 3; k++) {
            int c = posCol[d][k];
            ensuref(!used[r0][c],
                    "Overlap at row %d, col %d for team %d", r0+1, c+1, d);
            used[r0][c] = true;
        }

        // Check columns are consecutive
        sort(posCol[d].begin(), posCol[d].end());
        int c0 = posCol[d][0];
        ensuref(posCol[d][1] == c0 + 1 && posCol[d][2] == c0 + 2,
                "Team %d kayak cells are not consecutive: cols %d, %d, %d",
                d, posCol[d][0]+1, posCol[d][1]+1, posCol[d][2]+1);
    }

    // All checks passed
    inf.readEof();
    return 0;
}
