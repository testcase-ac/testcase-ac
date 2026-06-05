#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

vector<vector<int>> reachableCells(const vector<string>& board, int k) {
    int n = board.size();
    int m = board[0].size();
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

    return reachable;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int n = rnd.next(2, mode == 3 ? 24 : 12);
    int m = rnd.next(2, mode == 3 ? 24 : 12);
    int k = 0;
    if (mode == 1) {
        k = rnd.next(1, min(n - 1, m - 1));
    } else if (mode == 2) {
        int side = rnd.next(2, 16);
        n = side;
        m = side;
        k = rnd.next(1, side - 1);
    } else if (mode == 3) {
        k = rnd.next(0, min(n - 1, m - 1));
    }

    vector<string> board(n, string(m, '.'));
    if (mode == 0 || mode == 1) {
        double blockProb = mode == 0 ? rnd.next(0.05, 0.30) : rnd.next(0.00, 0.18);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (rnd.next() < blockProb) {
                    board[i][j] = '#';
                }
            }
        }
    } else if (mode == 2) {
        board.assign(n, string(m, '#'));
        for (int i = 0; i < n; ++i) {
            board[i][i] = '.';
            if (i + 1 < n && rnd.next(2)) {
                board[i][i + 1] = '.';
            }
            if (i + 1 < n && rnd.next(2)) {
                board[i + 1][i] = '.';
            }
        }
    } else {
        double blockProb = rnd.next(0.20, 0.55);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (rnd.next() < blockProb) {
                    board[i][j] = '#';
                }
            }
        }
    }

    board[n - 1][m - 1] = '.';
    vector<vector<int>> reachable = reachableCells(board, k);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (board[i][j] == '.' && !reachable[i][j]) {
                board[i][j] = '#';
            }
        }
    }

    vector<pair<int, int>> openCells;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (board[i][j] == '.' && !(i == n - 1 && j == m - 1)) {
                openCells.push_back({i + 1, j + 1});
            }
        }
    }

    if (openCells.empty()) {
        board[n - 1][m - 2] = '.';
        openCells.push_back({n, m - 1});
    }

    shuffle(openCells.begin(), openCells.end());
    int q = rnd.next(1, min<int>(300, openCells.size()));

    println(n, m, k);
    for (const string& row : board) {
        println(row);
    }
    println(q);
    for (int i = 0; i < q; ++i) {
        println(openCells[i].first, openCells[i].second);
    }

    return 0;
}
