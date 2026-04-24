#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions
    int N = inf.readInt(3, 10, "N");
    inf.readSpace();
    int M = inf.readInt(3, 10, "M");
    inf.readEoln();

    int countO = 0, countR = 0, countB = 0;
    for (int i = 0; i < N; i++) {
        // Read the i-th row
        string row = inf.readLine("[^]+", "row");
        // Check length
        ensuref((int)row.size() == M,
                "Row %d has length %d but expected %d", i, (int)row.size(), M);
        // Check characters and count special items
        for (int j = 0; j < M; j++) {
            char c = row[j];
            bool ok = (c == '.' || c == '#' || c == 'O' || c == 'R' || c == 'B');
            ensuref(ok,
                    "Invalid character '%c' at row %d, column %d", c, i, j);
            if (c == 'O') countO++;
            else if (c == 'R') countR++;
            else if (c == 'B') countB++;
            // Check borders are walls
            if (i == 0 || i == N-1 || j == 0 || j == M-1) {
                ensuref(c == '#',
                        "Border cell at (%d,%d) is '%c' but must be '#'", i, j, c);
            }
        }
    }

    // Check exactly one hole, one red, one blue
    ensuref(countO == 1, "Number of holes is %d but expected exactly 1", countO);
    ensuref(countR == 1, "Number of red marbles is %d but expected exactly 1", countR);
    ensuref(countB == 1, "Number of blue marbles is %d but expected exactly 1", countB);

    inf.readEof();
    return 0;
}
