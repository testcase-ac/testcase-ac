#include "testlib.h"
#include <vector>
#include <string>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N, M
    int N = inf.readInt(1, 20, "N");
    inf.readSpace();
    int M = inf.readInt(1, 20, "M");
    inf.readEoln();

    // 2. Read board
    vector<string> board(N);
    int cntA = 0, cntB = 0;
    int ax = -1, ay = -1, bx = -1, by = -1;
    for (int i = 0; i < N; ++i) {
        board[i] = inf.readLine("[A.BX]{"+to_string(M)+","+to_string(M)+"}", "board row");
        ensuref((int)board[i].size() == M, "Row %d length is %d, expected %d", i+1, (int)board[i].size(), M);
        for (int j = 0; j < M; ++j) {
            char c = board[i][j];
            if (c == 'A') {
                cntA++;
                ax = i; ay = j;
            } else if (c == 'B') {
                cntB++;
                bx = i; by = j;
            }
            // else: '.', 'X'
        }
    }

    // 3. Check exactly one A and one B
    ensuref(cntA == 1, "There must be exactly one 'A', found %d", cntA);
    ensuref(cntB == 1, "There must be exactly one 'B', found %d", cntB);

    // 4. Check A and B are not on the same cell
    ensuref(!(ax == bx && ay == by), "A and B must not be on the same cell");

    // 5. Check A and B are not on wall
    ensuref(board[ax][ay] == 'A', "A must be on its own cell");
    ensuref(board[bx][by] == 'B', "B must be on its own cell");

    // 6. Check only allowed characters
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            char c = board[i][j];
            ensuref(c == '.' || c == 'X' || c == 'A' || c == 'B',
                "Invalid character '%c' at (%d,%d)", c, i+1, j+1);
        }
    }

    // 7. Check that there is at least one empty cell for A and B to swap
    // (Not strictly required by statement, but if all cells are wall except A/B, swap is impossible anyway.)

    // 8. Check for extra input
    inf.readEof();
}
