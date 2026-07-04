#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int randomBlock() {
    return 1 << rnd.next(1, 10);
}

void ensureNonEmpty(vector<vector<int>>& board) {
    int n = int(board.size());
    for (const auto& row : board) {
        for (int value : row) {
            if (value != 0) return;
        }
    }
    board[rnd.next(n)][rnd.next(n)] = randomBlock();
}

vector<vector<int>> sparseBoard(int n) {
    vector<vector<int>> board(n, vector<int>(n, 0));
    int filled = rnd.next(1, min(n * n, max(1, n + 2)));
    for (int k = 0; k < filled; ++k) {
        int r = rnd.next(n);
        int c = rnd.next(n);
        board[r][c] = randomBlock();
    }
    ensureNonEmpty(board);
    return board;
}

vector<vector<int>> randomDensityBoard(int n) {
    vector<vector<int>> board(n, vector<int>(n, 0));
    int density = rnd.next(25, 90);
    int maxExp = rnd.next(3, 10);
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            if (rnd.next(100) < density) {
                board[r][c] = 1 << rnd.next(1, maxExp);
            }
        }
    }
    ensureNonEmpty(board);
    return board;
}

vector<vector<int>> mergeLineBoard(int n) {
    vector<vector<int>> board(n, vector<int>(n, 0));
    bool horizontal = rnd.next(2) == 0;
    int lines = rnd.next(1, min(n, 4));
    for (int line = 0; line < lines; ++line) {
        int index = rnd.next(n);
        int exp = rnd.next(1, 6);
        for (int pos = 0; pos < n; ++pos) {
            int value = 1 << exp;
            if (rnd.next(100) < 25) value <<= rnd.next(0, min(4, 10 - exp));
            if (horizontal) {
                board[index][pos] = value;
            } else {
                board[pos][index] = value;
            }
        }
    }
    ensureNonEmpty(board);
    return board;
}

vector<vector<int>> alternatingBoard(int n) {
    vector<vector<int>> board(n, vector<int>(n, 0));
    int shift = rnd.next(2);
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            int exp = 1 + ((r + c + shift) % 5);
            board[r][c] = 1 << exp;
            if (rnd.next(100) < 12) board[r][c] = 0;
        }
    }
    ensureNonEmpty(board);
    return board;
}

vector<vector<int>> cornerStackBoard(int n) {
    vector<vector<int>> board(n, vector<int>(n, 0));
    int height = rnd.next(1, n);
    int width = rnd.next(1, n);
    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            int exp = min(10, 1 + r + c + rnd.next(0, 1));
            board[r][c] = 1 << exp;
        }
    }
    if (rnd.next(2)) {
        reverse(board.begin(), board.end());
    }
    if (rnd.next(2)) {
        for (auto& row : board) reverse(row.begin(), row.end());
    }
    ensureNonEmpty(board);
    return board;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 6);
    } else if (mode == 4) {
        n = rnd.next(8, 20);
    } else {
        n = rnd.next(2, 8);
    }

    vector<vector<int>> board;
    if (mode == 0) {
        board = sparseBoard(n);
    } else if (mode == 1) {
        board = randomDensityBoard(n);
    } else if (mode == 2) {
        board = mergeLineBoard(n);
    } else if (mode == 3) {
        board = alternatingBoard(n);
    } else {
        board = cornerStackBoard(n);
    }

    println(n);
    for (const auto& row : board) {
        println(row);
    }
    return 0;
}
