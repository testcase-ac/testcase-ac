#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

vector<string> makeBoard(int n, int m, int mode) {
    vector<string> board(n, string(m, '.'));

    if (mode == 0) {
        double wallProb = rnd.next(0.0, 0.75);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (rnd.next() < wallProb) board[i][j] = '#';
            }
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if ((i + j + rnd.next(0, 1)) % 2 == 0) board[i][j] = '#';
            }
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (i % 2 == 1 && rnd.next(0, 3) != 0) board[i][j] = '#';
                if (i % 2 == 0 && rnd.next(0, 5) == 0) board[i][j] = '#';
            }
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            int l = rnd.next(0, m - 1);
            int r = rnd.next(l, m - 1);
            for (int j = 0; j < m; ++j) {
                board[i][j] = (l <= j && j <= r ? '.' : '#');
            }
        }
    } else {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) board[i][j] = '#';
        }

        int blocks = rnd.next(1, max(1, n * m / 5));
        for (int b = 0; b < blocks; ++b) {
            int h = rnd.next(1, min(2, n));
            int w = rnd.next(1, min(3, m));
            int row = rnd.next(0, n - h);
            int col = rnd.next(0, m - w);
            for (int i = row; i < row + h; ++i) {
                for (int j = col; j < col + w; ++j) board[i][j] = '.';
            }
        }
    }

    if (rnd.next(0, 9) == 0) {
        int row = rnd.next(0, n - 1);
        int col = rnd.next(0, m - 1);
        board[row][col] = '.';
    }

    return board;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    for (int tc = 0; tc < 3; ++tc) {
        int mode = (tc + rnd.next(0, 4)) % 5;
        int n;
        int m;

        if (tc == 0) {
            n = rnd.next(1, 3);
            m = rnd.next(1, 5);
        } else if (tc == 1) {
            n = rnd.next(2, 6);
            m = rnd.next(2, 8);
        } else {
            n = rnd.next(1, 10);
            m = rnd.next(1, 10);
        }

        if (rnd.next(0, 2) == 0) n = min(10, n | 1);

        vector<string> board = makeBoard(n, m, mode);
        println(n, m);
        for (const string& row : board) println(row);
    }

    return 0;
}
