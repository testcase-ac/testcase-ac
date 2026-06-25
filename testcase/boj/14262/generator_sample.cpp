#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

char randomColor(const string& palette) {
    return palette[rnd.next((int)palette.size())];
}

void setDiagonal(vector<string>& board, const string& colors) {
    int n = (int)board.size();
    int m = (int)board[0].size();
    int len = rnd.next(1, min(n, m));
    int r = rnd.next(0, n - len);
    int c = rnd.next(0, m - len);
    for (int k = 0; k < len; ++k) {
        board[r + k][c + k] = randomColor(colors);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n, m;
    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 20);
    } else if (mode == 1) {
        n = rnd.next(1, 20);
        m = 1;
    } else if (mode == 2) {
        n = rnd.next(2, 8);
        m = rnd.next(2, 8);
    } else if (mode == 3) {
        n = rnd.next(8, 20);
        m = rnd.next(8, 20);
    } else if (mode == 4) {
        n = rnd.next(20, 50);
        m = rnd.next(20, 50);
    } else {
        n = rnd.next(1, 50);
        m = rnd.next(1, 50);
    }

    long long t;
    int tMode = rnd.next(0, 5);
    if (tMode == 0) {
        t = 1;
    } else if (tMode == 1) {
        t = rnd.next(2, 50);
    } else if (tMode == 2) {
        t = rnd.next(51, 10000);
    } else if (tMode == 3) {
        t = rnd.next(100000000LL, 1000000000LL);
    } else {
        t = rnd.next(1LL, 1000000000LL);
    }

    string palette;
    int paletteMode = rnd.next(0, 5);
    if (paletteMode == 0) {
        palette = ".RGB";
    } else if (paletteMode == 1) {
        palette = "...RGB";
    } else if (paletteMode == 2) {
        palette = "RRR.GB";
    } else if (paletteMode == 3) {
        palette = "GGG.RB";
    } else if (paletteMode == 4) {
        palette = "BBB.RG";
    } else {
        palette = "RGB";
    }

    vector<string> board(n, string(m, '.'));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            board[i][j] = randomColor(palette);
        }
    }

    if (rnd.next(0, 1)) {
        int diagonalCount = rnd.next(1, 4);
        for (int i = 0; i < diagonalCount; ++i) {
            setDiagonal(board, "RGB");
        }
    }

    if (rnd.next(0, 3) == 0) {
        int holeCount = rnd.next(1, max(1, n * m / 3));
        for (int i = 0; i < holeCount; ++i) {
            board[rnd.next(0, n - 1)][rnd.next(0, m - 1)] = '.';
        }
    }

    println(n, m, t);
    for (const string& row : board) {
        println(row);
    }

    return 0;
}
