#include "testlib.h"
using namespace std;

int randomPow2(int minExp, int maxExp) {
    // returns 2^e, where e in [minExp, maxExp]
    int e = rnd.next(minExp, maxExp);
    return 1 << e;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int type = rnd.next(0, 6); // choose scenario type 0..6
    int N = 4;
    vector<vector<int>> board;

    if (type == 0) {
        // Tiny boards (N = 1..3), simple patterns
        N = rnd.next(1, 3);
        board.assign(N, vector<int>(N, 0));

        if (N == 1) {
            board[0][0] = randomPow2(1, 10); // 2..1024
        } else {
            int subtype = rnd.next(0, 2);
            if (subtype == 0) {
                // One full row of equal numbers
                int r = rnd.next(0, N - 1);
                int v = randomPow2(1, 5); // up to 32
                for (int j = 0; j < N; ++j) board[r][j] = v;
            } else if (subtype == 1) {
                // Main diagonal equal
                int v = randomPow2(1, 5);
                for (int i = 0; i < N; ++i) board[i][i] = v;
            } else {
                // Few random cells
                int cnt = rnd.next(1, N);
                for (int k = 0; k < cnt; ++k) {
                    int i = rnd.next(0, N - 1);
                    int j = rnd.next(0, N - 1);
                    board[i][j] = randomPow2(1, 5);
                }
            }
        }
    } else if (type == 1) {
        // Standard 4x4 random-ish board
        N = 4;
        board.assign(N, vector<int>(N, 0));
        int p = rnd.next(30, 90); // percentage of non-zero cells
        int nonzero = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (rnd.next(100) < p) {
                    int e;
                    if (rnd.next(0, 9) == 0)
                        e = rnd.next(7, 10); // sometimes big (128..1024)
                    else
                        e = rnd.next(1, 7);  // mostly small (2..128)
                    board[i][j] = 1 << e;
                    ++nonzero;
                }
            }
        }
        if (nonzero == 0) {
            board[rnd.next(0, N - 1)][rnd.next(0, N - 1)] = 2;
        }
    } else if (type == 2) {
        // Dense rows that encourage many merges
        N = rnd.next(3, 6);
        board.assign(N, vector<int>(N, 0));
        for (int i = 0; i < N; ++i) {
            int pos = 0;
            while (pos < N) {
                int pattern = rnd.next(0, 2);
                int v = randomPow2(1, 6); // up to 64
                if (pattern == 0 && pos + 1 < N) {
                    // Contiguous pair: v v
                    board[i][pos] = v;
                    board[i][pos + 1] = v;
                    pos += 2;
                } else if (pattern == 1 && pos + 2 < N) {
                    // Contiguous triple: v v v
                    board[i][pos] = v;
                    board[i][pos + 1] = v;
                    board[i][pos + 2] = v;
                    pos += 3;
                } else {
                    // Single or zero
                    if (rnd.next(0, 1) == 1) board[i][pos] = v;
                    pos += 1;
                }
            }
        }
    } else if (type == 3) {
        // Emphasize "three equal tiles" merge order cases
        N = rnd.next(3, 5);
        board.assign(N, vector<int>(N, 0));
        int v = randomPow2(1, 7); // up to 128

        bool horizontal = rnd.next(0, 1) == 0;
        if (horizontal) {
            int r = rnd.next(0, N - 1);
            int c = rnd.next(0, N - 3);
            for (int k = 0; k < 3; ++k) board[r][c + k] = v;
        } else {
            int c = rnd.next(0, N - 1);
            int r = rnd.next(0, N - 3);
            for (int k = 0; k < 3; ++k) board[r + k][c] = v;
        }

        // Add some extra random small tiles without disturbing non-zeros
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (board[i][j] == 0 && rnd.next(100) < 25) {
                    board[i][j] = randomPow2(1, 5);
                }
            }
        }
    } else if (type == 4) {
        // Boards with some high-valued tiles (near 1024)
        N = rnd.next(3, 5);
        board.assign(N, vector<int>(N, 0));

        int bigs = rnd.next(2, min(4, N * N));
        for (int b = 0; b < bigs; ++b) {
            int i, j;
            do {
                i = rnd.next(0, N - 1);
                j = rnd.next(0, N - 1);
            } while (board[i][j] != 0);
            board[i][j] = randomPow2(7, 10); // 128..1024
        }

        // Fill some remaining cells with small tiles
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (board[i][j] == 0 && rnd.next(100) < 30) {
                    board[i][j] = randomPow2(1, 5); // 2..32
                }
            }
        }
    } else if (type == 5) {
        // Almost empty board with a single full row/column
        N = rnd.next(5, 9);
        board.assign(N, vector<int>(N, 0));

        bool rowLine = rnd.next(0, 1) == 0;
        int v = randomPow2(1, 5); // 2..32

        if (rowLine) {
            int r = rnd.next(0, N - 1);
            for (int j = 0; j < N; ++j) board[r][j] = v;
        } else {
            int c = rnd.next(0, N - 1);
            for (int i = 0; i < N; ++i) board[i][c] = v;
        }

        // Optionally sprinkle a few more tiles
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (board[i][j] == 0 && rnd.next(100) < 10) {
                    board[i][j] = randomPow2(1, 4); // 2..16
                }
            }
        }
    } else if (type == 6) {
        // Medium-large sparse random boards, N up to 9, low density
        N = rnd.next(6, 9);
        board.assign(N, vector<int>(N, 0));
        int p = rnd.next(10, 40); // 10%..40% density
        int nonzero = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (rnd.next(100) < p) {
                    board[i][j] = randomPow2(1, 6); // 2..64
                    ++nonzero;
                }
            }
        }
        if (nonzero == 0) {
            board[rnd.next(0, N - 1)][rnd.next(0, N - 1)] = 2;
        }
    }

    // Safety: ensure at least one non-zero tile
    bool anyNonZero = false;
    for (int i = 0; i < (int)board.size(); ++i)
        for (int j = 0; j < (int)board[i].size(); ++j)
            if (board[i][j] != 0) anyNonZero = true;
    if (!anyNonZero) {
        int i = rnd.next(0, N - 1);
        int j = rnd.next(0, N - 1);
        board[i][j] = 2;
    }

    // Output
    println(N);
    for (int i = 0; i < N; ++i) {
        println(board[i]);
    }

    return 0;
}
