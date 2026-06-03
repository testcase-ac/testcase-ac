#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int downRight = rnd.next(1, 8);
    int downLeft = rnd.next(1, 8);
    int extraRows = rnd.next(0, 4);
    int extraCols = rnd.next(0, 4);

    int h = downRight + downLeft + extraRows;
    int w = downRight + downLeft + extraCols;
    h = max(h, 2);
    w = max(w, 2);

    int topR = rnd.next(0, h - downRight - downLeft);
    int topC = rnd.next(downLeft, w - downRight);

    vector<string> board(h, string(w, '.'));

    int r = topR;
    int c = topC;
    for (int i = 0; i < downRight; ++i) {
        board[r][c] = '\\';
        ++r;
        ++c;
    }
    for (int i = 0; i < downLeft; ++i) {
        board[r][c - 1] = '/';
        ++r;
        --c;
    }
    for (int i = 0; i < downRight; ++i) {
        board[r - 1][c - 1] = '\\';
        --r;
        --c;
    }
    for (int i = 0; i < downLeft; ++i) {
        board[r - 1][c] = '/';
        --r;
        ++c;
    }

    println(h, w);
    for (const string& row : board) {
        println(row);
    }

    return 0;
}
