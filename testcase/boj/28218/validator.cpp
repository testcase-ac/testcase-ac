#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 300, "N");
    inf.readSpace();
    int m = inf.readInt(2, 300, "M");
    inf.readSpace();
    int k = inf.readInt(0, min(n - 1, m - 1), "K");
    inf.readEoln();

    vector<string> board(n);
    for (int i = 0; i < n; ++i) {
        board[i] = inf.readToken("[#.]{1,300}", "row");
        ensuref((int)board[i].size() == m, "row %d has length %d, expected %d",
                i + 1, (int)board[i].size(), m);
        inf.readEoln();
    }

    ensuref(board[n - 1][m - 1] == '.', "(N, M) must not be blocked");

    vector<vector<int>> reachable(n, vector<int>(m, 0));
    for (int i = n - 1; i >= 0; --i) {
        for (int j = m - 1; j >= 0; --j) {
            if (board[i][j] == '#') {
                continue;
            }

            if (i == n - 1 && j == m - 1) {
                reachable[i][j] = 1;
                continue;
            }

            if (i + 1 < n && reachable[i + 1][j]) {
                reachable[i][j] = 1;
            }
            if (j + 1 < m && reachable[i][j + 1]) {
                reachable[i][j] = 1;
            }
            for (int d = 1; d <= k && !reachable[i][j]; ++d) {
                if (i + d < n && j + d < m && reachable[i + d][j + d]) {
                    reachable[i][j] = 1;
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            ensuref(board[i][j] == '#' || reachable[i][j],
                    "open cell (%d, %d) cannot reach (N, M)", i + 1, j + 1);
        }
    }

    int q = inf.readInt(1, 300, "Q");
    inf.readEoln();
    for (int i = 1; i <= q; ++i) {
        int x = inf.readInt(1, n, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, m, "y_i");
        inf.readEoln();

        ensuref(board[x - 1][y - 1] == '.', "query %d points to blocked cell (%d, %d)",
                i, x, y);
        ensuref(!(x == n && y == m), "query %d points to (N, M)", i);
    }

    inf.readEof();
}
