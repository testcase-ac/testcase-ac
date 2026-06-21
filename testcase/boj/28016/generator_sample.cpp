#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(3, mode == 5 ? 30 : 12);
    int m = rnd.next(3, mode == 5 ? 30 : 14);
    vector<vector<int>> board(n, vector<int>(m, 0));

    int start = rnd.next(0, m - 1);
    board[0][start] = 2;

    if (mode == 0) {
        // Mostly empty board: verifies straight drops and small perturbations.
        int nails = rnd.next(0, max(1, (n * (m - 2)) / 8));
        for (int t = 0; t < nails; ++t) {
            int row = rnd.next(0, n - 1);
            int col = rnd.next(1, m - 2);
            if (row != 0 || col != start) {
                board[row][col] = 1;
            }
        }
    } else if (mode == 1) {
        // Random sparse to medium density.
        int percent = rnd.next(15, 45);
        for (int i = 0; i < n; ++i) {
            for (int j = 1; j + 1 < m; ++j) {
                if ((i != 0 || j != start) && rnd.next(1, 100) <= percent) {
                    board[i][j] = 1;
                }
            }
        }
    } else if (mode == 2) {
        // Alternating internal columns create many forced side moves.
        int parity = rnd.next(0, 1);
        for (int i = 1; i + 1 < n; ++i) {
            for (int j = 1; j + 1 < m; ++j) {
                if ((i + j) % 2 == parity && rnd.next(1, 100) <= 70) {
                    board[i][j] = 1;
                }
            }
        }
    } else if (mode == 3) {
        // A horizontal band of nails can block several paths at once.
        int row = rnd.next(1, n - 2);
        for (int j = 1; j + 1 < m; ++j) {
            if (rnd.next(1, 100) <= 80) {
                board[row][j] = 1;
            }
        }
        for (int i = 0; i < n; ++i) {
            int col = rnd.next(1, m - 2);
            if (i != 0 || col != start) {
                board[i][col] = 1;
            }
        }
    } else if (mode == 4) {
        // A diagonal wall stresses left/right tie and border-adjacent behavior.
        int col = rnd.next(1, m - 2);
        int step = rnd.any(vector<int>{-1, 1});
        for (int i = 1; i < n; ++i) {
            board[i][col] = 1;
            if (rnd.next(1, 100) <= 35) {
                int extra = rnd.next(1, m - 2);
                board[i][extra] = 1;
            }
            if (m > 3) {
                col += step;
                if (col == 0 || col == m - 1) {
                    step *= -1;
                    col += 2 * step;
                }
            }
        }
    } else {
        // Larger compact case with mixed density by row.
        for (int i = 0; i < n; ++i) {
            int percent = rnd.next(5, 55);
            for (int j = 1; j + 1 < m; ++j) {
                if ((i != 0 || j != start) && rnd.next(1, 100) <= percent) {
                    board[i][j] = 1;
                }
            }
        }
    }

    board[0][start] = 2;
    for (int i = 0; i < n; ++i) {
        board[i][0] = 0;
        board[i][m - 1] = 0;
    }
    board[0][start] = 2;

    println(n, m);
    for (const auto& row : board) {
        println(row);
    }

    return 0;
}
