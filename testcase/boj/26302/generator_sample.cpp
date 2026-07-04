#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

vector<string> solvedBoard() {
    vector<string> board(9, string(9, '.'));
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            board[r][c] = char('1' + (r * 3 + r / 3 + c) % 9);
        }
    }

    vector<int> digits;
    for (int d = 0; d < 9; ++d) digits.push_back(d);
    shuffle(digits.begin(), digits.end());
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            board[r][c] = char('1' + digits[board[r][c] - '1']);
        }
    }

    for (int band = 0; band < 3; ++band) {
        vector<int> rows = {band * 3, band * 3 + 1, band * 3 + 2};
        shuffle(rows.begin(), rows.end());
        vector<string> old = board;
        for (int i = 0; i < 3; ++i) board[band * 3 + i] = old[rows[i]];
    }

    for (int stack = 0; stack < 3; ++stack) {
        vector<int> cols = {stack * 3, stack * 3 + 1, stack * 3 + 2};
        shuffle(cols.begin(), cols.end());
        vector<string> old = board;
        for (int r = 0; r < 9; ++r) {
            for (int i = 0; i < 3; ++i) board[r][stack * 3 + i] = old[r][cols[i]];
        }
    }

    return board;
}

void eraseCells(vector<string>& board, int cellsToErase) {
    vector<int> cells;
    for (int i = 0; i < 81; ++i) cells.push_back(i);
    shuffle(cells.begin(), cells.end());
    for (int i = 0; i < cellsToErase; ++i) {
        board[cells[i] / 9][cells[i] % 9] = '.';
    }
}

void placeRandomDigits(vector<string>& board, int count) {
    vector<int> cells;
    for (int i = 0; i < 81; ++i) cells.push_back(i);
    shuffle(cells.begin(), cells.end());
    for (int i = 0; i < count; ++i) {
        board[cells[i] / 9][cells[i] % 9] = char('1' + rnd.next(9));
    }
}

void addDuplicate(vector<string>& board) {
    int kind = rnd.next(3);
    char digit = char('1' + rnd.next(9));
    if (kind == 0) {
        int row = rnd.next(9);
        int c1 = rnd.next(9);
        int c2 = rnd.next(9);
        while (c2 == c1) c2 = rnd.next(9);
        board[row][c1] = digit;
        board[row][c2] = digit;
    } else if (kind == 1) {
        int col = rnd.next(9);
        int r1 = rnd.next(9);
        int r2 = rnd.next(9);
        while (r2 == r1) r2 = rnd.next(9);
        board[r1][col] = digit;
        board[r2][col] = digit;
    } else {
        int baseRow = rnd.next(3) * 3;
        int baseCol = rnd.next(3) * 3;
        int p1 = rnd.next(9);
        int p2 = rnd.next(9);
        while (p2 == p1) p2 = rnd.next(9);
        board[baseRow + p1 / 3][baseCol + p1 % 3] = digit;
        board[baseRow + p2 / 3][baseCol + p2 % 3] = digit;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> board(9, string(9, '.'));
    int mode = rnd.next(5);

    if (mode == 0) {
        placeRandomDigits(board, rnd.next(0, 18));
    } else if (mode == 1) {
        board = solvedBoard();
        eraseCells(board, rnd.next(45, 72));
    } else if (mode == 2) {
        board = solvedBoard();
        eraseCells(board, rnd.next(1, 12));
    } else if (mode == 3) {
        board = solvedBoard();
        eraseCells(board, rnd.next(35, 65));
        addDuplicate(board);
    } else {
        int filledRows = rnd.next(1, 4);
        for (int r = 0; r < filledRows; ++r) {
            vector<int> digits;
            for (int d = 0; d < 9; ++d) digits.push_back(d);
            shuffle(digits.begin(), digits.end());
            for (int c = 0; c < 9; ++c) {
                if (rnd.next(100) < 65) board[r][c] = char('1' + digits[c]);
            }
        }
        placeRandomDigits(board, rnd.next(0, 10));
    }

    for (const string& row : board) println(row);
    return 0;
}
