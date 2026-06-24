#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

struct Claim {
    int fixedCount;
    int operations;
};

int n;
vector<int> initialCards;

Claim readClaim(InStream& stream) {
    int op = stream.readInt(0, n * n, "op");
    vector<int> cards = initialCards;

    for (int i = 0; i < op; ++i) {
        int l = stream.readInt(1, n, format("L[%d]", i + 1).c_str());
        int r = stream.readInt(1, n, format("R[%d]", i + 1).c_str());
        if (l >= r) {
            stream.quitf(_wa, "operation %d has L=%d and R=%d, expected L < R", i + 1, l, r);
        }
        reverse(cards.begin() + l, cards.begin() + r + 1);
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after operation list");
    }

    int fixedCount = 0;
    for (int i = 1; i <= n; ++i) {
        if (cards[i] == i) {
            ++fixedCount;
        }
    }
    return {fixedCount, op};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 1000, "n");
    inf.readEoln();
    initialCards.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        initialCards[i] = inf.readInt(1, n, format("a[%d]", i).c_str());
        if (i < n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }
    inf.readEof();

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (participant.fixedCount < jury.fixedCount) {
        quitf(_wa,
              "participant fixes %d cards, but jury fixes %d cards",
              participant.fixedCount,
              jury.fixedCount);
    }
    if (participant.fixedCount > jury.fixedCount) {
        quitf(_fail,
              "participant fixes %d cards, better than jury's %d cards",
              participant.fixedCount,
              jury.fixedCount);
    }

    quitf(_ok,
          "fixed cards=%d, participant operations=%d, jury operations=%d",
          participant.fixedCount,
          participant.operations,
          jury.operations);
}
