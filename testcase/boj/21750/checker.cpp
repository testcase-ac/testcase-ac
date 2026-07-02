#include "testlib.h"

#include <array>
#include <string>

using namespace std;

struct Square {
    int x;
    int y;
};

struct Claim {
    bool impossible;
    int moves;
};

Square whiteStart, blackStart, whiteTarget, blackTarget;

const array<int, 8> dx = {1, 1, 2, 2, -1, -1, -2, -2};
const array<int, 8> dy = {2, -2, 1, -1, 2, -2, 1, -1};

Square readInputSquare() {
    string token = inf.readToken("[a-h][1-8]", "square");
    return {token[0] - 'a', token[1] - '1'};
}

bool sameSquare(Square a, Square b) {
    return a.x == b.x && a.y == b.y;
}

bool isKnightMove(Square from, Square to) {
    int ax = abs(from.x - to.x);
    int ay = abs(from.y - to.y);
    return (ax == 1 && ay == 2) || (ax == 2 && ay == 1);
}

Square readOutputSquare(InStream& stream, const char* name) {
    string token = stream.readToken("[a-h][1-8]", name);
    return {token[0] - 'a', token[1] - '1'};
}

Claim readClaim(InStream& stream) {
    int declaredMoves = stream.readInt(-1, 100000, "move count");
    stream.readEoln();

    if (declaredMoves == -1) {
        stream.readEof();
        return {true, -1};
    }

    Square white = whiteStart;
    Square black = blackStart;
    for (int i = 0; i < declaredMoves; ++i) {
        string color = stream.readToken("[WB]", format("move[%d].color", i + 1).c_str());
        Square next = readOutputSquare(stream, format("move[%d].square", i + 1).c_str());
        stream.readEoln();

        if (color == "W") {
            if (!isKnightMove(white, next)) {
                stream.quitf(_wa, "move %d is not a legal white knight move", i + 1);
            }
            if (sameSquare(next, black)) {
                stream.quitf(_wa, "move %d places white on black's square", i + 1);
            }
            white = next;
        } else {
            if (!isKnightMove(black, next)) {
                stream.quitf(_wa, "move %d is not a legal black knight move", i + 1);
            }
            if (sameSquare(next, white)) {
                stream.quitf(_wa, "move %d places black on white's square", i + 1);
            }
            black = next;
        }
    }

    stream.readEof();

    if (!sameSquare(white, whiteTarget)) {
        stream.quitf(_wa, "white ends on %c%d instead of target %c%d",
                     char('a' + white.x), white.y + 1,
                     char('a' + whiteTarget.x), whiteTarget.y + 1);
    }
    if (!sameSquare(black, blackTarget)) {
        stream.quitf(_wa, "black ends on %c%d instead of target %c%d",
                     char('a' + black.x), black.y + 1,
                     char('a' + blackTarget.x), blackTarget.y + 1);
    }

    return {false, declaredMoves};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    whiteStart = readInputSquare();
    blackStart = readInputSquare();
    whiteTarget = readInputSquare();
    blackTarget = readInputSquare();

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report impossible");
        }
        quitf(_fail, "participant found a valid %d-move sequence while jury says impossible",
              participant.moves);
    }
    if (participant.impossible) {
        quitf(_wa, "participant reports impossible, but jury has a %d-move sequence", jury.moves);
    }
    if (participant.moves > jury.moves) {
        quitf(_wa, "participant uses %d moves, jury uses %d", participant.moves, jury.moves);
    }
    if (participant.moves < jury.moves) {
        quitf(_fail, "participant found a shorter sequence: participant=%d jury=%d",
              participant.moves, jury.moves);
    }
    quitf(_ok, "valid %d-move sequence", participant.moves);
}
