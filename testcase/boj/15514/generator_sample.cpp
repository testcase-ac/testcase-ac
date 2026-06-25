#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

static char opposite(char c) {
    return c == 'B' ? 'W' : 'B';
}

static void maybeInvert(vector<string>& board) {
    if (rnd.next(2) == 0) return;

    for (string& row : board) {
        for (char& cell : row) cell = opposite(cell);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 4);
    } else if (mode == 1) {
        n = rnd.next(2, 8);
    } else {
        n = rnd.next(3, 15);
    }

    vector<string> board(n, string(n, 'B'));

    if (mode == 0) {
        char c = rnd.next(2) == 0 ? 'B' : 'W';
        for (string& row : board) fill(row.begin(), row.end(), c);
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            char c = rnd.next(2) == 0 ? 'B' : 'W';
            for (int j = 0; j < n; ++j) board[i][j] = c;
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                board[i][j] = ((i + j + rnd.next(2)) % 2 == 0) ? 'B' : 'W';
            }
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                board[i][j] = ((i / rnd.next(1, 3) + j / rnd.next(1, 3)) % 2 == 0) ? 'B' : 'W';
            }
        }
    } else if (mode == 4) {
        char base = rnd.next(2) == 0 ? 'B' : 'W';
        for (string& row : board) fill(row.begin(), row.end(), base);

        int patches = rnd.next(1, min(6, n * n));
        for (int p = 0; p < patches; ++p) {
            int r1 = rnd.next(0, n - 1);
            int c1 = rnd.next(0, n - 1);
            int r2 = rnd.next(r1, min(n - 1, r1 + rnd.next(0, 3)));
            int c2 = rnd.next(c1, min(n - 1, c1 + rnd.next(0, 3)));
            char color = rnd.next(2) == 0 ? base : opposite(base);
            for (int r = r1; r <= r2; ++r) {
                for (int c = c1; c <= c2; ++c) board[r][c] = color;
            }
        }
    } else {
        double blackProb = rnd.next(20, 80) / 100.0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                board[i][j] = rnd.next() < blackProb ? 'B' : 'W';
            }
        }
    }

    maybeInvert(board);

    println(n);
    for (const string& row : board) println(row);

    return 0;
}
