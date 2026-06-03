#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

static vector<vector<int>> randomBoard(int n, int maxValue, int zeroBias) {
    vector<vector<int>> board(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == n - 1 && j == n - 1) {
                board[i][j] = -1;
            } else if (rnd.next(100) < zeroBias) {
                board[i][j] = 0;
            } else {
                board[i][j] = rnd.next(1, maxValue);
            }
        }
    }
    return board;
}

static void addWinningPath(vector<vector<int>>& board) {
    int n = (int)board.size();
    int r = 0;
    int c = 0;

    while (r != n - 1 || c != n - 1) {
        vector<pair<int, int>> moves;
        for (int step = 1; r + step < n; ++step) {
            moves.push_back({step, 0});
        }
        for (int step = 1; c + step < n; ++step) {
            moves.push_back({0, step});
        }

        auto move = rnd.any(moves);
        board[r][c] = max(move.first, move.second);
        r += move.first;
        c += move.second;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int n;
    vector<vector<int>> board;

    if (mode == 0) {
        n = rnd.next(2, 9);
        board = randomBoard(n, min(100, 2 * n), rnd.next(5, 25));
    } else if (mode == 1) {
        n = rnd.next(2, 10);
        board = randomBoard(n, min(100, 3 * n), rnd.next(0, 20));
        addWinningPath(board);
    } else if (mode == 2) {
        n = rnd.next(2, 8);
        board = randomBoard(n, 100, rnd.next(20, 45));
        if (rnd.next(2) == 0) {
            board[0][0] = 0;
        } else {
            board[0][0] = rnd.next(n, 100);
        }
    } else {
        n = rnd.next(10, 16);
        board = randomBoard(n, 100, rnd.next(0, 15));
        if (rnd.next(3) == 0) {
            addWinningPath(board);
        }
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        println(board[i]);
    }

    return 0;
}
