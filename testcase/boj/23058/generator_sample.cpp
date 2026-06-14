#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 2);
    } else if (mode == 1) {
        n = rnd.next(7, 8);
    } else {
        n = rnd.next(1, 8);
    }

    vector<vector<int>> board(n, vector<int>(n, rnd.next(0, 1)));

    if (mode == 0) {
        int base = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                board[i][j] = base;
            }
        }
        int flips = rnd.next(0, n * n);
        for (int k = 0; k < flips; ++k) {
            int r = rnd.next(0, n - 1);
            int c = rnd.next(0, n - 1);
            board[r][c] ^= 1;
        }
    } else if (mode == 1) {
        int base = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                board[i][j] = base;
            }
        }
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 1)) {
                for (int j = 0; j < n; ++j) {
                    board[i][j] ^= 1;
                }
            }
        }
        for (int j = 0; j < n; ++j) {
            if (rnd.next(0, 1)) {
                for (int i = 0; i < n; ++i) {
                    board[i][j] ^= 1;
                }
            }
        }
        int noise = rnd.next(0, min(5, n * n));
        for (int k = 0; k < noise; ++k) {
            int r = rnd.next(0, n - 1);
            int c = rnd.next(0, n - 1);
            board[r][c] ^= 1;
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                board[i][j] = (i + j + rnd.next(0, 1)) % 2;
            }
        }
    } else if (mode == 3) {
        bool rowStripe = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int index = rowStripe ? i : j;
                board[i][j] = (index % rnd.next(2, 3) == 0);
            }
        }
    } else {
        int density = rnd.next(0, 100);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                board[i][j] = rnd.next(0, 99) < density;
            }
        }
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        println(board[i]);
    }

    return 0;
}
