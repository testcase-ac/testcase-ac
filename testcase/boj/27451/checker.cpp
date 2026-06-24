#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

int n, m, a, b, c;
vector<vector<bool>> edgeExists;

struct Claim {
    bool impossible;
    int meeting;
    int length;
};

Claim readClaim(InStream& stream) {
    int first = stream.readInt(-1, n, "first output token");
    if (first == -1) {
        stream.readEoln();
        stream.readEof();
        return {true, -1, -1};
    }

    int meeting = first;
    int length = stream.readInt(0, 1000000, "path length");
    stream.readEoln();

    vector<int> starts = {a, b, c};
    for (int pathIndex = 0; pathIndex < 3; ++pathIndex) {
        int previous = stream.readInt(1, n, format("path[%d][1]", pathIndex + 1).c_str());
        if (previous != starts[pathIndex]) {
            stream.quitf(_wa,
                         "path %d starts at %d instead of %d",
                         pathIndex + 1,
                         previous,
                         starts[pathIndex]);
        }

        for (int i = 0; i < length; ++i) {
            int current = stream.readInt(1, n, format("path[%d][%d]", pathIndex + 1, i + 2).c_str());
            if (!edgeExists[previous][current]) {
                stream.quitf(_wa,
                             "path %d uses missing directed edge %d -> %d at step %d",
                             pathIndex + 1,
                             previous,
                             current,
                             i + 1);
            }
            previous = current;
        }

        if (previous != meeting) {
            stream.quitf(_wa,
                         "path %d ends at %d instead of meeting restaurant %d",
                         pathIndex + 1,
                         previous,
                         meeting);
        }
        stream.readEoln();
    }

    stream.readEof();
    return {false, meeting, length};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    a = inf.readInt();
    b = inf.readInt();
    c = inf.readInt();

    edgeExists.assign(n + 1, vector<bool>(n + 1, false));
    for (int i = 0; i < m; ++i) {
        int s = inf.readInt();
        int e = inf.readInt();
        edgeExists[s][e] = true;
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report impossible");
        }
        quitf(_fail,
              "participant provided a valid meeting certificate of length %d while jury reports impossible",
              participant.length);
    }

    if (participant.impossible) {
        quitf(_wa, "participant reports impossible, but jury has a certificate");
    }

    if (participant.length < jury.length) {
        quitf(_fail,
              "participant has a shorter valid certificate: participant=%d jury=%d",
              participant.length,
              jury.length);
    }
    if (participant.length > jury.length) {
        quitf(_wa,
              "participant has a longer valid certificate: participant=%d jury=%d",
              participant.length,
              jury.length);
    }

    quitf(_ok, "valid meeting certificate with length %d", participant.length);
}
