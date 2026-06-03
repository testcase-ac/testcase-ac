#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

vector<string> makeBoard(int r, int c, int mode) {
    vector<string> board(r, string(c, '.'));

    if (mode == 0) {
        double p = rnd.next(0.05, 0.45);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (rnd.next() < p) {
                    board[i][j] = '*';
                }
            }
        }
    } else if (mode == 1) {
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if ((i + j + rnd.next(0, 1)) % 2 == 0) {
                    board[i][j] = '*';
                }
            }
        }
    } else if (mode == 2) {
        int border = rnd.next(0, 1);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                bool onBorder = i == 0 || i == r - 1 || j == 0 || j == c - 1;
                if (onBorder == static_cast<bool>(border) && rnd.next() < 0.75) {
                    board[i][j] = '*';
                }
            }
        }
    } else {
        int blocks = rnd.next(1, max(1, min(r, c)));
        for (int b = 0; b < blocks; ++b) {
            int r1 = rnd.next(0, r - 1);
            int r2 = rnd.next(r1, r - 1);
            int c1 = rnd.next(0, c - 1);
            int c2 = rnd.next(c1, c - 1);
            for (int i = r1; i <= r2; ++i) {
                for (int j = c1; j <= c2; ++j) {
                    if (rnd.next() < 0.6) {
                        board[i][j] = '*';
                    }
                }
            }
        }
    }

    return board;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int cases = rnd.next(1, 6);
    for (int tc = 0; tc < cases; ++tc) {
        int shape = rnd.next(0, 5);
        int r;
        int c;
        if (shape == 0) {
            r = 1;
            c = rnd.next(1, 30);
        } else if (shape == 1) {
            r = rnd.next(1, 30);
            c = 1;
        } else if (shape == 2) {
            r = rnd.next(2, 6);
            c = rnd.next(2, 6);
        } else if (shape == 3) {
            r = rnd.next(7, 15);
            c = rnd.next(2, 10);
        } else if (shape == 4) {
            r = rnd.next(2, 10);
            c = rnd.next(7, 15);
        } else {
            r = rnd.next(16, 30);
            c = rnd.next(16, 30);
        }

        vector<string> board = makeBoard(r, c, rnd.next(0, 3));
        println(r, c);
        for (const string& row : board) {
            println(row);
        }
    }

    println(0, 0);
    return 0;
}
