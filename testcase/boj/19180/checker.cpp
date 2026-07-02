#include "testlib.h"

#include <array>
#include <string>
using namespace std;

using Board = array<array<char, 6>, 6>;

const Board TARGET = {{
    {{'a', 'b', 'c', 'd', 'e', 'f'}},
    {{'g', 'h', 'i', 'j', 'k', 'l'}},
    {{'m', 'n', 'o', 'p', 'q', 'r'}},
    {{'s', 't', 'u', 'v', 'w', 'x'}},
    {{'y', 'z', '0', '1', '2', '3'}},
    {{'4', '5', '6', '7', '8', '9'}},
}};

void applyMove(Board& board, int index, char direction, int amount) {
    --index;

    if (direction == 'L' || direction == 'R') {
        array<char, 6> row = board[index];
        for (int col = 0; col < 6; ++col) {
            int next = direction == 'R' ? (col + amount) % 6 : (col - amount + 6) % 6;
            board[index][next] = row[col];
        }
        return;
    }

    array<char, 6> column;
    for (int row = 0; row < 6; ++row) {
        column[row] = board[row][index];
    }
    for (int row = 0; row < 6; ++row) {
        int next = direction == 'D' ? (row + amount) % 6 : (row - amount + 6) % 6;
        board[next][index] = column[row];
    }
}

void readAndValidateMoves(InStream& stream, Board board) {
    int moveNumber = 0;
    while (!stream.seekEof()) {
        ++moveNumber;
        int index = stream.readInt(1, 6, format("move[%d].index", moveNumber).c_str());
        string directionToken = stream.readToken("[LRUD]", format("move[%d].direction", moveNumber).c_str());
        int amount = stream.readInt(1, 5, format("move[%d].amount", moveNumber).c_str());

        applyMove(board, index, directionToken[0], amount);
    }

    if (board != TARGET) {
        stream.quitf(_wa, "moves do not transform the board to the target state");
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    Board initial;
    for (int row = 0; row < 6; ++row) {
        string line = inf.readToken("[a-z0-9]{6}", format("input row %d", row + 1).c_str());
        for (int col = 0; col < 6; ++col) {
            initial[row][col] = line[col];
        }
    }

    readAndValidateMoves(ans, initial);
    readAndValidateMoves(ouf, initial);

    quitf(_ok, "valid sequence of moves");
}
