#include "testlib.h"

#include <vector>
using namespace std;

struct Rain {
    int t;
    long long r;
};

struct Claim {
    bool impossible;
    int rainIndex;
    int floor;
};

int n, m;
long long k;
vector<Rain> rains;

Claim readClaim(InStream& stream) {
    int first = stream.readInt(-1, m, "rain index or -1");
    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true, -1, -1};
    }
    if (first == 0) {
        stream.quitf(_wa, "rain index must be -1 or between 1 and %d", m);
    }

    int floor = stream.readInt(1, n, "collapsed floor");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after collapse claim");
    }
    return {false, first, floor};
}

bool isValidCollapseClaim(const Claim& claim) {
    if (claim.impossible) {
        return false;
    }

    long long before = 0;
    for (int i = 1; i < claim.rainIndex; ++i) {
        if (claim.floor <= rains[i].t) {
            before += rains[i].r;
        }
    }

    long long after = before;
    if (claim.floor <= rains[claim.rainIndex].t) {
        after += rains[claim.rainIndex].r;
    }

    return before <= k && after > k;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    k = inf.readLong();

    rains.assign(m + 1, {0, 0});
    for (int i = 1; i <= m; ++i) {
        rains[i].t = inf.readInt();
        rains[i].r = inf.readLong();
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (!jury.impossible && !isValidCollapseClaim(jury)) {
        quitf(_fail,
              "jury collapse claim is invalid: rain=%d floor=%d",
              jury.rainIndex,
              jury.floor);
    }

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim no collapse");
        }
        if (isValidCollapseClaim(participant)) {
            quitf(_fail,
                  "participant found a valid collapse while jury claims -1: rain=%d floor=%d",
                  participant.rainIndex,
                  participant.floor);
        }
        quitf(_wa,
              "jury claims -1 but participant collapse claim is invalid: rain=%d floor=%d",
              participant.rainIndex,
              participant.floor);
    }

    if (participant.impossible) {
        quitf(_wa,
              "jury reports collapse at rain %d but participant claims -1",
              jury.rainIndex);
    }

    if (!isValidCollapseClaim(participant)) {
        quitf(_wa,
              "participant collapse claim is invalid: rain=%d floor=%d",
              participant.rainIndex,
              participant.floor);
    }

    if (participant.rainIndex != jury.rainIndex) {
        quitf(_wa,
              "collapse rain differs from jury: expected %d, found %d",
              jury.rainIndex,
              participant.rainIndex);
    }

    quitf(_ok, "valid collapse claim at rain %d", participant.rainIndex);
}
