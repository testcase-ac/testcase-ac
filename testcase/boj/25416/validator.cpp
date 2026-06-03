#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    vector<vector<int>> board(5, vector<int>(5));
    int one_count = 0;

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            board[i][j] = inf.readInt(-1, 1, "board_cell");
            if (board[i][j] == 1) {
                ++one_count;
            }
        }
        inf.readEoln();
    }

    ensuref(one_count == 1, "expected exactly one cell with value 1, found %d", one_count);

    int r = inf.readInt(0, 4, "r");
    inf.readSpace();
    int c = inf.readInt(0, 4, "c");
    inf.readEoln();

    ensuref(board[r][c] == 0, "starting cell (%d, %d) must contain 0", r, c);

    inf.readEof();
}
