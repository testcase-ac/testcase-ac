#include "testlib.h"

#include <cstdlib>
#include <vector>

using namespace std;

int n;

struct Claim {
    int moves;
};

bool isGoal(const vector<int>& board) {
    for (int i = 1; i <= n; ++i) {
        if (board[i] != -1) {
            return false;
        }
    }
    if (board[n + 1] != 0) {
        return false;
    }
    for (int i = n + 2; i <= 2 * n + 1; ++i) {
        if (board[i] != 1) {
            return false;
        }
    }
    return true;
}

Claim readClaim(InStream& stream) {
    const int cells = 2 * n + 1;
    const int maxMoves = 1000000;
    int moves = stream.readInt(0, maxMoves, "number of moves");

    vector<int> board(cells + 1, 0);
    for (int i = 1; i <= n; ++i) {
        board[i] = 1;
    }
    for (int i = n + 2; i <= cells; ++i) {
        board[i] = -1;
    }

    int empty = n + 1;
    for (int i = 1; i <= moves; ++i) {
        int from = stream.readInt(1, cells, format("move[%d]", i).c_str());
        if (board[from] == 0) {
            stream.quitf(_wa, "move %d starts from the empty field %d", i, from);
        }

        int distance = abs(from - empty);
        if (distance != 1 && distance != 2) {
            stream.quitf(_wa, "move %d from field %d cannot reach empty field %d", i, from, empty);
        }
        if (distance == 2) {
            int middle = (from + empty) / 2;
            if (board[middle] == 0) {
                stream.quitf(_wa, "move %d jumps over empty field %d", i, middle);
            }
            if (board[middle] == board[from]) {
                stream.quitf(_wa, "move %d jumps over a pawn of the same colour at field %d", i, middle);
            }
        }

        board[empty] = board[from];
        board[from] = 0;
        empty = from;
    }

    if (!isGoal(board)) {
        stream.quitf(_wa, "sequence does not reach the goal configuration");
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after the move sequence");
    }

    return {moves};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 100, "n");
    inf.readEoln();
    inf.readEof();

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (participant.moves < jury.moves) {
        quitf(_fail, "participant found a shorter valid sequence: jury=%d participant=%d",
              jury.moves, participant.moves);
    }
    if (participant.moves > jury.moves) {
        quitf(_wa, "sequence is not minimal: jury=%d participant=%d", jury.moves, participant.moves);
    }
    quitf(_ok, "valid shortest sequence with %d moves", participant.moves);
}
