#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 2;
    } else if (mode == 5) {
        n = rnd.next(20, 50);
    } else {
        n = rnd.next(2, 10);
    }

    vector<vector<int>> board(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            board[i][j] = i + 1;
        }
    }

    if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            int shift = rnd.next(0, n - 1);
            vector<int> row(n);
            for (int j = 0; j < n; ++j) {
                row[(j + shift) % n] = board[i][j];
            }
            board[i] = row;
        }
    } else if (mode == 2) {
        for (int j = 0; j < n; ++j) {
            vector<int> column(n);
            for (int i = 0; i < n; ++i) {
                column[i] = i + 1;
            }
            shuffle(column.begin(), column.end());
            for (int i = 0; i < n; ++i) {
                board[i][j] = column[i];
            }
        }
    } else if (mode == 3) {
        vector<int> values;
        for (int value = 1; value <= n; ++value) {
            for (int count = 0; count < n; ++count) {
                values.push_back(value);
            }
        }
        shuffle(values.begin(), values.end());
        int at = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                board[i][j] = values[at++];
            }
        }
    } else if (mode >= 4) {
        int operations = mode == 4 ? rnd.next(n, 4 * n) : rnd.next(4 * n, 10 * n);
        for (int op = 0; op < operations; ++op) {
            int index = rnd.next(0, n - 1);
            int shift = rnd.next(1, n - 1);
            if (rnd.next(0, 1) == 0) {
                vector<int> row(n);
                for (int j = 0; j < n; ++j) {
                    row[(j + shift) % n] = board[index][j];
                }
                board[index] = row;
            } else {
                vector<int> column(n);
                for (int i = 0; i < n; ++i) {
                    column[(i + shift) % n] = board[i][index];
                }
                for (int i = 0; i < n; ++i) {
                    board[i][index] = column[i];
                }
            }
        }
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        println(board[i]);
    }

    return 0;
}
