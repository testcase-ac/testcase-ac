#include "testlib.h"

#include <vector>

using namespace std;

int nextColor(int previous = 0) {
    int color = rnd.next(1, 5);
    if (previous != 0 && rnd.next(100) < 80) {
        while (color == previous) {
            color = rnd.next(1, 5);
        }
    }
    return color;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int m = rnd.next(1, 8);
    int n = rnd.next(1, 8);

    if (mode == 0) {
        m = rnd.next(1, 3);
        n = rnd.next(1, 3);
    } else if (mode == 1) {
        if (rnd.next(2) == 0) {
            m = 1;
        } else {
            n = 1;
        }
    } else if (mode >= 4) {
        m = rnd.next(5, 8);
        n = rnd.next(5, 8);
    }

    vector<vector<int>> board(n, vector<int>(m, 1));

    if (mode == 0) {
        int color = rnd.next(1, 5);
        for (int row = 0; row < n; ++row) {
            for (int col = 0; col < m; ++col) {
                board[row][col] = rnd.next(100) < 70 ? color : rnd.next(1, 5);
            }
        }
    } else if (mode == 1) {
        int previous = 0;
        for (int row = 0; row < n; ++row) {
            for (int col = 0; col < m; ++col) {
                board[row][col] = nextColor(previous);
                previous = board[row][col];
            }
        }
    } else if (mode == 2) {
        for (int row = 0; row < n; ++row) {
            int color = rnd.next(1, 5);
            for (int col = 0; col < m; ++col) {
                board[row][col] = rnd.next(100) < 85 ? color : rnd.next(1, 5);
            }
        }
    } else if (mode == 3) {
        for (int col = 0; col < m; ++col) {
            int color = rnd.next(1, 5);
            for (int row = 0; row < n; ++row) {
                board[row][col] = rnd.next(100) < 85 ? color : rnd.next(1, 5);
            }
        }
    } else if (mode == 4) {
        int a = rnd.next(1, 5);
        int b = nextColor(a);
        int c = nextColor(b);
        for (int row = 0; row < n; ++row) {
            for (int col = 0; col < m; ++col) {
                int parity = (row + col + rnd.next(100) / 85) % 2;
                board[row][col] = parity == 0 ? a : b;
                if (rnd.next(100) < 10) {
                    board[row][col] = c;
                }
            }
        }
    } else if (mode == 5) {
        int blockH = rnd.next(1, 3);
        int blockW = rnd.next(1, 3);
        for (int row = 0; row < n; ++row) {
            for (int col = 0; col < m; ++col) {
                board[row][col] = 1 + ((row / blockH + col / blockW + rnd.next(100) / 90) % 5);
            }
        }
    } else {
        for (int col = 0; col < m; ++col) {
            int bottom = rnd.next(1, 5);
            int middle = nextColor(bottom);
            int top = nextColor(middle);
            int split1 = rnd.next(1, n);
            int split2 = rnd.next(split1, n);
            for (int row = 0; row < n; ++row) {
                if (row < n - split2) {
                    board[row][col] = top;
                } else if (row < n - split1) {
                    board[row][col] = middle;
                } else {
                    board[row][col] = bottom;
                }
                if (rnd.next(100) < 8) {
                    board[row][col] = rnd.next(1, 5);
                }
            }
        }
    }

    println(m, n);
    for (const auto& row : board) {
        println(row);
    }

    return 0;
}
