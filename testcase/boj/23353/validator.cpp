#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(2, 1000, "N");
    inf.readEoln();

    // 2. Read the board
    vector<vector<int>> board(N, vector<int>(N));
    int black_count = 0, white_count = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            board[i][j] = inf.readInt(0, 2, "cell");
            if (j < N - 1) inf.readSpace();
            else inf.readEoln();
            if (board[i][j] == 1) black_count++;
            if (board[i][j] == 2) white_count++;
        }
    }

    // 3. Ensure at least one black and one white stone
    ensuref(black_count >= 1, "There must be at least one black stone (1) on the board, found %d", black_count);
    ensuref(white_count >= 1, "There must be at least one white stone (2) on the board, found %d", white_count);

    inf.readEof();
}
