#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100, "M");
    inf.readEoln();

    // Read grid and validate
    int countK = 0, countH = 0;
    for (int i = 0; i < N; i++) {
        // Read a row token: must consist only of .,#,K,H
        string row = inf.readToken("[.#KH]+", "row");
        // Check length exactly M
        ensuref((int)row.size() == M,
                "Row %d length mismatch: expected %d, got %d",
                i+1, M, (int)row.size());
        // Check each character and count K/H
        for (int j = 0; j < M; j++) {
            char c = row[j];
            ensuref(c == '.' || c == '#' || c == 'K' || c == 'H',
                    "Invalid character '%c' at row %d, col %d", c, i+1, j+1);
            if (c == 'K') countK++;
            if (c == 'H') countH++;
        }
        inf.readEoln();
    }

    // Must have exactly one K and one H
    ensuref(countK == 1, "There must be exactly one 'K', found %d", countK);
    ensuref(countH == 1, "There must be exactly one 'H', found %d", countH);

    inf.readEof();
    return 0;
}
