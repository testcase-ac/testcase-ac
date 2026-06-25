#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

char flip(char c) {
    return c == 'B' ? 'W' : 'B';
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (rnd.next(0, 9) == 0) {
        n = rnd.next(1, 25);
    } else {
        n = rnd.next(2, 14);
    }

    vector<string> board(n, string(n, 'B'));

    if (mode == 0) {
        double whiteProb = rnd.next(0.15, 0.85);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                board[i][j] = rnd.next() < whiteProb ? 'W' : 'B';
            }
        }
    } else if (mode == 1) {
        bool horizontal = rnd.next(0, 1);
        int stripeWidth = rnd.next(1, 4);
        char start = rnd.next(0, 1) ? 'B' : 'W';
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int band = (horizontal ? i : j) / stripeWidth;
                board[i][j] = band % 2 == 0 ? start : flip(start);
            }
        }
    } else if (mode == 2) {
        int block = rnd.next(2, 5);
        char start = rnd.next(0, 1) ? 'B' : 'W';
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int parity = (i / block + j / block) % 2;
                board[i][j] = parity == 0 ? start : flip(start);
            }
        }
    } else if (mode == 3) {
        char outer = rnd.next(0, 1) ? 'B' : 'W';
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int layer = min(min(i, j), min(n - 1 - i, n - 1 - j));
                board[i][j] = layer % 2 == 0 ? outer : flip(outer);
            }
        }
    } else if (mode == 4) {
        char first = rnd.next(0, 1) ? 'B' : 'W';
        int edits = rnd.next(1, max(1, n * n / 5));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                board[i][j] = (i + j) % 2 == 0 ? first : flip(first);
            }
        }
        for (int k = 0; k < edits; ++k) {
            int r = rnd.next(0, n - 1);
            int c = rnd.next(0, n - 1);
            board[r][c] = flip(board[r][c]);
        }
    } else {
        char fill = rnd.next(0, 1) ? 'B' : 'W';
        char path = flip(fill);
        for (int i = 0; i < n; ++i) {
            fill_n(board[i].begin(), n, fill);
        }
        int r = rnd.next(0, n - 1);
        int c = rnd.next(0, n - 1);
        int steps = rnd.next(n, n * n);
        for (int s = 0; s < steps; ++s) {
            board[r][c] = path;
            int dir = rnd.next(0, 3);
            if (dir == 0 && r > 0) --r;
            if (dir == 1 && r + 1 < n) ++r;
            if (dir == 2 && c > 0) --c;
            if (dir == 3 && c + 1 < n) ++c;
        }
    }

    println(n);
    for (const string& row : board) {
        println(row);
    }

    return 0;
}
