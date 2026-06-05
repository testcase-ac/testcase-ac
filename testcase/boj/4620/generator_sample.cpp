#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

using int64 = long long;

static const int64 LIMIT = (1LL << 62);

int64 countPaths(const vector<string>& board) {
    int n = (int)board.size();
    vector<vector<int64>> dp(n, vector<int64>(n, 0));
    dp[0][0] = 1;

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            int step = board[r][c] - '0';
            if (step == 0 || dp[r][c] == 0) {
                continue;
            }
            if (r + step < n) {
                dp[r + step][c] = min(LIMIT, dp[r + step][c] + dp[r][c]);
            }
            if (c + step < n) {
                dp[r][c + step] = min(LIMIT, dp[r][c + step] + dp[r][c]);
            }
        }
    }

    return dp[n - 1][n - 1];
}

vector<string> deadHeavyBoard(int n) {
    vector<string> board(n, string(n, '0'));
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            if (r == n - 1 && c == n - 1) {
                continue;
            }
            if (rnd.next(100) < 35) {
                board[r][c] = char('1' + rnd.next(9));
            }
        }
    }
    return board;
}

vector<string> randomBoard(int n) {
    vector<string> board(n, string(n, '0'));
    int zeroChance = rnd.next(10, 45);
    int maxDigit = rnd.next(1, 9);

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            if (r == n - 1 && c == n - 1) {
                continue;
            }
            if (rnd.next(100) >= zeroChance) {
                board[r][c] = char('1' + rnd.next(maxDigit));
            }
        }
    }
    return board;
}

vector<string> forcedPathBoard(int n) {
    vector<string> board(n, string(n, '0'));
    int r = 0;
    int c = 0;

    while (r != n - 1 || c != n - 1) {
        bool goDown = (c == n - 1) || (r + 1 < n && rnd.next(2) == 0);
        int remaining = goDown ? n - 1 - r : n - 1 - c;
        int step = rnd.next(1, min(9, remaining));
        board[r][c] = char('0' + step);
        if (goDown) {
            r += step;
        } else {
            c += step;
        }
    }

    int noise = rnd.next(n, n * n / 2);
    for (int i = 0; i < noise; ++i) {
        int rr = rnd.next(n);
        int cc = rnd.next(n);
        if (rr == n - 1 && cc == n - 1) {
            continue;
        }
        if (board[rr][cc] == '0') {
            board[rr][cc] = char('1' + rnd.next(9));
        }
    }
    return board;
}

vector<string> oneHeavyBoard(int n) {
    vector<string> board(n, string(n, '1'));
    board[n - 1][n - 1] = '0';

    int holes = rnd.next(0, n * n / 3);
    for (int i = 0; i < holes; ++i) {
        int r = rnd.next(n);
        int c = rnd.next(n);
        if (r != 0 || c != 0) {
            board[r][c] = '0';
        }
    }

    int jumps = rnd.next(0, n);
    for (int i = 0; i < jumps; ++i) {
        int r = rnd.next(n);
        int c = rnd.next(n);
        if (r != n - 1 || c != n - 1) {
            board[r][c] = char('2' + rnd.next(8));
        }
    }
    return board;
}

vector<string> makeBoard(int mode, int n) {
    for (int attempt = 0; attempt < 200; ++attempt) {
        vector<string> board;
        if (mode == 0) {
            board = deadHeavyBoard(n);
        } else if (mode == 1) {
            board = randomBoard(n);
        } else if (mode == 2) {
            board = forcedPathBoard(n);
        } else {
            board = oneHeavyBoard(n);
        }

        if (countPaths(board) < LIMIT) {
            return board;
        }
    }

    return deadHeavyBoard(n);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int boards = rnd.next(1, 8);
    for (int tc = 0; tc < boards; ++tc) {
        int mode = rnd.next(4);
        int n;
        if (mode == 3) {
            n = rnd.next(4, 12);
        } else if (rnd.next(100) < 10) {
            n = rnd.next(20, 34);
        } else {
            n = rnd.next(4, 14);
        }

        vector<string> board = makeBoard(mode, n);
        println(n);
        for (const string& row : board) {
            println(row);
        }
    }
    println("-1");

    return 0;
}
