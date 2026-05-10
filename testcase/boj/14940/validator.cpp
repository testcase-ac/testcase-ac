#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read grid dimensions
    int n = inf.readInt(2, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(2, 1000, "m");
    inf.readEoln();

    // Read the grid and count the number of '2's (the goal cell)
    int goalCount = 0;
    for (int i = 0; i < n; i++) {
        vector<int> row = inf.readInts(m, 0, 2, "grid");
        inf.readEoln();
        for (int j = 0; j < m; j++) {
            if (row[j] == 2) {
                goalCount++;
            }
        }
    }

    // There must be exactly one goal cell
    ensuref(goalCount == 1,
            "There must be exactly one goal cell (value 2), found %d",
            goalCount);

    inf.readEof();
    return 0;
}
