#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read R, C, T
    int R = inf.readInt(6, 50, "R");
    inf.readSpace();
    int C = inf.readInt(6, 50, "C");
    inf.readSpace();
    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    // Read the grid and locate air purifier cells (-1)
    int purifier_count = 0;
    vector<int> purifier_rows;
    for (int r = 1; r <= R; r++) {
        vector<int> row = inf.readInts(C, -1, 1000, "A");
        inf.readEoln();
        for (int c = 1; c <= C; c++) {
            int v = row[c-1];
            if (v == -1) {
                purifier_count++;
                // Must be in first column
                ensuref(c == 1,
                        "Air purifier cell at (%d,%d) is in column %d; must be column 1",
                        r, c, c);
                purifier_rows.push_back(r);
            } else {
                // All other cells must be non-negative
                ensuref(v >= 0,
                        "Dust amount at (%d,%d) is %d; must be >= 0",
                        r, c, v);
            }
        }
    }

    // Exactly two purifier cells
    ensuref(purifier_count == 2,
            "Number of air purifier cells is %d; exactly 2 required",
            purifier_count);

    // They must be in consecutive rows
    // purifier_rows is in ascending order because we read rows in increasing r
    int r1 = purifier_rows[0];
    int r2 = purifier_rows[1];
    ensuref(r2 == r1 + 1,
            "Air purifier cells are at rows %d and %d; they must be consecutive",
            r1, r2);

    // The purifier must be at least two rows away from top and bottom
    // That means r1 >= 3 and r2 <= R-2
    ensuref(r1 >= 3,
            "Upper purifier row is %d; must be >= 3 to be two rows from the top",
            r1);
    ensuref(r2 <= R - 2,
            "Lower purifier row is %d; must be <= %d to be two rows from the bottom",
            r2, R-2);

    inf.readEof();
    return 0;
}
