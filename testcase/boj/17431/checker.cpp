#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

struct Claim {
    vector<int> lengths;
};

int t;
vector<long long> xs;

long long addChecked(long long a, long long b, int caseIndex, InStream& stream) {
    if (a > (long long)4e18 - b) {
        stream.quitf(_wa, "case %d overflows while simulating moves", caseIndex);
    }
    return a + b;
}

int validateMoves(const string& moves, long long target, int caseIndex, InStream& stream) {
    long long blue = 1;
    long long red = 1;

    if (target == 1) {
        if (!moves.empty()) {
            stream.quitf(_wa, "case %d has %d moves, but x is already 1", caseIndex, (int)moves.size());
        }
        return 0;
    }

    for (int i = 0; i < (int)moves.size(); ++i) {
        char move = moves[i];
        if (move != 'B' && move != 'R') {
            stream.quitf(_wa, "case %d move %d is '%c', expected B or R", caseIndex, i + 1, move);
        }

        long long sum = addChecked(blue, red, caseIndex, stream);
        if (move == 'B') {
            blue = sum;
        } else {
            red = sum;
        }

        bool reached = (blue == target || red == target);
        if (i + 1 < (int)moves.size() && reached) {
            stream.quitf(_wa, "case %d reaches x after move %d before the output ends", caseIndex, i + 1);
        }
        if (blue > target && red > target) {
            stream.quitf(_wa, "case %d passes x after move %d without reaching it", caseIndex, i + 1);
        }
    }

    if (blue != target && red != target) {
        stream.quitf(_wa, "case %d ends at (%lld, %lld), not x=%lld", caseIndex, blue, red, target);
    }
    return (int)moves.size();
}

Claim readClaim(InStream& stream) {
    Claim claim;
    claim.lengths.reserve(t);
    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        string moves = stream.readLine();
        claim.lengths.push_back(validateMoves(moves, xs[caseIndex - 1], caseIndex, stream));
    }
    stream.readEof();
    return claim;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    t = inf.readInt();
    xs.resize(t);
    for (int i = 0; i < t; ++i) {
        xs[i] = inf.readLong();
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    for (int i = 0; i < t; ++i) {
        if (participant.lengths[i] < jury.lengths[i]) {
            quitf(_fail,
                  "case %d participant found shorter valid sequence: participant=%d jury=%d",
                  i + 1,
                  participant.lengths[i],
                  jury.lengths[i]);
        }
        if (participant.lengths[i] > jury.lengths[i]) {
            quitf(_wa,
                  "case %d sequence is longer than jury optimum: participant=%d jury=%d",
                  i + 1,
                  participant.lengths[i],
                  jury.lengths[i]);
        }
    }

    quitf(_ok, "all %d certificates match the jury optimum lengths", t);
}
