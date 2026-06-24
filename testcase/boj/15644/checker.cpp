#include "testlib.h"
#include <string>
#include <utility>
#include <vector>
using namespace std;

struct State {
    int rr, rc, br, bc;
};

struct Answer {
    int moves;
};

int N, M;
vector<string> board;
int holeR, holeC;
State startState;

const int dr[4] = {0, 0, -1, 1};
const int dc[4] = {-1, 1, 0, 0};

bool isParticipant(InStream& stream) {
    return &stream == &ouf;
}

template <typename... Args>
void quitStream(InStream& stream, TResult verdict, const char* fmt, Args... args) {
    if (!isParticipant(stream) && verdict != _fail) {
        verdict = _fail;
    }
    stream.quitf(verdict, "%s", format(fmt, args...).c_str());
}

void quitStream(InStream& stream, TResult verdict, const char* message) {
    if (!isParticipant(stream) && verdict != _fail) {
        verdict = _fail;
    }
    stream.quitf(verdict, "%s", message);
}

int directionIndex(char ch) {
    if (ch == 'L') return 0;
    if (ch == 'R') return 1;
    if (ch == 'U') return 2;
    if (ch == 'D') return 3;
    return -1;
}

pair<int, int> roll(int r, int c, int dir, bool& inHole, int otherR, int otherC) {
    inHole = false;
    while (true) {
        int nr = r + dr[dir];
        int nc = c + dc[dir];
        if (board[nr][nc] == '#') break;
        if (nr == otherR && nc == otherC) break;
        if (nr == holeR && nc == holeC) {
            inHole = true;
            return {nr, nc};
        }
        r = nr;
        c = nc;
    }
    return {r, c};
}

bool applyMove(State& state, int dir, bool& redHole, bool& blueHole) {
    bool firstIsRed;
    if (dir == 0) {
        firstIsRed = state.rc < state.bc;
    } else if (dir == 1) {
        firstIsRed = state.rc > state.bc;
    } else if (dir == 2) {
        firstIsRed = state.rr < state.br;
    } else {
        firstIsRed = state.rr > state.br;
    }

    redHole = false;
    blueHole = false;
    pair<int, int> redPos, bluePos;

    if (firstIsRed) {
        redPos = roll(state.rr, state.rc, dir, redHole, state.br, state.bc);
        bluePos = roll(state.br, state.bc, dir, blueHole,
                       redHole ? -1 : redPos.first,
                       redHole ? -1 : redPos.second);
    } else {
        bluePos = roll(state.br, state.bc, dir, blueHole, state.rr, state.rc);
        redPos = roll(state.rr, state.rc, dir, redHole,
                      blueHole ? -1 : bluePos.first,
                      blueHole ? -1 : bluePos.second);
    }

    if (!redHole) {
        state.rr = redPos.first;
        state.rc = redPos.second;
    }
    if (!blueHole) {
        state.br = bluePos.first;
        state.bc = bluePos.second;
    }
    return redHole && !blueHole;
}

void validateSequence(InStream& stream, const string& sequence) {
    State state = startState;
    for (int i = 0; i < (int)sequence.size(); ++i) {
        int dir = directionIndex(sequence[i]);
        if (dir == -1) {
            quitStream(stream, _wa, "move %d has invalid direction '%c'", i + 1, sequence[i]);
        }

        bool redHole, blueHole;
        bool success = applyMove(state, dir, redHole, blueHole);
        if (blueHole) {
            quitStream(stream, _wa, "blue ball falls into the hole after move %d", i + 1);
        }
        if (redHole && !success) {
            quitStream(stream, _wa, "red ball falls into the hole unsuccessfully after move %d", i + 1);
        }
        if (success && i + 1 != (int)sequence.size()) {
            quitStream(stream, _wa, "sequence continues after success at move %d", i + 1);
        }
    }

    bool redHole, blueHole;
    State replay = startState;
    bool success = false;
    for (int i = 0; i < (int)sequence.size(); ++i) {
        success = applyMove(replay, directionIndex(sequence[i]), redHole, blueHole);
        if (success) break;
    }
    if (!success) {
        quitStream(stream, _wa, "red ball does not fall into the hole");
    }
}

Answer readAnswer(InStream& stream) {
    int moves = stream.readInt(-1, 10, "move count");
    if (moves == -1) {
        if (!stream.seekEof()) {
            quitStream(stream, _wa, "extra output after -1");
        }
        return {-1};
    }

    if (moves == 0) {
        quitStream(stream, _wa, "move count must be -1 or between 1 and 10");
    }

    string sequence = stream.readToken("[LRUD]{1,10}", "move sequence");
    if (!stream.seekEof()) {
        quitStream(stream, _wa, "extra output after move sequence");
    }
    if ((int)sequence.size() != moves) {
        quitStream(stream, _wa, "move count %d does not match sequence length %d",
                   moves, (int)sequence.size());
    }

    validateSequence(stream, sequence);
    return {moves};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    N = inf.readInt();
    M = inf.readInt();
    board.resize(N);
    holeR = holeC = -1;
    startState = {-1, -1, -1, -1};

    for (int i = 0; i < N; ++i) {
        board[i] = inf.readToken();
        for (int j = 0; j < M; ++j) {
            if (board[i][j] == 'O') {
                holeR = i;
                holeC = j;
            } else if (board[i][j] == 'R') {
                startState.rr = i;
                startState.rc = j;
            } else if (board[i][j] == 'B') {
                startState.br = i;
                startState.bc = j;
            }
        }
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.moves == -1) {
        if (participant.moves == -1) {
            quitf(_ok, "both outputs report no solution within 10 moves");
        }
        quitf(_fail, "participant found a valid solution in %d moves, but jury reported -1",
              participant.moves);
    }
    if (participant.moves == -1) {
        quitf(_wa, "participant reported -1, but jury has a %d-move solution", jury.moves);
    }
    if (participant.moves > jury.moves) {
        quitf(_wa, "participant uses %d moves, jury uses %d moves",
              participant.moves, jury.moves);
    }
    if (participant.moves < jury.moves) {
        quitf(_fail, "participant found a shorter solution: participant=%d jury=%d",
              participant.moves, jury.moves);
    }
    quitf(_ok, "valid shortest solution with %d moves", participant.moves);
}
