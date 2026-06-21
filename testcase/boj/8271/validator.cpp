#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "n");
    inf.readEoln();

    vector<bool> hasRookInRow(n, false);
    vector<bool> hasRookInCol(n, false);
    int rookCount = 0;

    for (int row = 0; row < n; ++row) {
        string line = inf.readLine("[.W]{1,1000}", "board_row");
        ensuref(static_cast<int>(line.size()) == n,
                "row %d has length %d, expected %d",
                row + 1,
                static_cast<int>(line.size()),
                n);

        for (int col = 0; col < n; ++col) {
            if (line[col] != 'W') {
                continue;
            }

            ensuref(!hasRookInRow[row], "multiple rooks in row %d", row + 1);
            ensuref(!hasRookInCol[col], "multiple rooks in column %d", col + 1);
            hasRookInRow[row] = true;
            hasRookInCol[col] = true;
            ++rookCount;
        }
    }

    ensuref(1 <= rookCount && rookCount <= n - 1,
            "rook count %d is outside [1, %d]",
            rookCount,
            n - 1);

    inf.readEof();
}
