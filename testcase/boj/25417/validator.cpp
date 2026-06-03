#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    vector<vector<int>> board(5, vector<int>(5));
    int oneCount = 0;

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            board[i][j] = inf.readInt(-1, 7, "board_i_j");
            ensuref(board[i][j] == -1 || board[i][j] == 0 || board[i][j] == 1 ||
                        board[i][j] == 7,
                    "board[%d][%d] has invalid value %d", i, j, board[i][j]);
            if (board[i][j] == 1) {
                ++oneCount;
            }

            if (j + 1 < 5) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    ensuref(oneCount == 1, "board must contain exactly one cell with value 1");

    int r = inf.readInt(0, 4, "r");
    inf.readSpace();
    int c = inf.readInt(0, 4, "c");
    inf.readEoln();
    ensuref(board[r][c] == 0, "start cell board[%d][%d] must contain 0", r, c);

    inf.readEof();
}
