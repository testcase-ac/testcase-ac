#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // We expect exactly 3 lines, each with 3 integers between 0 and 8 inclusive,
    // all distinct, representing the 8-puzzle configuration.
    vector<bool> seen(9, false);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int x = inf.readInt(0, 8, "cell");
            // Check for duplicates
            ensuref(!seen[x],
                    "Duplicate number %d at position (%d, %d)", x, i+1, j+1);
            seen[x] = true;
            if (j < 2) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }
    // By pigeonhole principle, 9 distinct values in [0,8] cover all numbers.
    // No further global constraints (solvability is for the solution, not the validator).

    inf.readEof();
    return 0;
}
