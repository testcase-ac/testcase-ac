#include "testlib.h"

#include <vector>
using namespace std;

const int N = 7;

bool hasPendingRemoval(const vector<vector<int>>& board) {
    vector<vector<bool>> marked(N, vector<bool>(N, false));

    for (int r = 0; r < N; ++r) {
        int c = 0;
        while (c < N) {
            if (board[r][c] == 0) {
                ++c;
                continue;
            }
            int start = c;
            while (c < N && board[r][c] != 0) {
                ++c;
            }
            int len = c - start;
            for (int j = start; j < c; ++j) {
                if (board[r][j] == len) {
                    marked[r][j] = true;
                }
            }
        }
    }

    for (int c = 0; c < N; ++c) {
        int r = 0;
        while (r < N) {
            if (board[r][c] == 0) {
                ++r;
                continue;
            }
            int start = r;
            while (r < N && board[r][c] != 0) {
                ++r;
            }
            int len = r - start;
            for (int i = start; i < r; ++i) {
                if (board[i][c] == len) {
                    marked[i][c] = true;
                }
            }
        }
    }

    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            if (marked[r][c]) {
                return true;
            }
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    vector<vector<int>> board(N, vector<int>(N));
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            board[r][c] = inf.readInt(0, 7, "cell");
            if (c + 1 < N) {
                inf.readSpace();
            }
        }
        inf.readEoln();
    }

    int next = inf.readInt(1, 7, "next");
    (void)next;
    inf.readEoln();
    inf.readEof();

    for (int c = 0; c < N; ++c) {
        ensuref(board[0][c] == 0, "first row cell (%d, %d) is not empty", 1, c + 1);
    }

    for (int c = 0; c < N; ++c) {
        bool seenEmptyBelow = false;
        for (int r = N - 1; r >= 0; --r) {
            if (board[r][c] == 0) {
                seenEmptyBelow = true;
            } else {
                ensuref(!seenEmptyBelow, "ball at (%d, %d) is floating above an empty cell", r + 1, c + 1);
            }
        }
    }

    ensuref(!hasPendingRemoval(board), "board has a removable group before dropping the next ball");
}
