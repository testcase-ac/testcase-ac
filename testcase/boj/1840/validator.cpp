#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N = 9;
    const int STEPS = 81;

    // Sudoku board: 0 means empty, else 1..9
    int board[N][N] = {0};

    for (int step = 0; step < STEPS; ++step) {
        int r = inf.readInt(1, N, "r");
        inf.readSpace();
        int c = inf.readInt(1, N, "c");
        inf.readSpace();
        int v = inf.readInt(1, N, "v");
        if (step + 1 < STEPS) inf.readEoln();
        else inf.readEoln(); // last line must also end with EOLN

        // From problem statement: at each step they "fill a number into an empty cell".
        // Enforce that each (r,c) is used at most once and must be empty when written.
        ensuref(board[r - 1][c - 1] == 0,
                "Cell (%d,%d) is assigned more than once (step %d)",
                r, c, step + 1);

        board[r - 1][c - 1] = v;
    }

    // No extra tokens
    inf.readEof();
}
