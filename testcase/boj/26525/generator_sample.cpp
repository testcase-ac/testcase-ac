#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int countZeros(const vector<string>& board) {
    int zeros = 0;
    for (const string& row : board) {
        for (char cell : row) {
            zeros += cell == '0';
        }
    }
    return zeros;
}

void setCell(vector<string>& board, int r, int c, char value) {
    if (0 <= r && r < (int)board.size() && 0 <= c && c < (int)board.size()) {
        board[r][c] = value;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (rnd.next(0, 9) == 0) {
        n = rnd.next(15, 25);
    } else {
        n = rnd.next(2, 12);
    }

    vector<string> board(n, string(n, '0'));

    if (mode == 1) {
        double oneProbability = rnd.next(0.15, 0.85);
        for (string& row : board) {
            for (char& cell : row) {
                cell = rnd.next() < oneProbability ? '1' : '0';
            }
        }
    } else if (mode == 2) {
        int fullRows = rnd.next(0, n);
        int fullCols = rnd.next(0, n);
        vector<int> order(n);
        for (int i = 0; i < n; ++i) order[i] = i;

        shuffle(order.begin(), order.end());
        for (int i = 0; i < fullRows; ++i) {
            fill(board[order[i]].begin(), board[order[i]].end(), '1');
        }

        shuffle(order.begin(), order.end());
        for (int i = 0; i < fullCols; ++i) {
            for (int r = 0; r < n; ++r) board[r][order[i]] = '1';
        }
    } else if (mode == 3) {
        bool mainDiagonal = rnd.next(0, 1);
        bool antiDiagonal = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) {
            if (mainDiagonal) setCell(board, i, i, '1');
            if (antiDiagonal) setCell(board, i, n - 1 - i, '1');
        }

        int extraOnes = rnd.next(0, n);
        for (int i = 0; i < extraOnes; ++i) {
            setCell(board, rnd.next(0, n - 1), rnd.next(0, n - 1), '1');
        }
    } else if (mode == 4) {
        for (string& row : board) fill(row.begin(), row.end(), '1');

        vector<pair<int, int>> cells;
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) cells.push_back({r, c});
        }
        shuffle(cells.begin(), cells.end());

        int zeros = rnd.next(1, min(n * n, max(2, n + 3)));
        for (int i = 0; i < zeros; ++i) {
            board[cells[i].first][cells[i].second] = '0';
        }
    } else if (mode == 5) {
        int missingPerLine = rnd.next(1, min(n, 3));
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                board[r][c] = '1';
            }
            vector<int> cols(n);
            for (int c = 0; c < n; ++c) cols[c] = c;
            shuffle(cols.begin(), cols.end());
            for (int i = 0; i < missingPerLine; ++i) board[r][cols[i]] = '0';
        }
    }

    int emptyCells = countZeros(board);
    if (emptyCells == 0) {
        board[rnd.next(0, n - 1)][rnd.next(0, n - 1)] = '0';
        emptyCells = 1;
    }

    int kMode = rnd.next(0, 4);
    int k = 0;
    if (kMode == 0) {
        k = 0;
    } else if (kMode == 1) {
        k = emptyCells;
    } else if (kMode == 2) {
        k = rnd.next(0, min(emptyCells, n));
    } else {
        k = rnd.next(0, emptyCells);
    }

    println(n, k);
    for (const string& row : board) println(row);

    return 0;
}
