#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read R and C
    int R = inf.readInt(1, 100, "R");
    inf.readSpace();
    int C = inf.readInt(1, 100, "C");
    inf.readEoln();

    // Read the grid
    int cnt_x = 0;
    for (int i = 0; i < R; i++) {
        // Read a row token consisting of '.' or 'x'
        string row = inf.readToken("[\\.x]+", "row");
        // Check exact length
        ensuref((int)row.size() == C,
                "Row %d has length %d, but expected %d", i+1, (int)row.size(), C);
        // Validate characters and count 'x'
        for (int j = 0; j < C; j++) {
            char ch = row[j];
            ensuref(ch == '.' || ch == 'x',
                    "Invalid character at row %d, col %d: '%c'", i+1, j+1, ch);
            if (ch == 'x') cnt_x++;
        }
        inf.readEoln();
    }

    // Global property: there must be at least two 'x' cells
    // so that two 1x1 squares can always be formed
    ensuref(cnt_x >= 2,
            "Not enough building cells ('x'): found %d, expected at least 2", cnt_x);

    inf.readEof();
    return 0;
}
