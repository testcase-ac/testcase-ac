#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

void printGrid(const vector<string>& g) {
    int N = (int)g.size();
    int M = (N ? (int)g[0].size() : 0);
    println(N, M);
    for (const auto &row : g) println(row);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    vector<string> g;

    if (mode == 0) {
        // All dots, small grid
        int N = rnd.next(1, 10);
        int M = rnd.next(1, 10);
        g.assign(N, string(M, '.'));
    } else if (mode == 1) {
        // Single row or single column with some fixed cells
        bool rowCase = rnd.next(0, 1) == 0;
        if (rowCase) {
            int N = 1;
            int M = rnd.next(1, 15);
            g.assign(N, string(M, '.'));
            for (int j = 0; j < M; ++j) {
                if (rnd.next(0, 99) < 40) {
                    g[0][j] = rnd.next(0, 1) == 0 ? '-' : '^';
                }
            }
        } else {
            int N = rnd.next(1, 15);
            int M = 1;
            g.assign(N, string(M, '.'));
            for (int i = 0; i < N; ++i) {
                if (rnd.next(0, 99) < 40) {
                    g[i][0] = rnd.next(0, 1) == 0 ? '-' : '^';
                }
            }
        }
    } else if (mode == 2) {
        // Small random 2D grid
        int N = rnd.next(2, 7);
        int M = rnd.next(2, 7);
        g.assign(N, string(M, '.'));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                int r = rnd.next(0, 99);
                if (r < 50) {
                    g[i][j] = '.';
                } else {
                    g[i][j] = rnd.next(0, 1) == 0 ? '-' : '^';
                }
            }
        }
    } else if (mode == 3) {
        // Explicit single conflict between horizontal and vertical pattern
        // Grid 3x4 with a cell that cannot satisfy both patterns simultaneously
        int N = 3, M = 4;
        g.assign(N, string(M, '.'));
        // Vertical pattern at col 1, rows 0..2: -^-
        g[0][1] = '-';
        // g[1][1] is the conflicting cell: remains '.'
        g[2][1] = '-';
        // Horizontal pattern at row 1, cols 1..3: -^-
        // g[1][1] again conflicting cell
        g[1][2] = '^';
        g[1][3] = '-';
        // Add a bit of random noise in other cells (except the conflict cell)
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (i == 1 && j == 1) continue; // keep as '.'
                if (g[i][j] != '.') continue;   // already fixed
                if (rnd.next(0, 99) < 30) {
                    g[i][j] = rnd.next(0, 1) == 0 ? '-' : '^';
                }
            }
        }
    } else if (mode == 4) {
        // 5x5 grid with one conflict region plus random rest
        int N = 5, M = 5;
        g.assign(N, string(M, '.'));
        // Conflict centered around (1,1) as in mode 3 but embedded in 5x5
        // Vertical at col 1, rows 0..2: -^-
        g[0][1] = '-';
        // g[1][1] is conflict cell: '.'
        g[2][1] = '-';
        // Horizontal at row 1, cols 1..3: -^-
        // g[1][1] conflict
        g[1][2] = '^';
        g[1][3] = '-';
        // Random fill elsewhere with higher density of fixed cells
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (i == 1 && j == 1) continue;
                if (g[i][j] != '.') continue;
                int r = rnd.next(0, 99);
                if (r < 70) {
                    g[i][j] = rnd.next(0, 1) == 0 ? '-' : '^';
                }
            }
        }
    } else if (mode == 5) {
        // Nearly full fixed biggish grid
        int N = rnd.next(8, 15);
        int M = rnd.next(8, 15);
        g.assign(N, string(M, '.'));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (rnd.next(0, 99) < 90) {
                    g[i][j] = rnd.next(0, 1) == 0 ? '-' : '^';
                } else {
                    g[i][j] = '.';
                }
            }
        }
    } else if (mode == 6) {
        // Start all dots but embed several guaranteed -^- patterns
        int N = rnd.next(3, 12);
        int M = rnd.next(3, 12);
        g.assign(N, string(M, '.'));
        int patterns = rnd.next(1, max(N, M));
        for (int p = 0; p < patterns; ++p) {
            bool horiz = rnd.next(0, 1) == 0;
            if (horiz && M >= 3) {
                int i = rnd.next(0, N - 1);
                int j = rnd.next(0, M - 3);
                g[i][j] = '-';
                g[i][j + 1] = '^';
                g[i][j + 2] = '-';
            } else if (!horiz && N >= 3) {
                int i = rnd.next(0, N - 3);
                int j = rnd.next(0, M - 1);
                g[i][j] = '-';
                g[i + 1][j] = '^';
                g[i + 2][j] = '-';
            }
        }
        // Optionally turn some remaining dots into fixed random chars
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (g[i][j] == '.' && rnd.next(0, 99) < 30) {
                    g[i][j] = rnd.next(0, 1) == 0 ? '-' : '^';
                }
            }
        }
    }

    printGrid(g);
    return 0;
}
