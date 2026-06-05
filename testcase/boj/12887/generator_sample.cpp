#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int m;
    if (rnd.next(0, 9) == 0) {
        m = rnd.next(30, 50);
    } else {
        m = rnd.next(1, 18);
    }

    vector<string> board(2, string(m, '#'));

    if (mode == 0) {
        int row = rnd.next(0, 1);
        board[row] = string(m, '.');
        for (int c = 0; c < m; ++c) {
            if (rnd.next(0, 5) == 0) {
                board[1 - row][c] = '.';
            }
        }
    } else {
        int row = rnd.next(0, 1);
        for (int c = 0; c < m; ++c) {
            board[row][c] = '.';

            int switchChance;
            if (mode == 1) {
                switchChance = 2;
            } else if (mode == 2) {
                switchChance = 5;
            } else if (mode == 3) {
                switchChance = 3;
            } else {
                switchChance = 8;
            }

            if (c + 1 < m && rnd.next(0, switchChance - 1) == 0) {
                board[1 - row][c] = '.';
                row = 1 - row;
                board[row][c] = '.';
            }
        }

        int addChance;
        if (mode == 1) {
            addChance = 5;
        } else if (mode == 2) {
            addChance = 2;
        } else if (mode == 3) {
            addChance = 3;
        } else {
            addChance = 12;
        }

        for (int r = 0; r < 2; ++r) {
            for (int c = 0; c < m; ++c) {
                if (rnd.next(0, addChance - 1) == 0) {
                    board[r][c] = '.';
                }
            }
        }
    }

    println(m);
    println(board[0]);
    println(board[1]);

    return 0;
}
