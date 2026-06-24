#include "testlib.h"

#include <set>
using namespace std;

const long long LIMIT = 1000000000000000000LL;
const int MAX_STEPS = 43;

struct Claim {
    int steps;
};

Claim readClaim(InStream& stream, long long target) {
    set<long long> values = {0, 1, 2};

    int steps = 0;
    while (!stream.seekEof()) {
        if (steps == MAX_STEPS) {
            stream.quitf(_wa, "more than %d steps", MAX_STEPS);
        }

        long long x = stream.readLong(0LL, LIMIT, format("x[%d]", steps + 1).c_str());
        long long y = stream.readLong(0LL, LIMIT, format("y[%d]", steps + 1).c_str());

        if (!values.count(x)) {
            stream.quitf(_wa, "x[%d]=%lld is not in the set", steps + 1, x);
        }
        if (!values.count(y)) {
            stream.quitf(_wa, "y[%d]=%lld is not in the set", steps + 1, y);
        }

        __int128 inserted = (__int128)x * x - y;
        if (inserted < 0 || inserted > LIMIT) {
            stream.quitf(_wa, "x[%d]^2-y[%d] is outside [0, 10^18]", steps + 1, steps + 1);
        }

        values.insert((long long)inserted);
        ++steps;
    }

    if (!values.count(target)) {
        stream.quitf(_wa, "target %lld was not constructed", target);
    }

    return {steps};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    long long target = inf.readLong(0LL, LIMIT, "n");

    Claim jury = readClaim(ans, target);
    Claim participant = readClaim(ouf, target);

    quitf(_ok, "constructed %lld in %d steps; jury used %d steps",
          target, participant.steps, jury.steps);
}
