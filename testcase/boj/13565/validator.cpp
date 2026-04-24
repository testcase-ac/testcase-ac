#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions M and N
    int M = inf.readInt(2, 1000, "M");
    inf.readSpace();
    int N = inf.readInt(2, 1000, "N");
    inf.readEoln();

    // Read M rows of the grid
    for (int i = 0; i < M; i++) {
        // Read a token of digits 0/1
        string row = inf.readToken("[01]+", "row");
        // Check exact length
        ensuref((int)row.length() == N,
                "Row %d has length %d but expected %d", i+1, (int)row.length(), N);
        // Each character must be '0' or '1' (regex already enforces this, but double-check)
        for (int j = 0; j < N; j++) {
            char c = row[j];
            ensuref(c == '0' || c == '1',
                    "Invalid character at row %d, col %d: '%c'", i+1, j+1, c);
        }
        // Expect exactly one newline after each row
        inf.readEoln();
    }

    // No extra content
    inf.readEof();
    return 0;
}
