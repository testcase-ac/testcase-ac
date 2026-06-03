#include "testlib.h"

#include <vector>

using namespace std;

void toggle(vector<vector<int>>& board, int x, int y) {
    int n = (int)board.size();
    if (x < 0 || x >= n || y < 0 || y >= n) {
        return;
    }
    board[x][y] ^= 1;
}

void press(vector<vector<int>>& board, int x, int y) {
    toggle(board, x, y);
    toggle(board, x - 1, y);
    toggle(board, x + 1, y);
    toggle(board, x, y - 1);
    toggle(board, x, y + 1);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(100);
    int n;
    if (sizeMode < 25) {
        n = rnd.next(2, 4);
    } else if (sizeMode < 75) {
        n = rnd.next(5, 10);
    } else {
        n = rnd.next(11, 18);
    }

    vector<vector<int>> board(n, vector<int>(n, 0));
    int mode = rnd.next(6);

    if (mode == 0) {
        int p = rnd.next(5, 95);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                board[i][j] = rnd.next(100) < p;
            }
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                board[i][j] = (i + j + rnd.next(2)) % 2;
            }
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            int value = rnd.next(2);
            for (int j = 0; j < n; ++j) {
                board[i][j] = value;
            }
        }
    } else if (mode == 3) {
        for (int j = 0; j < n; ++j) {
            int value = rnd.next(2);
            for (int i = 0; i < n; ++i) {
                board[i][j] = value;
            }
        }
    } else if (mode == 4) {
        int presses = rnd.next(1, n * n);
        for (int k = 0; k < presses; ++k) {
            press(board, rnd.next(n), rnd.next(n));
        }
    } else {
        int borderValue = rnd.next(2);
        int centerValue = rnd.next(2);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                bool border = i == 0 || i == n - 1 || j == 0 || j == n - 1;
                board[i][j] = border ? borderValue : centerValue;
            }
        }
    }

    println(n);
    for (const auto& row : board) {
        println(row);
    }

    return 0;
}
