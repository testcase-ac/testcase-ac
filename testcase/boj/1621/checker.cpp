#include "testlib.h"

#include <vector>

using namespace std;

int n, k, c;
vector<int> weight;

struct Answer {
    long long totalTime;
    int blockCount;
};

Answer readAnswer(InStream& stream) {
    long long claimedTime = stream.readLong(0, (long long)4e18, "total time");
    int blockCount = stream.readInt(0, n, "block count");

    vector<int> covered(n + 1, 0);
    int previousLeft = 0;

    for (int i = 0; i < blockCount; ++i) {
        int maxLeft = n - k + 1;
        if (maxLeft < 1) {
            stream.quitf(_wa, "block[%d] is present, but K=%d is larger than N=%d", i + 1, k, n);
        }

        int left = stream.readInt(1, maxLeft, format("block[%d]", i + 1).c_str());
        if (left <= previousLeft) {
            stream.quitf(_wa, "block positions are not strictly increasing at index %d", i + 1);
        }
        previousLeft = left;

        for (int pos = left; pos < left + k; ++pos) {
            if (covered[pos]) {
                stream.quitf(_wa, "banana position %d is covered by more than one block", pos);
            }
            covered[pos] = 1;
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after block positions");
    }

    long long actualTime = (long long)blockCount * c;
    for (int i = 1; i <= n; ++i) {
        if (!covered[i]) {
            actualTime += weight[i];
        }
    }

    if (actualTime != claimedTime) {
        stream.quitf(_wa, "claimed time %lld does not match certificate time %lld", claimedTime, actualTime);
    }

    return {actualTime, blockCount};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    k = inf.readInt();
    c = inf.readInt();
    weight.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        weight[i] = inf.readInt();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.totalTime != jury.totalTime) {
        if (participant.totalTime < jury.totalTime) {
            quitf(_fail, "participant found smaller time: jury=%lld participant=%lld",
                  jury.totalTime, participant.totalTime);
        }
        quitf(_wa, "jury has smaller time: jury=%lld participant=%lld",
              jury.totalTime, participant.totalTime);
    }

    if (participant.blockCount != jury.blockCount) {
        if (participant.blockCount < jury.blockCount) {
            quitf(_fail, "participant used fewer blocks for optimal time: jury=%d participant=%d",
                  jury.blockCount, participant.blockCount);
        }
        quitf(_wa, "jury uses fewer blocks for optimal time: jury=%d participant=%d",
              jury.blockCount, participant.blockCount);
    }

    quitf(_ok, "time=%lld blocks=%d", participant.totalTime, participant.blockCount);
}
