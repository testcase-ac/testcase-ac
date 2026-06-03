#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int randomTile(int maxExp = 10) {
    if (rnd.next(100) < 30) {
        return 0;
    }
    return 1 << rnd.next(1, maxExp);
}

vector<vector<int>> makeBoard(int n, int mode) {
    vector<vector<int>> board(n, vector<int>(n, 0));

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                board[i][j] = randomTile();
            }
        }
    } else if (mode == 1) {
        int value = 1 << rnd.next(1, 6);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                board[i][j] = (rnd.next(100) < 70 ? value : 0);
            }
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            int value = 1 << rnd.next(1, 6);
            for (int j = 0; j < n; ++j) {
                board[i][j] = (j % 2 == 0 ? value : (rnd.next(2) ? value : 0));
            }
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int exp = 1 + ((i + j + rnd.next(3)) % 10);
                board[i][j] = (rnd.next(100) < 20 ? 0 : (1 << exp));
            }
        }
    } else {
        int filled = rnd.next(1, n * n);
        for (int k = 0; k < filled; ++k) {
            int i = rnd.next(n);
            int j = rnd.next(n);
            board[i][j] = randomTile();
        }
    }

    return board;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> dirs = {"left", "right", "up", "down"};
    int t = rnd.next(1, 20);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int n = (tc < 4 ? tc + 1 : rnd.next(1, 4));
        string dir = (tc < 4 ? dirs[tc] : rnd.any(dirs));
        int mode = rnd.next(5);
        vector<vector<int>> board = makeBoard(n, mode);

        println(n, dir);
        for (int i = 0; i < n; ++i) {
            println(board[i]);
        }
    }

    return 0;
}
