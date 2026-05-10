#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions
    int N = inf.readInt(1, 600, "N");
    inf.readSpace();
    int M = inf.readInt(1, 600, "M");
    inf.readEoln();

    // Read the grid rows
    int countI = 0;
    for (int i = 0; i < N; i++) {
        // Read a line consisting only of characters O, X, I, P
        string row = inf.readLine("[OXIP]{1,600}", "row");
        // Check exact length
        ensuref((int)row.length() == M,
                "Row %d has length %d but expected %d", i+1, (int)row.length(), M);
        // Check each character and count 'I'
        for (int j = 0; j < M; j++) {
            char c = row[j];
            ensuref(c=='O' || c=='X' || c=='I' || c=='P',
                    "Invalid character '%c' at row %d, column %d", c, i+1, j+1);
            if (c == 'I') {
                countI++;
            }
        }
    }

    // Exactly one starting position 'I' must exist
    ensuref(countI == 1,
            "Expected exactly one 'I' but found %d", countI);

    inf.readEof();
    return 0;
}
