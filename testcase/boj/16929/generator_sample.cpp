#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

void printBoard(const vector<string>& board) {
    println((int)board.size(), (int)board[0].size());
    for (const string& row : board) {
        println(row);
    }
}

vector<string> randomBoard(int n, int m, const string& alphabet) {
    vector<string> board(n, string(m, 'A'));
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            board[r][c] = rnd.any(alphabet);
        }
    }
    return board;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 12);
    int m = rnd.next(2, 12);
    vector<string> board;

    if (mode == 0) {
        board.assign(n, string(m, rnd.any(string("ABC"))));
    } else if (mode == 1) {
        board.assign(n, string(m, 'A'));
        string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        int offset = rnd.next(0, 25);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                board[r][c] = letters[(r + c + offset) % 26];
            }
        }
    } else if (mode == 2) {
        n = rnd.next(3, 12);
        m = rnd.next(3, 12);
        board = randomBoard(n, m, "BCDE");
        int top = rnd.next(0, n - 3);
        int bottom = rnd.next(top + 2, n - 1);
        int left = rnd.next(0, m - 3);
        int right = rnd.next(left + 2, m - 1);
        char color = rnd.any(string("AXYZ"));
        for (int c = left; c <= right; ++c) {
            board[top][c] = color;
            board[bottom][c] = color;
        }
        for (int r = top; r <= bottom; ++r) {
            board[r][left] = color;
            board[r][right] = color;
        }
    } else if (mode == 3) {
        n = rnd.next(2, 8);
        m = rnd.next(2, 16);
        board.assign(n, string(m, 'A'));
        for (int r = 0; r < n; ++r) {
            char base = char('A' + (r % 5));
            for (int c = 0; c < m; ++c) {
                if (rnd.next(0, 6) == 0) {
                    board[r][c] = rnd.any(string("FGHIJ"));
                } else {
                    board[r][c] = base;
                }
            }
        }
    } else if (mode == 4) {
        n = rnd.next(2, 10);
        m = rnd.next(2, 10);
        board = randomBoard(n, m, "ABCD");
        int h = rnd.next(2, min(4, n));
        int w = rnd.next(2, min(4, m));
        int top = rnd.next(0, n - h);
        int left = rnd.next(0, m - w);
        char color = rnd.any(string("MNOP"));
        for (int r = top; r < top + h; ++r) {
            for (int c = left; c < left + w; ++c) {
                board[r][c] = color;
            }
        }
    } else {
        int shape = rnd.next(0, 2);
        if (shape == 0) {
            n = 2;
            m = rnd.next(2, 50);
        } else if (shape == 1) {
            n = rnd.next(2, 50);
            m = 2;
        } else {
            n = rnd.next(40, 50);
            m = rnd.next(40, 50);
        }
        board = randomBoard(n, m, "ABCDEF");
    }

    printBoard(board);
    return 0;
}
