#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and excavator type
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    // Excavator type must be one of R, Q, B, N, K
    string t = inf.readToken("[RQBNK]", "excavator_type");
    char type = t[0];
    inf.readEoln();

    // Read the grid
    int count_excavators = 0;
    for (int i = 0; i < N; i++) {
        // Read the i-th row as a token (no whitespace)
        string row = inf.readToken("[^]+", "row");
        // Check length
        ensuref((int)row.size() == N,
                "Row %d has length %d but expected %d", i+1, (int)row.size(), N);
        // Validate each character
        for (int j = 0; j < N; j++) {
            char c = row[j];
            ensuref(c == '.' || c == type,
                    "Invalid character at (%d,%d): expected '.' or '%c', found '%c'",
                    i+1, j+1, type, c);
            if (c == type) count_excavators++;
        }
        inf.readEoln();
    }

    // There must be at least one excavator
    ensuref(count_excavators >= 1,
            "No excavators of type '%c' found in the grid", type);

    inf.readEof();
    return 0;
}
