#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

static char coin(bool tails) {
    return tails ? 'T' : 'H';
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 6) {
        n = rnd.next(24, 32);
    } else if (rnd.next(0, 4) == 0) {
        n = rnd.next(1, 4);
    } else {
        n = rnd.next(5, 14);
    }

    vector<string> board(n, string(n, 'H'));

    if (mode == 0) {
        double p = rnd.next(0.05, 0.95);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                board[i][j] = coin(rnd.next() < p);
            }
        }
    } else if (mode == 1) {
        vector<int> row(n), col(n);
        for (int i = 0; i < n; ++i) row[i] = rnd.next(0, 1);
        for (int j = 0; j < n; ++j) col[j] = rnd.next(0, 1);

        int noise = rnd.next(0, max(1, n / 2));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                board[i][j] = coin(row[i] ^ col[j]);
            }
        }
        for (int k = 0; k < noise; ++k) {
            int r = rnd.next(0, n - 1);
            int c = rnd.next(0, n - 1);
            board[r][c] = coin(board[r][c] == 'H');
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                board[i][j] = coin((i + j + rnd.next(0, 1)) % 2);
            }
        }
    } else if (mode == 3) {
        int period = rnd.next(1, min(n, 5));
        bool byRows = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int bucket = byRows ? i / period : j / period;
                board[i][j] = coin(bucket % 2);
            }
        }
    } else if (mode == 4) {
        int cnt = rnd.next(0, max(1, n));
        char fill = coin(rnd.next(0, 1));
        for (int i = 0; i < n; ++i) board[i] = string(n, fill);
        for (int k = 0; k < cnt; ++k) {
            int r = rnd.next(0, n - 1);
            int c = rnd.next(0, n - 1);
            board[r][c] = coin(board[r][c] == 'H');
        }
    } else {
        for (int i = 0; i < n; ++i) {
            int tails = rnd.next(0, n);
            vector<int> cols;
            for (int j = 0; j < n; ++j) cols.push_back(j);
            shuffle(cols.begin(), cols.end());
            for (int k = 0; k < tails; ++k) board[i][cols[k]] = 'T';
        }
    }

    println(n);
    for (const string& row : board) println(row);

    return 0;
}
