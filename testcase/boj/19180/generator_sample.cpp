#include "testlib.h"

#include <array>
#include <string>
using namespace std;

using Board = array<string, 6>;

void shiftRow(Board& board, int row, int amount, bool right) {
    string old = board[row];
    for (int col = 0; col < 6; ++col) {
        int next = right ? (col + amount) % 6 : (col - amount + 6) % 6;
        board[row][next] = old[col];
    }
}

void shiftColumn(Board& board, int col, int amount, bool down) {
    array<char, 6> old{};
    for (int row = 0; row < 6; ++row) {
        old[row] = board[row][col];
    }

    for (int row = 0; row < 6; ++row) {
        int next = down ? (row + amount) % 6 : (row - amount + 6) % 6;
        board[next][col] = old[row];
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    Board board = {{
        "abcdef",
        "ghijkl",
        "mnopqr",
        "stuvwx",
        "yz0123",
        "456789",
    }};

    int mode = rnd.next(0, 4);
    int moves = 0;
    if (mode == 0) {
        moves = rnd.next(1, 4);
    } else if (mode == 1) {
        moves = rnd.next(5, 12);
    } else if (mode == 2) {
        moves = rnd.next(13, 30);
    } else if (mode == 3) {
        moves = rnd.next(31, 80);
    } else {
        moves = rnd.next(1, 80);
        if (rnd.next(0, 3) == 0) {
            moves = 0;
        }
    }

    for (int step = 0; step < moves; ++step) {
        int index = rnd.next(0, 5);
        int amount = rnd.next(1, 5);
        bool positiveDirection = rnd.next(0, 1) == 1;

        if (rnd.next(0, 1) == 0) {
            shiftRow(board, index, amount, positiveDirection);
        } else {
            shiftColumn(board, index, amount, positiveDirection);
        }
    }

    for (const string& row : board) {
        println(row);
    }

    return 0;
}
