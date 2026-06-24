#include "testlib.h"

#include <vector>

using namespace std;

struct Claim {
    int boxCount;
    int boxSize;
    long long popcountSum;
};

Claim readClaim(InStream& stream, int n, int k) {
    const int boxCount = 1 << k;
    const int boxSize = 1 << (n - k);
    const int valueCount = 1 << n;

    vector<char> used(valueCount, 0);
    long long expectedSum = -1;

    for (int box = 0; box < boxCount; ++box) {
        long long currentSum = 0;
        for (int pos = 0; pos < boxSize; ++pos) {
            int value = stream.readInt(0, valueCount - 1,
                                       format("box[%d][%d]", box + 1, pos + 1).c_str());
            if (used[value]) {
                stream.quitf(_wa, "value %d appears more than once", value);
            }
            used[value] = 1;
            currentSum += __builtin_popcount((unsigned)value);
        }
        if (!stream.seekEoln()) {
            stream.quitf(_wa, "box %d has extra output after %d values", box + 1, boxSize);
        }

        if (box == 0) {
            expectedSum = currentSum;
        } else if (currentSum != expectedSum) {
            stream.quitf(_wa,
                         "box %d has popcount sum %lld instead of %lld",
                         box + 1,
                         currentSum,
                         expectedSum);
        }
    }

    stream.readEof();
    return {boxCount, boxSize, expectedSum};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int k = inf.readInt();

    Claim jury = readClaim(ans, n, k);
    Claim participant = readClaim(ouf, n, k);

    if (jury.boxCount != participant.boxCount || jury.boxSize != participant.boxSize) {
        quitf(_fail, "internal checker mismatch while comparing claims");
    }

    quitf(_ok,
          "%d boxes of %d values each, popcount sum %lld",
          participant.boxCount,
          participant.boxSize,
          participant.popcountSum);
}
