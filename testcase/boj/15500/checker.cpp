#include "testlib.h"

#include <vector>

using namespace std;

const int MAX_MOVES = 12345;

struct Claim {
    int moves;
};

int n;
vector<int> initial;

Claim readClaim(InStream& stream) {
    int k = stream.readInt(0, MAX_MOVES, "K");
    stream.readEoln();

    vector<vector<int>> rods(4);
    rods[1] = initial;

    for (int i = 0; i < k; ++i) {
        int from = stream.readInt(1, 3, format("move[%d].from", i + 1).c_str());
        stream.readSpace();
        int to = stream.readInt(1, 3, format("move[%d].to", i + 1).c_str());
        stream.readEoln();

        if (from == to) {
            stream.quitf(_wa, "move %d has the same source and destination rod %d", i + 1, from);
        }
        if (rods[from].empty()) {
            stream.quitf(_wa, "move %d tries to move from empty rod %d", i + 1, from);
        }

        int disk = rods[from].back();
        rods[from].pop_back();
        rods[to].push_back(disk);
    }

    stream.readEof();

    if (!rods[1].empty() || !rods[2].empty() || (int)rods[3].size() != n) {
        stream.quitf(_wa,
                     "after %d moves rod sizes are [%d, %d, %d], expected all %d disks on rod 3",
                     k,
                     (int)rods[1].size(),
                     (int)rods[2].size(),
                     (int)rods[3].size(),
                     n);
    }

    return {k};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 123, "N");
    inf.readEoln();
    initial = inf.readInts(n, 1, n, "a_i");
    inf.readEoln();
    inf.readEof();

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    quitf(_ok, "valid move sequence with %d moves, jury used %d moves", participant.moves, jury.moves);
}
