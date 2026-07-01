#include "testlib.h"
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

using Pos = pair<int, int>;

int dr8[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dc8[] = {-1, 0, 1, -1, 1, -1, 0, 1};

bool inside(int n, int r, int c) {
    return 0 <= r && r < n && 0 <= c && c < n;
}

Pos randomEmpty(const vector<vector<char>>& board) {
    int n = board.size();
    while (true) {
        int r = rnd.next(n);
        int c = rnd.next(n);
        if (board[r][c] == '0') {
            return {r, c};
        }
    }
}

void putRandom(vector<vector<char>>& board, char piece) {
    auto [r, c] = randomEmpty(board);
    board[r][c] = piece;
}

void addRandomPieces(vector<vector<char>>& board, int count, bool queenAllowed) {
    string pieces = queenAllowed ? "QRBN" : "RBN";
    bool queenPlaced = false;
    for (int i = 0; i < count; ++i) {
        char piece = rnd.any(pieces);
        if (piece == 'Q') {
            if (queenPlaced) {
                piece = rnd.any(string("RBN"));
            }
            queenPlaced = true;
        }
        putRandom(board, piece);
    }
}

void printBoard(const vector<vector<char>>& board) {
    cout << board.size() << '\n';
    for (const auto& row : board) {
        for (int j = 0; j < (int)row.size(); ++j) {
            if (j) {
                cout << ' ';
            }
            cout << row[j];
        }
        cout << '\n';
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(2, mode == 4 ? 14 : 10);
    vector<vector<char>> board(n, vector<char>(n, '0'));

    if (mode == 0) {
        Pos p = {rnd.next(n), rnd.next(n)};
        vector<Pos> near;
        for (int d = 0; d < 8; ++d) {
            int nr = p.first + dr8[d];
            int nc = p.second + dc8[d];
            if (inside(n, nr, nc)) {
                near.push_back({nr, nc});
            }
        }
        Pos k = rnd.any(near);
        board[p.first][p.second] = 'P';
        board[k.first][k.second] = 'K';
        addRandomPieces(board, rnd.next(0, min(6, n * n - 2)), true);
    } else if (mode == 1) {
        putRandom(board, 'P');
        putRandom(board, 'K');
        addRandomPieces(board, rnd.next(0, min(10, n * n - 2)), true);
    } else if (mode == 2) {
        int row = rnd.next(n);
        int pCol = rnd.next(n);
        int kCol = rnd.next(n);
        while (kCol == pCol) {
            kCol = rnd.next(n);
        }
        board[row][pCol] = 'P';
        board[row][kCol] = 'K';

        int lo = min(pCol, kCol) + 1;
        int hi = max(pCol, kCol) - 1;
        if (lo <= hi) {
            board[row][rnd.next(lo, hi)] = rnd.any(string("RBN"));
        }
        addRandomPieces(board, rnd.next(1, min(8, n * n - 3)), true);
    } else if (mode == 3) {
        putRandom(board, 'P');
        putRandom(board, 'K');
        int extra = rnd.next(1, min(12, n * n - 2));
        for (int i = 0; i < extra; ++i) {
            putRandom(board, rnd.next(100) < 65 ? 'N' : rnd.any(string("RBN")));
        }
    } else {
        putRandom(board, 'P');
        putRandom(board, 'K');
        int available = n * n - 2;
        int count = rnd.next(max(1, available / 5), max(1, available / 2));
        bool queenPlaced = false;
        for (int i = 0; i < count; ++i) {
            char piece = rnd.any(string("RRBBNNQ"));
            if (piece == 'Q') {
                if (queenPlaced) {
                    piece = rnd.any(string("RBN"));
                }
                queenPlaced = true;
            }
            putRandom(board, piece);
        }
    }

    printBoard(board);
    return 0;
}
