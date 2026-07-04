#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int clampRow(int row) {
    return min(9, max(0, row));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    if (mode == 0) {
        n = rnd.next(1, 6);
    } else if (mode == 1) {
        n = rnd.next(8, 20);
    } else if (mode == 2) {
        n = rnd.next(15, 35);
    } else {
        n = rnd.next(25, 60);
    }

    vector<int> path(n, 9);
    int row = 9;
    int direction = -1;
    int segmentLeft = rnd.next(1, 5);

    for (int column = 1; column < n; ++column) {
        if (mode == 1) {
            direction = -1;
        } else if (mode == 2) {
            direction = (column % 2 == 0 ? -1 : 1);
        } else if (mode == 3) {
            if (segmentLeft == 0) {
                direction *= -1;
                segmentLeft = rnd.next(2, 8);
            }
            --segmentLeft;
        } else if (mode == 4) {
            direction = rnd.any(vector<int>{-1, 1});
        } else if (rnd.next(0, 3) == 0) {
            direction *= -1;
        }

        row = clampRow(row + direction);
        path[column] = row;
    }

    vector<string> board(10, string(n, 'X'));
    for (int column = 0; column < n; ++column) {
        board[path[column]][column] = '.';
    }

    int openPercent = rnd.next(5, 55);
    if (mode == 0) {
        openPercent = rnd.next(55, 100);
    } else if (mode == 1) {
        openPercent = rnd.next(0, 18);
    }

    for (int r = 0; r < 10; ++r) {
        for (int c = 0; c < n; ++c) {
            if (board[r][c] == 'X' && rnd.next(0, 99) < openPercent) {
                board[r][c] = '.';
            }
        }
    }

    board[9][0] = '.';

    println(n);
    for (const string& line : board) {
        println(line);
    }

    return 0;
}
