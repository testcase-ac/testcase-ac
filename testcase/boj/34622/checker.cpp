#include "testlib.h"

using namespace std;

struct Claim {
    bool impossible;
};

long long N, M, initialSpacing, targetSpacing, targetX, targetY;

Claim readClaim(InStream& stream) {
    int commandCount = stream.readInt(-1, 3, "command count");
    if (commandCount == -1) {
        stream.readEoln();
        stream.readEof();
        return {true};
    }

    stream.readEoln();

    long long originX = 0;
    long long originY = 0;
    long long spacing = initialSpacing;

    for (int commandIndex = 1; commandIndex <= commandCount; ++commandIndex) {
        long long i = stream.readLong(1, N, format("i[%d]", commandIndex).c_str());
        stream.readSpace();
        long long j = stream.readLong(1, M, format("j[%d]", commandIndex).c_str());
        stream.readSpace();
        long long nextSpacing = stream.readLong(1, 1000000000LL, format("k[%d]", commandIndex).c_str());
        stream.readEoln();

        originX += (spacing - nextSpacing) * (i - 1);
        originY += (spacing - nextSpacing) * (j - 1);
        spacing = nextSpacing;
    }

    stream.readEof();

    if (originX != targetX || originY != targetY || spacing != targetSpacing) {
        stream.quitf(_wa,
                     "commands end at (%lld, %lld) with spacing %lld, expected (%lld, %lld) with spacing %lld",
                     originX, originY, spacing, targetX, targetY, targetSpacing);
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    N = inf.readLong();
    M = inf.readLong();
    initialSpacing = inf.readLong();
    targetSpacing = inf.readLong();
    targetX = inf.readLong();
    targetY = inf.readLong();

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (!jury.impossible) {
        if (participant.impossible) {
            quitf(_wa, "participant reported impossible, but jury has a valid command sequence");
        }
        quitf(_ok, "valid command sequence");
    }

    if (participant.impossible) {
        quitf(_ok, "both outputs report impossible");
    }

    quitf(_fail, "participant found a valid command sequence while jury reports impossible");
}
