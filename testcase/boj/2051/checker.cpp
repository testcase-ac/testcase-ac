#include "testlib.h"

#include <vector>

using namespace std;

int n, m;
vector<vector<int>> adj;

struct Answer {
    int claimedSize;
    int aCount;
    int bCount;
};

Answer readAnswer(InStream& stream) {
    int claimedSize = stream.readInt(0, n + m, "cover size");
    stream.readEoln();

    int aCount = stream.readInt(0, n, "A count");
    vector<int> inA(n + 1, 0);
    for (int i = 0; i < aCount; ++i) {
        stream.readSpace();
        int a = stream.readInt(1, n, format("A vertex[%d]", i + 1).c_str());
        if (inA[a]) {
            stream.quitf(_wa, "A vertex %d is repeated", a);
        }
        inA[a] = 1;
    }
    stream.readEoln();

    int bCount = stream.readInt(0, m, "B count");
    vector<int> inB(m + 1, 0);
    for (int i = 0; i < bCount; ++i) {
        stream.readSpace();
        int b = stream.readInt(1, m, format("B vertex[%d]", i + 1).c_str());
        if (inB[b]) {
            stream.quitf(_wa, "B vertex %d is repeated", b);
        }
        inB[b] = 1;
    }
    stream.readEoln();
    stream.readEof();

    if (claimedSize != aCount + bCount) {
        stream.quitf(_wa,
                     "claimed cover size %d differs from listed size %d",
                     claimedSize,
                     aCount + bCount);
    }

    for (int a = 1; a <= n; ++a) {
        for (int b : adj[a]) {
            if (!inA[a] && !inB[b]) {
                stream.quitf(_wa, "edge A%d-B%d is not covered", a, b);
            }
        }
    }

    return {claimedSize, aCount, bCount};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    adj.assign(n + 1, {});
    for (int a = 1; a <= n; ++a) {
        int degree = inf.readInt();
        adj[a].resize(degree);
        for (int i = 0; i < degree; ++i) {
            adj[a][i] = inf.readInt();
        }
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.claimedSize < jury.claimedSize) {
        quitf(_fail,
              "participant found smaller valid cover: jury=%d participant=%d",
              jury.claimedSize,
              participant.claimedSize);
    }
    if (participant.claimedSize > jury.claimedSize) {
        quitf(_wa,
              "cover is not minimum: jury=%d participant=%d",
              jury.claimedSize,
              participant.claimedSize);
    }

    quitf(_ok,
          "minimum vertex cover size %d, A count %d, B count %d",
          participant.claimedSize,
          participant.aCount,
          participant.bCount);
}
