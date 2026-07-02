#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Claim {
    string moves;
};

int n, targetRow, targetCol;

Claim readClaim(InStream& stream) {
    string moves = stream.readToken("[UDLR]*", "moves");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after move string");
    }

    int limit = 3 * (n - 1);
    if ((int)moves.size() > limit) {
        stream.quitf(_wa, "move string length %d exceeds limit %d", (int)moves.size(), limit);
    }

    int rowLow = 1, rowHigh = n;
    int colLow = 1, colHigh = n;
    for (int i = 0; i < (int)moves.size(); ++i) {
        char move = moves[i];
        if (move == 'U') {
            rowLow = max(1, rowLow - 1);
            rowHigh = max(1, rowHigh - 1);
        } else if (move == 'D') {
            rowLow = min(n, rowLow + 1);
            rowHigh = min(n, rowHigh + 1);
        } else if (move == 'L') {
            colLow = max(1, colLow - 1);
            colHigh = max(1, colHigh - 1);
        } else if (move == 'R') {
            colLow = min(n, colLow + 1);
            colHigh = min(n, colHigh + 1);
        }
    }

    if (rowLow != targetRow || rowHigh != targetRow || colLow != targetCol || colHigh != targetCol) {
        stream.quitf(_wa,
                     "moves end with occupied rows [%d, %d] and columns [%d, %d], expected (%d, %d)",
                     rowLow, rowHigh, colLow, colHigh, targetRow, targetCol);
    }

    return {moves};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    targetRow = inf.readInt();
    targetCol = inf.readInt();

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    quitf(_ok,
          "valid sequence of length %d; jury length %d",
          (int)participant.moves.size(),
          (int)jury.moves.size());
}
