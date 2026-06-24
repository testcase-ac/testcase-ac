#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int n;
vector<vector<int>> initialBoard;

void rotateRight(vector<vector<int>>& board, int row, int shift) {
    vector<int> nextRow(n);
    for (int col = 0; col < n; ++col) {
        nextRow[(col + shift) % n] = board[row][col];
    }
    board[row] = nextRow;
}

void rotateDown(vector<vector<int>>& board, int col, int shift) {
    vector<int> nextCol(n);
    for (int row = 0; row < n; ++row) {
        nextCol[(row + shift) % n] = board[row][col];
    }
    for (int row = 0; row < n; ++row) {
        board[row][col] = nextCol[row];
    }
}

void readAndValidateAnswer(InStream& stream) {
    int k = stream.readInt(0, 20000, "K");
    vector<vector<int>> board = initialBoard;

    for (int i = 0; i < k; ++i) {
        string op = stream.readToken("[RD]", format("operation[%d].type", i + 1).c_str());
        int x = stream.readInt(1, n, format("operation[%d].x", i + 1).c_str());
        int shift = stream.readInt(1, n - 1, format("operation[%d].k", i + 1).c_str());

        if (op == "R") {
            rotateRight(board, x - 1, shift);
        } else {
            rotateDown(board, x - 1, shift);
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after operation list");
    }

    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; ++col) {
            if (board[row][col] != row + 1) {
                stream.quitf(_wa,
                             "after all operations, cell (%d, %d) has %d instead of %d",
                             row + 1,
                             col + 1,
                             board[row][col],
                             row + 1);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    initialBoard.assign(n, vector<int>(n));
    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; ++col) {
            initialBoard[row][col] = inf.readInt();
        }
    }

    readAndValidateAnswer(ans);
    readAndValidateAnswer(ouf);

    quitf(_ok, "valid solution");
}
