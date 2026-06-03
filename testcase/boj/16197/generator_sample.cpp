#include "testlib.h"
#include <algorithm>
#include <string>
#include <utility>
#include <vector>
using namespace std;

using Cell = pair<int, int>;

void placeCoins(vector<string>& board, Cell a, Cell b) {
    board[a.first][a.second] = 'o';
    board[b.first][b.second] = 'o';
}

void printBoard(const vector<string>& board) {
    println((int)board.size(), (int)board[0].size());
    for (const string& row : board) {
        println(row);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<string> board;

    if (mode == 0) {
        int n = rnd.next(1, 4);
        int m = rnd.next(2, 8);
        board.assign(n, string(m, '.'));
        int r = rnd.next(0, n - 1);
        int c = rnd.next(0, m - 2);
        placeCoins(board, {r, c}, {r, c + 1});
    } else if (mode == 1) {
        int n = rnd.next(2, 8);
        int m = rnd.next(1, 4);
        board.assign(n, string(m, '.'));
        int r = rnd.next(0, n - 2);
        int c = rnd.next(0, m - 1);
        placeCoins(board, {r, c}, {r + 1, c});
    } else if (mode == 2) {
        int n = rnd.next(3, 9);
        int m = rnd.next(3, 9);
        board.assign(n, string(m, '#'));
        int row = rnd.next(1, n - 2);
        for (int c = 0; c < m; ++c) {
            board[row][c] = '.';
        }
        int c1 = rnd.next(0, m - 2);
        int c2 = rnd.next(c1 + 1, m - 1);
        placeCoins(board, {row, c1}, {row, c2});
    } else if (mode == 3) {
        int n = rnd.next(3, 9);
        int m = rnd.next(3, 9);
        board.assign(n, string(m, '#'));
        int col = rnd.next(1, m - 2);
        for (int r = 0; r < n; ++r) {
            board[r][col] = '.';
        }
        int r1 = rnd.next(0, n - 2);
        int r2 = rnd.next(r1 + 1, n - 1);
        placeCoins(board, {r1, col}, {r2, col});
    } else if (mode == 4) {
        int n = rnd.next(3, 8);
        int m = rnd.next(3, 8);
        board.assign(n, string(m, '.'));
        int top = rnd.next(0, n - 3);
        int left = rnd.next(0, m - 3);
        for (int r = top; r < top + 3; ++r) {
            for (int c = left; c < left + 3; ++c) {
                if (r == top || r == top + 2 || c == left || c == left + 2) {
                    board[r][c] = '#';
                }
            }
        }
        vector<Cell> candidates;
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                if (board[r][c] == '.' && Cell{r, c} != Cell{top + 1, left + 1}) {
                    candidates.push_back({r, c});
                }
            }
        }
        placeCoins(board, {top + 1, left + 1}, rnd.any(candidates));
    } else {
        int n = rnd.next(2, 10);
        int m = rnd.next(2, 10);
        board.assign(n, string(m, '.'));
        double wallProb = rnd.next(0.0, 0.35);
        vector<Cell> emptyCells;
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                if (rnd.next() < wallProb) {
                    board[r][c] = '#';
                } else {
                    emptyCells.push_back({r, c});
                }
            }
        }
        while ((int)emptyCells.size() < 2) {
            int r = rnd.next(0, n - 1);
            int c = rnd.next(0, m - 1);
            if (board[r][c] == '#') {
                board[r][c] = '.';
                emptyCells.push_back({r, c});
            }
        }
        shuffle(emptyCells.begin(), emptyCells.end());
        placeCoins(board, emptyCells[0], emptyCells[1]);
    }

    printBoard(board);
    return 0;
}
