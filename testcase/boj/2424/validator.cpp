#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read grid dimensions
    int N = inf.readInt(1, 700, "N");
    inf.readSpace();
    int M = inf.readInt(1, 700, "M");
    inf.readEoln();

    // Counters for special symbols
    int cntV = 0, cntY = 0, cntT = 0;

    // Read each row
    for (int i = 0; i < N; i++) {
        // Only the characters '.', 'I', 'V', 'Y', 'T' are allowed
        string row = inf.readLine("[.IVYT]+", "row");
        // Check correct length
        ensuref((int)row.size() == M,
                "Row %d has length %d, but expected %d", i+1, (int)row.size(), M);
        // Count special symbols, ensure at most one per symbol
        for (int j = 0; j < M; j++) {
            char c = row[j];
            if (c == 'V') {
                cntV++;
                ensuref(cntV <= 1, "Multiple pirates 'V' found (at least two)");
            } else if (c == 'Y') {
                cntY++;
                ensuref(cntY <= 1, "Multiple start positions 'Y' found (at least two)");
            } else if (c == 'T') {
                cntT++;
                ensuref(cntT <= 1, "Multiple treasures 'T' found (at least two)");
            }
        }
    }

    // Ensure exactly one of each special symbol
    ensuref(cntV == 1, "Expected exactly one pirate 'V', found %d", cntV);
    ensuref(cntY == 1, "Expected exactly one start 'Y', found %d", cntY);
    ensuref(cntT == 1, "Expected exactly one treasure 'T', found %d", cntT);

    inf.readEof();
    return 0;
}
