#include "testlib.h"
#include <array>
using namespace std;

const int N = 4;

using Board = array<array<int, N>, N>;

struct Move {
    int type;
    int index;
    int shift;
};

struct Answer {
    int count;
};

Board initialBoard;

void applyMove(Board& board, const Move& move) {
    int idx = move.index - 1;
    int k = move.shift;

    Board next = board;
    if (move.type == 1) {
        for (int c = 0; c < N; ++c) {
            next[idx][(c + k) % N] = board[idx][c];
        }
    } else {
        for (int r = 0; r < N; ++r) {
            next[(r + k) % N][idx] = board[r][idx];
        }
    }
    board = next;
}

bool isSolved(const Board& board) {
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            if (board[r][c] != r * N + c + 1) {
                return false;
            }
        }
    }
    return true;
}

Answer readAnswer(InStream& stream) {
    int count = stream.readInt(0, 100, "move count");
    stream.readEoln();

    Board board = initialBoard;

    for (int step = 0; step < count; ++step) {
        Move move;
        move.type = stream.readInt(1, 2, format("move[%d].type", step + 1).c_str());
        stream.readSpace();
        move.index = stream.readInt(1, N, format("move[%d].index", step + 1).c_str());
        stream.readSpace();
        move.shift = stream.readInt(1, N - 1, format("move[%d].shift", step + 1).c_str());
        stream.readEoln();

        applyMove(board, move);
    }

    stream.readEof();

    if (!isSolved(board)) {
        stream.quitf(_wa, "the claimed %d moves do not solve the board", count);
    }

    return {count};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            initialBoard[r][c] = inf.readInt();
        }
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.count < jury.count) {
        quitf(_fail,
              "participant found a better solution: jury=%d participant=%d",
              jury.count,
              participant.count);
    }
    if (participant.count > jury.count) {
        quitf(_wa,
              "participant used more moves than jury: jury=%d participant=%d",
              jury.count,
              participant.count);
    }

    quitf(_ok, "accepted %d moves", participant.count);
}
