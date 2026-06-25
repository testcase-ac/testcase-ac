#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = 1;
    int m = 1;
    int k = 1;

    if (mode == 0) {
        n = rnd.next(1, 2);
        m = rnd.next(1, 2);
        k = rnd.any(vector<int>{1, 2, 3, 100});
    } else if (mode == 1) {
        n = 1;
        m = rnd.next(2, 12);
        k = rnd.next(1, 100);
    } else if (mode == 2) {
        n = rnd.next(2, 12);
        m = 1;
        k = rnd.next(1, 100);
    } else if (mode == 3) {
        n = rnd.next(2, 10);
        m = rnd.next(2, 10);
        k = rnd.any(vector<int>{1, 2, 3, rnd.next(4, 30), 100});
    } else if (mode == 4) {
        n = rnd.next(3, 12);
        m = rnd.next(3, 12);
        k = rnd.next(1, 60);
    } else if (mode == 5) {
        n = rnd.next(3, 12);
        m = rnd.next(3, 12);
        k = rnd.next(1, 100);
    } else {
        n = rnd.next(2, 8);
        m = rnd.next(2, 8);
        k = rnd.next(1, 100);
    }

    vector<string> board(n, string(m, '.'));

    if (mode == 1 || mode == 2) {
        double blockProb = rnd.next(0.0, 0.45);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                if (rnd.next() < blockProb) {
                    board[r][c] = '#';
                }
            }
        }
    } else if (mode == 4) {
        int clearRow = rnd.next(0, n - 1);
        int clearCol = rnd.next(0, m - 1);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                if (r != clearRow && c != clearCol && rnd.next(0, 2) != 0) {
                    board[r][c] = '#';
                }
            }
        }
    } else if (mode == 5) {
        double blockProb = rnd.next(0.15, 0.55);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                bool onMain = r == c;
                bool onAnti = r + c == m - 1;
                if (!onMain && !onAnti && rnd.next() < blockProb) {
                    board[r][c] = '#';
                }
            }
        }
    } else if (mode == 6) {
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                if ((r + c + rnd.next(0, 1)) % 3 == 0) {
                    board[r][c] = '#';
                }
            }
        }
    }

    vector<pair<int, int>> openCells;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (board[r][c] == '.') {
                openCells.push_back({r, c});
            }
        }
    }

    if (openCells.empty()) {
        int r = rnd.next(0, n - 1);
        int c = rnd.next(0, m - 1);
        board[r][c] = '.';
        openCells.push_back({r, c});
    }

    pair<int, int> start = rnd.any(openCells);
    pair<int, int> finish = rnd.any(openCells);

    if (mode == 3 && n > 1 && m > 1) {
        vector<pair<int, int>> corners{{0, 0}, {0, m - 1}, {n - 1, 0}, {n - 1, m - 1}};
        shuffle(corners.begin(), corners.end());
        start = corners[0];
        finish = corners[1];
        board[start.first][start.second] = '.';
        board[finish.first][finish.second] = '.';
    }

    println(n, m, k);
    for (const string& row : board) {
        println(row);
    }
    println(start.first + 1, start.second + 1);
    println(finish.first + 1, finish.second + 1);

    return 0;
}
