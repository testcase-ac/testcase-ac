#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

struct ClaimedColoring {
    long long claimedScore;
    long long actualScore;
    string colors;
};

int n;
vector<pair<int, int>> edges;
vector<vector<int>> beauty;

ClaimedColoring readClaim(InStream& stream, TResult invalidOutcome) {
    long long claimedScore = stream.readLong(0, 1LL * n * 1000, "claimed score");
    stream.readEoln();

    string colors = stream.readToken();
    stream.readEoln();
    stream.readEof();

    if ((int)colors.size() != n) {
        stream.quitf(invalidOutcome, "color string length is %d instead of %d", (int)colors.size(), n);
    }

    long long actualScore = 0;
    for (int i = 0; i < n; ++i) {
        int color = -1;
        if (colors[i] == 'R') {
            color = 0;
        } else if (colors[i] == 'G') {
            color = 1;
        } else if (colors[i] == 'B') {
            color = 2;
        } else {
            stream.quitf(invalidOutcome, "invalid color '%c' at position %d", colors[i], i + 1);
        }
        actualScore += beauty[i + 1][color];
    }

    for (const auto& edge : edges) {
        int u = edge.first;
        int v = edge.second;
        if (colors[u - 1] == colors[v - 1]) {
            stream.quitf(invalidOutcome, "adjacent vertices %d and %d both have color %c", u, v, colors[u - 1]);
        }
    }

    if (claimedScore != actualScore) {
        stream.quitf(invalidOutcome, "claimed score %lld does not match coloring score %lld", claimedScore, actualScore);
    }

    return {claimedScore, actualScore, colors};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    edges.reserve(max(0, n - 1));
    for (int i = 0; i < n - 1; ++i) {
        int u = inf.readInt();
        int v = inf.readInt();
        edges.push_back({u, v});
    }

    beauty.assign(n + 1, vector<int>(3));
    for (int i = 1; i <= n; ++i) {
        for (int c = 0; c < 3; ++c) {
            beauty[i][c] = inf.readInt();
        }
    }

    ClaimedColoring jury = readClaim(ans, _fail);
    ClaimedColoring participant = readClaim(ouf, _wa);

    if (participant.actualScore < jury.actualScore) {
        quitf(_wa, "participant score %lld is lower than jury score %lld", participant.actualScore, jury.actualScore);
    }
    if (participant.actualScore > jury.actualScore) {
        quitf(_fail, "participant score %lld is better than jury score %lld", participant.actualScore, jury.actualScore);
    }

    quitf(_ok, "score %lld", participant.actualScore);
}
