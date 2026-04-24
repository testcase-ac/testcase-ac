#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // We expect exactly a 4x4 grid, each cell with two integers: fish number and direction.
    // Fish numbers: distinct, in [1,16]
    // Directions: in [1,8]
    // Layout: 4 lines, each with 8 integers: a_ij b_ij ... ending with newline.
    vector<bool> seen(17, false);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            // Read fish number
            int a = inf.readInt(1, 16, format("a_%d_%d", i, j).c_str());
            inf.readSpace();
            // Read fish direction
            int b = inf.readInt(1, 8, format("b_%d_%d", i, j).c_str());
            // After each pair, expect a space except at end of line
            if (j < 3) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
            // Check duplicate fish numbers
            ensuref(!seen[a],
                    "Duplicate fish number %d found at cell (%d, %d)", a, i, j);
            seen[a] = true;
        }
    }
    // All fish numbers from 1 to 16 must appear exactly once
    for (int x = 1; x <= 16; x++) {
        ensuref(seen[x],
                "Fish number %d is missing from the grid", x);
    }

    inf.readEof();
    return 0;
}
