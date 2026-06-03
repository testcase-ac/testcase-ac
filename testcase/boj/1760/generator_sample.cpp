#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 12);
    int m = rnd.next(1, 12);

    if (mode == 1) {
        n = rnd.next(1, 4);
        m = rnd.next(8, 18);
    } else if (mode == 2) {
        n = rnd.next(8, 18);
        m = rnd.next(1, 4);
    } else if (mode == 5) {
        n = rnd.next(12, 25);
        m = rnd.next(12, 25);
    }

    vector<vector<int>> board(n, vector<int>(m, 0));

    if (mode == 0) {
        int pitWeight = rnd.next(1, 5);
        int wallWeight = rnd.next(1, 5);
        int emptyWeight = rnd.next(4, 12);
        int total = pitWeight + wallWeight + emptyWeight;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int x = rnd.next(1, total);
                if (x <= emptyWeight) {
                    board[i][j] = 0;
                } else if (x <= emptyWeight + pitWeight) {
                    board[i][j] = 1;
                } else {
                    board[i][j] = 2;
                }
            }
        }
    } else if (mode == 1 || mode == 2) {
        int wallPeriod = rnd.next(2, 5);
        int pitPeriod = rnd.next(2, 6);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if ((mode == 1 && j % wallPeriod == wallPeriod - 1) ||
                    (mode == 2 && i % wallPeriod == wallPeriod - 1)) {
                    board[i][j] = 2;
                } else if ((i + j + rnd.next(0, 1)) % pitPeriod == 0) {
                    board[i][j] = 1;
                }
            }
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if ((i + j) % 2 == 0) {
                    board[i][j] = rnd.next(0, 3) == 0 ? 1 : 0;
                } else {
                    board[i][j] = rnd.next(0, 4) == 0 ? 2 : 1;
                }
            }
        }
    } else if (mode == 4) {
        int blockH = rnd.next(2, 4);
        int blockW = rnd.next(2, 4);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (i % blockH == blockH - 1 || j % blockW == blockW - 1) {
                    board[i][j] = 2;
                } else if (rnd.next(0, 4) == 0) {
                    board[i][j] = 1;
                }
            }
        }
    } else {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int x = rnd.next(0, 99);
                if (x < 58) {
                    board[i][j] = 0;
                } else if (x < 82) {
                    board[i][j] = 1;
                } else {
                    board[i][j] = 2;
                }
            }
        }
    }

    board[rnd.next(n)][rnd.next(m)] = 0;

    println(n, m);
    for (int i = 0; i < n; ++i) {
        println(board[i]);
    }

    return 0;
}
