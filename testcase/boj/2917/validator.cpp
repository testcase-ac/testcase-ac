#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 500, "N");
    inf.readSpace();
    int M = inf.readInt(1, 500, "M");
    inf.readEoln();

    // Counters for special characters
    int countV = 0, countJ = 0, countPlus = 0;

    // Read the grid rows
    for (int i = 0; i < N; i++) {
        // Read entire line (may contain any chars, validate manually)
        string row = inf.readLine("[^]+", "row");
        // Check length
        ensuref((int)row.size() == M,
                "Row %d: expected length %d but got %d",
                i+1, M, (int)row.size());
        // Check characters
        for (int j = 0; j < M; j++) {
            char c = row[j];
            ensuref(c == '.' || c == '+' || c == 'V' || c == 'J',
                    "Row %d, Column %d: invalid character '%c'",
                    i+1, j+1, c);
            if (c == 'V') countV++;
            if (c == 'J') countJ++;
            if (c == '+') countPlus++;
        }
    }

    // Validate counts of special symbols
    ensuref(countV == 1,
            "Expected exactly one 'V', but found %d", countV);
    ensuref(countJ == 1,
            "Expected exactly one 'J', but found %d", countJ);
    ensuref(countPlus >= 1,
            "Expected at least one '+', but found %d", countPlus);

    // No further global assumptions (e.g., connectivity) are stated.
    inf.readEof();
    return 0;
}
