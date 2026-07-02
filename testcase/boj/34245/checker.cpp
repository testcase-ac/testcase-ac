#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int n, m;

struct Claim {
    long long edgeCount;
};

Claim readClaim(InStream& stream) {
    int k = stream.readInt(1, n - 1, "k");

    set<pair<int, int>> usedEdges;
    long long edgeCount = 0;

    for (int pathIndex = 1; pathIndex <= k; ++pathIndex) {
        int length = stream.readInt(2, n, format("path[%d].length", pathIndex));
        int previous = stream.readInt(1, n, format("path[%d][1]", pathIndex));
        if (previous != 1) {
            stream.quitf(_wa, "path %d starts at %d instead of 1", pathIndex, previous);
        }

        for (int position = 2; position <= length; ++position) {
            int current = stream.readInt(1, n, format("path[%d][%d]", pathIndex, position));
            if (previous >= current) {
                stream.quitf(_wa,
                             "path %d is not strictly increasing at positions %d and %d: %d >= %d",
                             pathIndex, position - 1, position, previous, current);
            }
            if (!usedEdges.insert({previous, current}).second) {
                stream.quitf(_wa,
                             "edge (%d, %d) is used by more than one path",
                             previous, current);
            }
            ++edgeCount;
            previous = current;
        }

        if (previous != n) {
            stream.quitf(_wa, "path %d ends at %d instead of %d", pathIndex, previous, n);
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d paths", k);
    }

    if (edgeCount < m) {
        stream.quitf(_wa, "only %lld edges are supplied, but at least %d are required", edgeCount, m);
    }

    return {edgeCount};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    quitf(_ok,
          "jury edges=%lld, participant edges=%lld",
          jury.edgeCount,
          participant.edgeCount);
}
