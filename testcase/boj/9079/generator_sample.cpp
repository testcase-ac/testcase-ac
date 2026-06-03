#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

using Board = vector<string>;

void flipRow(Board& board, int row) {
    for (int col = 0; col < 3; ++col) {
        board[row][col] = board[row][col] == 'H' ? 'T' : 'H';
    }
}

void flipCol(Board& board, int col) {
    for (int row = 0; row < 3; ++row) {
        board[row][col] = board[row][col] == 'H' ? 'T' : 'H';
    }
}

void flipDiag(Board& board, int diag) {
    for (int i = 0; i < 3; ++i) {
        int col = diag == 0 ? i : 2 - i;
        board[i][col] = board[i][col] == 'H' ? 'T' : 'H';
    }
}

Board randomBoard() {
    Board board(3, string(3, 'H'));
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            board[row][col] = rnd.next(2) == 0 ? 'H' : 'T';
        }
    }
    return board;
}

Board reachableBoard() {
    Board board(3, string(3, rnd.next(2) == 0 ? 'H' : 'T'));
    vector<int> ops;
    for (int op = 0; op < 8; ++op) ops.push_back(op);
    shuffle(ops.begin(), ops.end());

    int count = rnd.next(0, 8);
    for (int i = 0; i < count; ++i) {
        int op = ops[i];
        if (op < 3) {
            flipRow(board, op);
        } else if (op < 6) {
            flipCol(board, op - 3);
        } else {
            flipDiag(board, op - 6);
        }
    }
    return board;
}

Board biasedBoard() {
    Board board(3, string(3, rnd.next(2) == 0 ? 'H' : 'T'));
    int changes = rnd.next(1, 4);
    vector<int> cells;
    for (int i = 0; i < 9; ++i) cells.push_back(i);
    shuffle(cells.begin(), cells.end());

    for (int i = 0; i < changes; ++i) {
        int cell = cells[i];
        int row = cell / 3;
        int col = cell % 3;
        board[row][col] = board[row][col] == 'H' ? 'T' : 'H';
    }
    return board;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 10);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(100);
        Board board;
        if (mode < 40) {
            board = randomBoard();
        } else if (mode < 75) {
            board = reachableBoard();
        } else {
            board = biasedBoard();
        }

        for (int row = 0; row < 3; ++row) {
            println(string(1, board[row][0]), string(1, board[row][1]), string(1, board[row][2]));
        }
    }

    return 0;
}
