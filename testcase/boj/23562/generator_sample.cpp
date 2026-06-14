#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

void paintShape(vector<string>& board, int top, int left, int k) {
    const int dx[7] = {0, 0, 0, 1, 2, 2, 2};
    const int dy[7] = {0, 1, 2, 0, 0, 1, 2};

    for (int block = 0; block < 7; ++block) {
        for (int i = 0; i < k; ++i) {
            for (int j = 0; j < k; ++j) {
                board[top + dx[block] * k + i][left + dy[block] * k + j] = '#';
            }
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(3, 12);
    int m = rnd.next(3, 12);
    if (mode == 5) {
        n = rnd.next(15, 20);
        m = rnd.next(15, 20);
    } else if (mode == 6) {
        if (rnd.next(0, 1) == 0) {
            n = 3;
            m = rnd.next(3, 20);
        } else {
            n = rnd.next(3, 20);
            m = 3;
        }
    }

    int a = rnd.next(1, 1000);
    int b = rnd.next(1, 1000);
    if (mode == 3) {
        a = rnd.any(vector<int>{1, 2, 999, 1000});
        b = rnd.any(vector<int>{1, 2, 999, 1000});
    }

    vector<string> board(n, string(m, '.'));

    if (mode <= 2 || mode == 5) {
        int maxK = min(n, m) / 3;
        int k = rnd.next(1, maxK);
        int top = rnd.next(0, n - 3 * k);
        int left = rnd.next(0, m - 3 * k);
        paintShape(board, top, left, k);

        if (mode == 1 || mode == 5) {
            int flips = rnd.next(1, max(1, n * m / 5));
            for (int t = 0; t < flips; ++t) {
                int x = rnd.next(0, n - 1);
                int y = rnd.next(0, m - 1);
                board[x][y] = (board[x][y] == '#') ? '.' : '#';
            }
        } else if (mode == 2) {
            int extra = rnd.next(1, max(1, n * m / 4));
            for (int t = 0; t < extra; ++t) {
                board[rnd.next(0, n - 1)][rnd.next(0, m - 1)] = '#';
            }
        }
    } else if (mode == 3) {
        int threshold = rnd.next(10, 90);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (rnd.next(1, 100) <= threshold) board[i][j] = '#';
            }
        }
    } else if (mode == 4) {
        int style = rnd.next(0, 2);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                bool filled = false;
                if (style == 0) filled = ((i + j) % 2 == 0);
                if (style == 1) filled = (i % rnd.next(2, 3) == 0);
                if (style == 2) filled = (j % rnd.next(2, 3) == 0);
                if (filled) board[i][j] = '#';
            }
        }
    } else {
        int marks = rnd.next(0, n * m);
        for (int t = 0; t < marks; ++t) {
            board[rnd.next(0, n - 1)][rnd.next(0, m - 1)] = '#';
        }
    }

    println(n, m);
    println(a, b);
    for (const string& row : board) println(row);

    return 0;
}
