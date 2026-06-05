#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

vector<string> emptyBoard() {
    return vector<string>(8, string(8, '.'));
}

void placeQueens(vector<string>& board, const vector<int>& cols) {
    for (int row = 0; row < 8; ++row) {
        board[row][cols[row]] = '*';
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<vector<int>> validLayouts = {
        {0, 4, 7, 5, 2, 6, 1, 3},
        {0, 5, 7, 2, 6, 3, 1, 4},
        {1, 3, 5, 7, 2, 0, 6, 4},
        {2, 5, 7, 0, 3, 6, 4, 1},
        {3, 1, 6, 2, 5, 7, 0, 4},
        {4, 6, 1, 5, 2, 0, 3, 7},
    };

    vector<string> board = emptyBoard();
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        placeQueens(board, rnd.any(validLayouts));
    } else if (mode == 1) {
        vector<int> cols = rnd.any(validLayouts);
        int row = rnd.next(0, 7);
        int oldCol = cols[row];
        int newCol = rnd.next(0, 7);
        while (newCol == oldCol) {
            newCol = rnd.next(0, 7);
        }
        cols[row] = newCol;
        placeQueens(board, cols);
    } else if (mode == 2) {
        vector<int> cols;
        for (int i = 0; i < 8; ++i) {
            cols.push_back(i);
        }
        shuffle(cols.begin(), cols.end());
        placeQueens(board, cols);
        int row = rnd.next(1, 7);
        board[row][cols[row]] = '.';
        board[row][cols[0]] = '*';
    } else if (mode == 3) {
        int queens = rnd.next(0, 12);
        vector<int> cells;
        for (int cell = 0; cell < 64; ++cell) {
            cells.push_back(cell);
        }
        shuffle(cells.begin(), cells.end());
        for (int i = 0; i < queens; ++i) {
            int cell = cells[i];
            board[cell / 8][cell % 8] = '*';
        }
    } else if (mode == 4) {
        int row = rnd.next(0, 7);
        int firstCol = rnd.next(0, 6);
        int secondCol = rnd.next(firstCol + 1, 7);
        board[row][firstCol] = '*';
        board[row][secondCol] = '*';

        int extra = rnd.next(0, 6);
        vector<int> cells;
        for (int cell = 0; cell < 64; ++cell) {
            if (cell / 8 != row) {
                cells.push_back(cell);
            }
        }
        shuffle(cells.begin(), cells.end());
        for (int i = 0; i < extra; ++i) {
            int cell = cells[i];
            board[cell / 8][cell % 8] = '*';
        }
    } else {
        int startRow = rnd.next(0, 6);
        int startCol = rnd.next(0, 6);
        board[startRow][startCol] = '*';
        board[startRow + 1][startCol + 1] = '*';

        int extra = rnd.next(0, 6);
        vector<int> cells;
        for (int cell = 0; cell < 64; ++cell) {
            int row = cell / 8;
            int col = cell % 8;
            if (board[row][col] == '.') {
                cells.push_back(cell);
            }
        }
        shuffle(cells.begin(), cells.end());
        for (int i = 0; i < extra; ++i) {
            int cell = cells[i];
            board[cell / 8][cell % 8] = '*';
        }
    }

    for (const string& row : board) {
        println(row);
    }

    return 0;
}
