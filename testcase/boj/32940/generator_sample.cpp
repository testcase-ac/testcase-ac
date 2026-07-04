#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode <= 5) {
        n = rnd.next(2, 18);
    } else {
        n = rnd.next(19, 35);
    }

    vector<string> board(n, string(n, '0'));

    if (mode == 0) {
        board[0][0] = char('0' + rnd.next(0, 1));
    } else if (mode == 1) {
        double p = rnd.next(0.05, 0.95);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                board[i][j] = rnd.next() < p ? '1' : '0';
            }
        }
    } else if (mode == 2) {
        int period = rnd.next(2, 5);
        int shift = rnd.next(0, period - 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                board[i][j] = ((i + j + shift) % period == 0) ? '1' : '0';
            }
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            char bit = char('0' + rnd.next(0, 1));
            for (int j = 0; j < n; ++j) {
                board[i][j] = bit;
            }
        }
    } else if (mode == 4) {
        for (int j = 0; j < n; ++j) {
            char bit = char('0' + rnd.next(0, 1));
            for (int i = 0; i < n; ++i) {
                board[i][j] = bit;
            }
        }
    } else if (mode == 5) {
        int rectangles = rnd.next(1, 5);
        for (int r = 0; r < rectangles; ++r) {
            int y1 = rnd.next(0, n - 1);
            int y2 = rnd.next(y1, n - 1);
            int x1 = rnd.next(0, n - 1);
            int x2 = rnd.next(x1, n - 1);
            for (int i = y1; i <= y2; ++i) {
                for (int j = x1; j <= x2; ++j) {
                    board[i][j] = board[i][j] == '0' ? '1' : '0';
                }
            }
        }
    } else if (mode == 6) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                board[i][j] = ((i & 1) ^ (j & 1)) ? '1' : '0';
            }
        }
    } else {
        int border = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                bool onBorder = i == 0 || j == 0 || i == n - 1 || j == n - 1;
                board[i][j] = (onBorder == (border == 1)) ? '1' : '0';
            }
        }
    }

    println(n);
    for (const string& row : board) {
        println(row);
    }

    return 0;
}
