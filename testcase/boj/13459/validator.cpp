#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions
    int N = inf.readInt(3, 10, "N");
    inf.readSpace();
    int M = inf.readInt(3, 10, "M");
    inf.readEoln();

    vector<string> board(N);
    int cntR = 0, cntB = 0, cntO = 0;
    for (int i = 0; i < N; i++) {
        // Read each row as an entire line
        string row = inf.readLine("[^]+", "row");
        // Check length
        ensuref((int)row.size() == M,
                "Row %d length is %d but expected %d", i + 1, (int)row.size(), M);
        // Check characters and count special tokens
        for (int j = 0; j < M; j++) {
            char c = row[j];
            ensuref(c == '.' || c == '#' || c == 'O' || c == 'R' || c == 'B',
                    "Invalid character '%c' at row %d, column %d", c, i + 1, j + 1);
            if (c == 'R') cntR++;
            if (c == 'B') cntB++;
            if (c == 'O') cntO++;
            // Check border walls
            if (i == 0 || i == N - 1 || j == 0 || j == M - 1) {
                ensuref(c == '#',
                        "Border cell at row %d, column %d must be '#', found '%c'",
                        i + 1, j + 1, c);
            }
        }
        board[i] = row;
    }

    // Check exactly one R, one B, one O
    ensuref(cntR == 1, "There must be exactly one red ball 'R', found %d", cntR);
    ensuref(cntB == 1, "There must be exactly one blue ball 'B', found %d", cntB);
    ensuref(cntO == 1, "There must be exactly one hole 'O', found %d", cntO);

    inf.readEof();
    return 0;
}
