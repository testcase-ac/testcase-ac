#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

struct Claim {
    int moves;
};

int n;
vector<pair<int, int>> initialPos;

int cellId(int r, int c) {
    return (r - 1) * n + (c - 1);
}

Claim readClaim(InStream& stream) {
    int k = stream.readInt(0, 1000000000, "K");
    stream.readEoln();

    vector<pair<int, int>> pos = initialPos;
    vector<int> occupied(n * n, 0);
    for (int i = 1; i <= n; ++i) {
        occupied[cellId(pos[i].first, pos[i].second)] = i;
    }

    for (int move = 1; move <= k; ++move) {
        int tank = stream.readInt(1, n, format("tank[%d]", move).c_str());
        stream.readSpace();
        string dir = stream.readToken("[LRUD]", format("direction[%d]", move).c_str());
        stream.readEoln();

        int nr = pos[tank].first;
        int nc = pos[tank].second;
        if (dir[0] == 'L') --nc;
        if (dir[0] == 'R') ++nc;
        if (dir[0] == 'U') --nr;
        if (dir[0] == 'D') ++nr;

        if (nr < 1 || nr > n || nc < 1 || nc > n) {
            stream.quitf(_wa, "move %d sends tank %d outside the board to (%d, %d)",
                         move, tank, nr, nc);
        }

        int oldCell = cellId(pos[tank].first, pos[tank].second);
        int newCell = cellId(nr, nc);
        if (occupied[newCell] != 0) {
            stream.quitf(_wa, "move %d sends tank %d into occupied cell (%d, %d)",
                         move, tank, nr, nc);
        }

        occupied[oldCell] = 0;
        occupied[newCell] = tank;
        pos[tank] = {nr, nc};
    }
    stream.readEof();

    vector<int> rows(n + 1, 0), cols(n + 1, 0);
    for (int tank = 1; tank <= n; ++tank) {
        int r = pos[tank].first;
        int c = pos[tank].second;
        if (++rows[r] > 1) {
            stream.quitf(_wa, "row %d contains more than one tank after all moves", r);
        }
        if (++cols[c] > 1) {
            stream.quitf(_wa, "column %d contains more than one tank after all moves", c);
        }
    }

    return {k};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    initialPos.assign(n + 1, {0, 0});
    for (int i = 1; i <= n; ++i) {
        int r = inf.readInt();
        int c = inf.readInt();
        initialPos[i] = {r, c};
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (participant.moves > jury.moves) {
        quitf(_wa, "participant uses more moves than jury: participant=%d jury=%d",
              participant.moves, jury.moves);
    }
    if (participant.moves < jury.moves) {
        quitf(_fail, "participant found a better valid answer: participant=%d jury=%d",
              participant.moves, jury.moves);
    }

    quitf(_ok, "valid sequence with %d moves", participant.moves);
}
