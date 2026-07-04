#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int m = 1;
    int n = 1;

    if (mode == 0) {
        m = 1;
        n = rnd.next(1, 20);
    } else if (mode == 1) {
        m = rnd.next(1, 20);
        n = 1;
    } else if (mode == 2) {
        m = 2;
        n = 2;
    } else if (mode == 3) {
        m = rnd.next(2, 8);
        n = rnd.next(2, 8);
    } else if (mode == 4) {
        m = rnd.next(3, 12);
        n = rnd.next(3, 12);
    } else if (mode == 5) {
        m = rnd.any(vector<int>{1, 2, 3, 10, 100});
        n = rnd.any(vector<int>{1, 2, 3, 10, 100});
    } else {
        m = rnd.next(1, 12);
        n = rnd.next(1, 12);
    }

    vector<string> board(m, string(n, '.'));
    int pattern = rnd.next(0, 5);

    if (pattern == 0) {
        // Leave an all-white board.
    } else if (pattern == 1) {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                board[i][j] = 'X';
            }
        }
    } else if (pattern == 2) {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if ((i + j + rnd.next(0, 1)) % 2 == 0) {
                    board[i][j] = 'X';
                }
            }
        }
    } else {
        int blackCount = rnd.next(1, m * n);
        vector<int> cells;
        for (int i = 0; i < m * n; ++i) {
            cells.push_back(i);
        }
        shuffle(cells.begin(), cells.end());

        if (pattern == 4 && blackCount % 2 == 1 && blackCount < m * n) {
            ++blackCount;
        }
        if (pattern == 5 && blackCount % 2 == 0) {
            blackCount = blackCount == m * n ? blackCount - 1 : blackCount + 1;
        }

        for (int k = 0; k < blackCount; ++k) {
            int cell = cells[k];
            board[cell / n][cell % n] = 'X';
        }
    }

    println(m, n);
    for (const string& row : board) {
        println(row);
    }

    return 0;
}
