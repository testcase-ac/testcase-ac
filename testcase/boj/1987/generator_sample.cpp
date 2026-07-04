#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

static void printBoard(const vector<string>& board) {
    println((int)board.size(), (int)board[0].size());
    for (const string& row : board) {
        println(row);
    }
}

static vector<string> repeatedBoard(int r, int c) {
    char ch = (char)('A' + rnd.next(26));
    vector<string> board(r, string(c, ch));

    int variants = rnd.next(1, min(26, r * c));
    for (int k = 0; k < variants; ++k) {
        int y = rnd.next(r);
        int x = rnd.next(c);
        board[y][x] = (char)('A' + rnd.next(26));
    }
    board[0][0] = (char)('A' + rnd.next(26));
    return board;
}

static vector<string> snakeBoard(int r, int c) {
    vector<string> board(r, string(c, 'A'));
    string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    shuffle(letters.begin(), letters.end());

    int pos = 0;
    for (int i = 0; i < r; ++i) {
        if (i % 2 == 0) {
            for (int j = 0; j < c; ++j) {
                board[i][j] = letters[pos % (int)letters.size()];
                ++pos;
            }
        } else {
            for (int j = c - 1; j >= 0; --j) {
                board[i][j] = letters[pos % (int)letters.size()];
                ++pos;
            }
        }
    }
    return board;
}

static vector<string> randomBoard(int r, int c) {
    int alphabetSize = rnd.next(1, 26);
    vector<string> board(r, string(c, 'A'));
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            board[i][j] = (char)('A' + rnd.next(alphabetSize));
        }
    }
    return board;
}

static vector<string> stripedBoard(int r, int c) {
    vector<string> board(r, string(c, 'A'));
    int alphabetSize = rnd.next(2, 26);
    bool vertical = rnd.next(2) == 0;
    int shift = rnd.next(alphabetSize);

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            int index = vertical ? j : i;
            if (rnd.next(100) < 15) {
                index += rnd.next(alphabetSize);
            }
            board[i][j] = (char)('A' + (index + shift) % alphabetSize);
        }
    }
    return board;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int r, c;
    vector<string> board;

    if (mode == 0) {
        r = rnd.next(1, 3);
        c = rnd.next(1, 6);
        if (rnd.next(2)) {
            swap(r, c);
        }
        board = randomBoard(r, c);
    } else if (mode == 1) {
        r = rnd.next(1, 20);
        c = rnd.next(1, 20);
        board = repeatedBoard(r, c);
    } else if (mode == 2) {
        r = rnd.next(2, 8);
        c = rnd.next(2, 8);
        board = snakeBoard(r, c);
    } else if (mode == 3) {
        r = rnd.next(2, 12);
        c = rnd.next(2, 12);
        board = stripedBoard(r, c);
    } else {
        r = rnd.next(10, 20);
        c = rnd.next(10, 20);
        board = randomBoard(r, c);
    }

    printBoard(board);
    return 0;
}
