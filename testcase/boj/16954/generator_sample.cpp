#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> board(8, string(8, '.'));
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        double p = rnd.next(0.0, 0.38);
        for (int r = 0; r < 8; ++r) {
            for (int c = 0; c < 8; ++c) {
                if (rnd.next() < p) board[r][c] = '#';
            }
        }
    } else if (mode == 1) {
        int rows = rnd.next(1, 4);
        for (int i = 0; i < rows; ++i) {
            int r = rnd.next(0, 6);
            int gap = rnd.next(0, 7);
            int secondGap = rnd.next(0, 7);
            for (int c = 0; c < 8; ++c) {
                if (c != gap && c != secondGap) board[r][c] = '#';
            }
        }
    } else if (mode == 2) {
        int cols = rnd.next(1, 3);
        for (int i = 0; i < cols; ++i) {
            int c = rnd.next(0, 7);
            int top = rnd.next(0, 4);
            int bottom = rnd.next(top, 7);
            int gap = rnd.next(top, bottom);
            for (int r = top; r <= bottom; ++r) {
                if (r != gap) board[r][c] = '#';
            }
        }
    } else if (mode == 3) {
        int shift = rnd.next(0, 7);
        for (int r = 0; r < 8; ++r) {
            int c = (r + shift) % 8;
            board[r][c] = '#';
            if (rnd.next(0, 2) == 0) board[r][(c + 1) % 8] = '#';
        }
    } else if (mode == 4) {
        int count = rnd.next(4, 12);
        for (int i = 0; i < count; ++i) {
            int r = rnd.next(4, 7);
            int c = rnd.next(0, 3);
            board[r][c] = '#';
        }
        if (rnd.next(0, 1)) {
            board[6][0] = '#';
            board[6][1] = '#';
        }
    } else {
        int count = rnd.next(6, 22);
        for (int i = 0; i < count; ++i) {
            int r = rnd.wnext(8, -2);
            int c = rnd.next(0, 7);
            board[r][c] = '#';
        }
    }

    board[7][0] = '.';

    for (const string& row : board) {
        println(row);
    }

    return 0;
}
