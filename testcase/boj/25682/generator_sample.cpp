#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

char chessColor(int i, int j, char topLeft) {
    bool sameParity = ((i + j) % 2 == 0);
    return sameParity ? topLeft : (topLeft == 'B' ? 'W' : 'B');
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 18);
    int m = rnd.next(1, 24);

    if (mode == 1) {
        int side = rnd.next(1, 18);
        n = side;
        m = side;
    } else if (mode == 2) {
        n = rnd.next(1, 5);
        m = rnd.next(1, 24);
    } else if (mode == 3) {
        n = rnd.next(6, 18);
        m = rnd.next(6, 24);
    }

    int k;
    int minSide = min(n, m);
    int kMode = rnd.next(0, 4);
    if (kMode == 0) {
        k = 1;
    } else if (kMode == 1) {
        k = minSide;
    } else {
        k = rnd.next(1, minSide);
    }

    vector<string> board(n, string(m, 'B'));

    if (mode == 0) {
        char c = rnd.next(0, 1) ? 'B' : 'W';
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) board[i][j] = c;
        }
    } else if (mode == 1) {
        char topLeft = rnd.next(0, 1) ? 'B' : 'W';
        int flips = rnd.next(0, max(1, n * m / 5));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) board[i][j] = chessColor(i, j, topLeft);
        }
        for (int t = 0; t < flips; ++t) {
            int r = rnd.next(0, n - 1);
            int c = rnd.next(0, m - 1);
            board[r][c] = (board[r][c] == 'B' ? 'W' : 'B');
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            char c = rnd.next(0, 1) ? 'B' : 'W';
            for (int j = 0; j < m; ++j) board[i][j] = c;
        }
    } else if (mode == 3) {
        char topLeft = rnd.next(0, 1) ? 'B' : 'W';
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) board[i][j] = chessColor(i, j, topLeft);
        }
        int r0 = rnd.next(0, n - k);
        int c0 = rnd.next(0, m - k);
        int blockH = rnd.next(1, k);
        int blockW = rnd.next(1, k);
        char fill = rnd.next(0, 1) ? 'B' : 'W';
        for (int i = r0; i < min(n, r0 + blockH); ++i) {
            for (int j = c0; j < min(m, c0 + blockW); ++j) board[i][j] = fill;
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) board[i][j] = rnd.next(0, 1) ? 'B' : 'W';
        }
    } else {
        bool vertical = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int band = vertical ? j : i;
                board[i][j] = (band % rnd.next(2, 4) == 0) ? 'B' : 'W';
            }
        }
    }

    println(n, m, k);
    for (const string& row : board) println(row);

    return 0;
}
