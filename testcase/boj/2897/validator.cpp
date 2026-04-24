#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions
    int R = inf.readInt(2, 50, "R");
    inf.readSpace();
    int C = inf.readInt(2, 50, "C");
    inf.readEoln();

    // Read grid rows
    for (int i = 0; i < R; i++) {
        // Read entire line (should be exactly C chars, no spaces)
        string row = inf.readLine("[^]+", "row");
        ensuref((int)row.size() == C,
                "Row %d has length %d but expected %d", i+1, (int)row.size(), C);
        for (int j = 0; j < C; j++) {
            char ch = row[j];
            bool ok = (ch == '.' || ch == '#' || ch == 'X');
            ensuref(ok,
                    "Invalid character at row %d, column %d: '%c'", i+1, j+1, ch);
        }
    }

    inf.readEof();
    return 0;
}
