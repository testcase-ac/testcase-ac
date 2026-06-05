#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int board[5][5];
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            board[i][j] = inf.readInt(-1, 1, "board");
        }
        inf.readEoln();
    }

    int r = inf.readInt(0, 4, "r");
    inf.readSpace();
    int c = inf.readInt(0, 4, "c");
    inf.readEoln();

    ensuref(board[r][c] == 0, "starting cell (%d, %d) must be empty", r, c);

    inf.readEof();
}
