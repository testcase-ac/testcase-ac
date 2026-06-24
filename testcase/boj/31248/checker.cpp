#include "testlib.h"

#include <vector>
using namespace std;

struct Claim {
    long long moves;
};

int n;

int pegIndex(const string& token, InStream& stream, const char* name, long long moveIndex) {
    if (token.size() != 1 || token[0] < 'A' || token[0] > 'D') {
        stream.quitf(_wa, "move %lld has invalid %s peg '%s'", moveIndex, name, token.c_str());
    }
    return token[0] - 'A';
}

Claim readClaim(InStream& stream) {
    const long long maxMoves = 10000000LL;
    long long m = stream.readLong(0, maxMoves, "M");
    stream.readEoln();

    vector<vector<int>> peg(4);
    for (int disk = n; disk >= 1; --disk) {
        peg[0].push_back(disk);
    }

    for (long long i = 1; i <= m; ++i) {
        string fromToken = stream.readToken("[A-D]", format("move[%lld].from", i).c_str());
        string toToken = stream.readToken("[A-D]", format("move[%lld].to", i).c_str());
        stream.readEoln();

        int from = pegIndex(fromToken, stream, "source", i);
        int to = pegIndex(toToken, stream, "destination", i);

        if (from == to) {
            stream.quitf(_wa, "move %lld uses the same source and destination peg %c", i, char('A' + from));
        }
        if (from == 3) {
            stream.quitf(_wa, "move %lld moves a disk out of peg D", i);
        }
        if (peg[from].empty()) {
            stream.quitf(_wa, "move %lld moves from empty peg %c", i, char('A' + from));
        }

        int disk = peg[from].back();
        if (!peg[to].empty() && peg[to].back() < disk) {
            stream.quitf(_wa,
                         "move %lld places disk %d on smaller disk %d",
                         i,
                         disk,
                         peg[to].back());
        }

        peg[from].pop_back();
        peg[to].push_back(disk);
    }

    stream.readEof();

    if ((int)peg[3].size() != n) {
        stream.quitf(_wa, "after %lld moves, peg D contains %d disks instead of %d", m, (int)peg[3].size(), n);
    }
    for (int disk = n; disk >= 1; --disk) {
        int pos = n - disk;
        if (peg[3][pos] != disk) {
            stream.quitf(_wa, "peg D has disk %d at position %d instead of disk %d", peg[3][pos], pos + 1, disk);
        }
    }

    return {m};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 20, "N");

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (participant.moves < jury.moves) {
        quitf(_fail,
              "participant has a valid shorter sequence: jury=%lld participant=%lld",
              jury.moves,
              participant.moves);
    }
    if (participant.moves > jury.moves) {
        quitf(_wa,
              "participant uses more moves than jury: jury=%lld participant=%lld",
              jury.moves,
              participant.moves);
    }

    quitf(_ok, "valid sequence with %lld moves", participant.moves);
}
