#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

int n, m;
set<pair<int, int>> edges;

struct Output {
    bool possible;
    vector<int> color;
};

Output readOutput(InStream& stream) {
    int first = stream.readInt(-1, 3, "first token");
    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {false, {}};
    }
    if (first == 0) {
        stream.quitf(_wa, "vertex 1 is assigned to invalid set 0");
    }

    vector<int> color(n + 1);
    vector<int> count(4, 0);
    color[1] = first;
    ++count[first];

    for (int i = 2; i <= n; ++i) {
        color[i] = stream.readInt(1, 3, format("set[%d]", i).c_str());
        ++count[color[i]];
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after assignment");
    }

    for (int c = 1; c <= 3; ++c) {
        if (count[c] == 0) {
            stream.quitf(_wa, "set %d is empty", c);
        }
    }

    for (auto [u, v] : edges) {
        if (color[u] == color[v]) {
            stream.quitf(_wa, "edge (%d, %d) has both endpoints in set %d", u, v, color[u]);
        }
    }

    long long requiredEdges = 0;
    requiredEdges += 1LL * count[1] * count[2];
    requiredEdges += 1LL * count[1] * count[3];
    requiredEdges += 1LL * count[2] * count[3];
    if (requiredEdges != m) {
        stream.quitf(_wa,
                     "assignment requires %lld cross-set edges, but graph has %d edges",
                     requiredEdges,
                     m);
    }

    return {true, color};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    for (int i = 0; i < m; ++i) {
        int u = inf.readInt();
        int v = inf.readInt();
        edges.insert({u, v});
    }

    Output jury = readOutput(ans);
    Output participant = readOutput(ouf);

    if (!jury.possible) {
        if (!participant.possible) {
            quitf(_ok, "both outputs report impossibility");
        }
        quitf(_fail, "participant found a valid assignment while jury reports impossibility");
    }

    if (!participant.possible) {
        quitf(_wa, "jury has a valid assignment but participant reports impossibility");
    }

    quitf(_ok, "valid complete tripartite assignment");
}
