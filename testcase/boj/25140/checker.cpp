#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

struct Claim {
    int moves;
};

static vector<int> initialBoard;

static int findBlank(const vector<int>& board) {
    for (int i = 0; i < 9; ++i) {
        if (board[i] == 0) {
            return i;
        }
    }
    quitf(_fail, "internal error: board has no blank tile");
}

static bool isSolved(const vector<int>& board) {
    for (int i = 0; i < 8; ++i) {
        if (board[i] != i + 1) {
            return false;
        }
    }
    return board[8] == 0;
}

static Claim readClaim(InStream& stream) {
    int n = stream.readInt(0, 31, "move count");
    vector<int> board = initialBoard;

    for (int i = 0; i < n; ++i) {
        int tile = stream.readInt(1, 8, format("move[%d]", i + 1).c_str());
        int blank = findBlank(board);
        int tilePos = -1;
        for (int pos = 0; pos < 9; ++pos) {
            if (board[pos] == tile) {
                tilePos = pos;
                break;
            }
        }
        if (tilePos == -1) {
            stream.quitf(_wa, "move %d names missing tile %d", i + 1, tile);
        }

        int blankRow = blank / 3;
        int blankCol = blank % 3;
        int tileRow = tilePos / 3;
        int tileCol = tilePos % 3;
        if (abs(blankRow - tileRow) + abs(blankCol - tileCol) != 1) {
            stream.quitf(_wa,
                         "move %d moves tile %d from (%d,%d), not adjacent to blank at (%d,%d)",
                         i + 1,
                         tile,
                         tileRow + 1,
                         tileCol + 1,
                         blankRow + 1,
                         blankCol + 1);
        }
        swap(board[blank], board[tilePos]);
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after move sequence");
    }

    if (!isSolved(board)) {
        stream.quitf(_wa, "claimed sequence of %d moves does not solve the puzzle", n);
    }

    return {n};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    initialBoard.resize(9);
    for (int i = 0; i < 9; ++i) {
        string token = inf.readToken();
        initialBoard[i] = (token == "X") ? 0 : token[0] - '0';
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (participant.moves < jury.moves) {
        quitf(_fail,
              "participant found a shorter valid solution: jury=%d participant=%d",
              jury.moves,
              participant.moves);
    }
    if (participant.moves > jury.moves) {
        quitf(_wa,
              "solution is not minimal: jury=%d participant=%d",
              jury.moves,
              participant.moves);
    }

    quitf(_ok, "valid minimal solution with %d moves", participant.moves);
}
