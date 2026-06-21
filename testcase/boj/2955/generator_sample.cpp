#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

using Board = vector<string>;

Board solvedBoard() {
    return {
        "534678912",
        "672195348",
        "198342567",
        "859761423",
        "426853791",
        "713924856",
        "961537284",
        "287419635",
        "345286179",
    };
}

void permuteSolvedBoard(Board& board) {
    vector<int> digits(10);
    vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    shuffle(values.begin(), values.end());
    for (int i = 1; i <= 9; ++i) {
        digits[i] = values[i - 1];
    }

    for (string& row : board) {
        for (char& cell : row) {
            cell = char('0' + digits[cell - '0']);
        }
    }
}

void hideCells(Board& board, int blanks) {
    vector<int> cells(81);
    for (int i = 0; i < 81; ++i) {
        cells[i] = i;
    }
    shuffle(cells.begin(), cells.end());
    for (int i = 0; i < blanks; ++i) {
        board[cells[i] / 9][cells[i] % 9] = '.';
    }
}

void addRowDuplicate(Board& board) {
    int row = rnd.next(0, 8);
    int c1 = rnd.next(0, 8);
    int c2 = rnd.next(0, 8);
    while (c1 == c2) {
        c2 = rnd.next(0, 8);
    }
    board[row][c1] = char('1' + rnd.next(0, 8));
    board[row][c2] = board[row][c1];
}

void addColumnDuplicate(Board& board) {
    int col = rnd.next(0, 8);
    int r1 = rnd.next(0, 8);
    int r2 = rnd.next(0, 8);
    while (r1 == r2) {
        r2 = rnd.next(0, 8);
    }
    board[r1][col] = char('1' + rnd.next(0, 8));
    board[r2][col] = board[r1][col];
}

Board sparseCrossHatchingBoard() {
    Board board(9, string(9, '.'));
    int digit = rnd.next(1, 9);
    int targetBox = rnd.next(0, 8);
    int targetRow = 3 * (targetBox / 3) + rnd.next(0, 2);
    int targetCol = 3 * (targetBox % 3) + rnd.next(0, 2);

    vector<int> rows;
    vector<int> cols;
    for (int i = 3 * (targetBox / 3); i < 3 * (targetBox / 3) + 3; ++i) {
        if (i != targetRow) {
            rows.push_back(i);
        }
    }
    for (int j = 3 * (targetBox % 3); j < 3 * (targetBox % 3) + 3; ++j) {
        if (j != targetCol) {
            cols.push_back(j);
        }
    }

    int rowWitnessCol = (3 * (targetBox % 3) + 3 + rnd.next(0, 5)) % 9;
    while (rowWitnessCol / 3 == targetBox % 3) {
        rowWitnessCol = rnd.next(0, 8);
    }
    int colWitnessRow = (3 * (targetBox / 3) + 3 + rnd.next(0, 5)) % 9;
    while (colWitnessRow / 3 == targetBox / 3) {
        colWitnessRow = rnd.next(0, 8);
    }

    board[rows[0]][rowWitnessCol] = char('0' + digit);
    board[rows[1]][(rowWitnessCol + 1) % 9] = char('0' + digit);
    board[colWitnessRow][cols[0]] = char('0' + digit);
    board[(colWitnessRow + 1) % 9][cols[1]] = char('0' + digit);

    int extra = rnd.next(0, 8);
    for (int k = 0; k < extra; ++k) {
        int r = rnd.next(0, 8);
        int c = rnd.next(0, 8);
        if (board[r][c] == '.') {
            board[r][c] = char('1' + rnd.next(0, 8));
        }
    }
    return board;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    Board board = solvedBoard();

    if (mode == 0) {
        permuteSolvedBoard(board);
        hideCells(board, rnd.next(45, 72));
    } else if (mode == 1) {
        permuteSolvedBoard(board);
        hideCells(board, rnd.next(8, 35));
    } else if (mode == 2) {
        board = Board(9, string(9, '.'));
        int givens = rnd.next(0, 18);
        for (int i = 0; i < givens; ++i) {
            board[rnd.next(0, 8)][rnd.next(0, 8)] = char('1' + rnd.next(0, 8));
        }
    } else if (mode == 3) {
        permuteSolvedBoard(board);
        hideCells(board, rnd.next(45, 70));
        addRowDuplicate(board);
    } else {
        if (rnd.next(0, 1) == 0) {
            board = sparseCrossHatchingBoard();
        } else {
            permuteSolvedBoard(board);
            hideCells(board, rnd.next(45, 70));
            addColumnDuplicate(board);
        }
    }

    for (const string& row : board) {
        println(row);
    }
    return 0;
}
