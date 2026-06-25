#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

static vector<string> makeBoard(int r, int c, char fill) {
    return vector<string>(r, string(c, fill));
}

static void scatter(vector<string>& board, int count, char ch) {
    int r = (int)board.size();
    int c = (int)board[0].size();
    vector<int> cells;
    for (int i = 0; i < r * c; ++i) cells.push_back(i);
    shuffle(cells.begin(), cells.end());
    count = min(count, r * c);
    for (int i = 0; i < count; ++i) {
        board[cells[i] / c][cells[i] % c] = ch;
    }
}

static void printBoard(const vector<string>& board) {
    println((int)board.size(), (int)board[0].size());
    for (const string& row : board) println(row);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int r = rnd.next(1, 12);
    int c = rnd.next(1, 12);
    vector<string> board;

    if (mode == 0) {
        r = rnd.next(1, 2);
        c = rnd.next(1, 18);
        board = makeBoard(r, c, '.');
        scatter(board, rnd.next(0, max(1, c / 2)), '#');
    } else if (mode == 1) {
        r = rnd.next(1, 18);
        c = rnd.next(1, 2);
        board = makeBoard(r, c, '.');
        scatter(board, rnd.next(0, max(1, r / 2)), '#');
    } else if (mode == 2) {
        r = rnd.next(1, 8);
        c = rnd.next(1, 8);
        board = makeBoard(r, c, rnd.next(0, 1) ? '#' : '.');
    } else if (mode == 3) {
        r = rnd.next(3, 12);
        c = rnd.next(3, 12);
        board = makeBoard(r, c, '.');
        int borderDots = 0;
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                bool corner = (i == 0 || i == r - 1) && (j == 0 || j == c - 1);
                bool border = i == 0 || i == r - 1 || j == 0 || j == c - 1;
                if (border && !corner && rnd.next(0, 99) < 55) {
                    board[i][j] = '#';
                } else if (!border && rnd.next(0, 99) < 25) {
                    board[i][j] = '#';
                } else if (border) {
                    ++borderDots;
                }
            }
        }
        if (borderDots == 2 * r + 2 * c - 8) {
            if (rnd.next(0, 1)) board[0][rnd.next(1, c - 2)] = '#';
            else board[rnd.next(1, r - 2)][0] = '#';
        }
    } else if (mode == 4) {
        r = rnd.next(3, 12);
        c = rnd.next(3, 12);
        board = makeBoard(r, c, '.');
        for (int i = 1; i + 1 < r; ++i) {
            for (int j = 1; j + 1 < c; ++j) {
                if (rnd.next(0, 99) < 65) board[i][j] = '#';
            }
        }
    } else if (mode == 5) {
        r = rnd.next(3, 14);
        c = rnd.next(3, 14);
        board = makeBoard(r, c, '.');
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if ((i + j + rnd.next(0, 1)) % 3 == 0) board[i][j] = '#';
            }
        }
    } else if (mode == 6) {
        r = rnd.next(8, 20);
        c = rnd.next(8, 20);
        board = makeBoard(r, c, '.');
        int patches = rnd.next(2, 6);
        for (int p = 0; p < patches; ++p) {
            int r1 = rnd.next(0, r - 1);
            int r2 = rnd.next(r1, min(r - 1, r1 + rnd.next(0, 3)));
            int c1 = rnd.next(0, c - 1);
            int c2 = rnd.next(c1, min(c - 1, c1 + rnd.next(0, 3)));
            for (int i = r1; i <= r2; ++i) {
                for (int j = c1; j <= c2; ++j) board[i][j] = '#';
            }
        }
    } else {
        r = rnd.next(3, 12);
        c = rnd.next(3, 12);
        board = makeBoard(r, c, '.');
        if (rnd.next(0, 1)) {
            int row = rnd.next(1, r - 2);
            for (int j = 0; j < c; ++j) board[row][j] = '#';
        } else {
            int col = rnd.next(1, c - 2);
            for (int i = 0; i < r; ++i) board[i][col] = '#';
        }
        scatter(board, rnd.next(0, r + c), '#');
    }

    printBoard(board);
    return 0;
}
