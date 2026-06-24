#include "testlib.h"

#include <algorithm>
#include <map>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Dsu {
    vector<int> parent;

    explicit Dsu(int n) : parent(n + 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) parent[b] = a;
    }
};

int n, m;
int terminalA, terminalB, terminalC;
map<pair<int, int>, int> edgeCost;

struct Answer {
    long long cost;
    int edgeCount;
};

Answer readAnswer(InStream& stream) {
    long long claimedCost = stream.readLong(0, 1'000'000'000'000LL, "cost");
    int r = stream.readInt(0, m, "edge count");
    stream.readEoln();

    long long actualCost = 0;
    Dsu dsu(n);
    set<pair<int, int>> usedEdges;

    for (int i = 1; i <= r; ++i) {
        int u = stream.readInt(1, n, format("edge[%d].u", i).c_str());
        int v = stream.readInt(1, n, format("edge[%d].v", i).c_str());
        stream.readEoln();

        if (u == v) {
            stream.quitf(_wa, "edge %d is a self-loop: %d", i, u);
        }

        auto edge = minmax(u, v);
        auto it = edgeCost.find(edge);
        if (it == edgeCost.end()) {
            stream.quitf(_wa, "edge %d (%d, %d) is not in the input graph", i, u, v);
        }
        if (!usedEdges.insert(edge).second) {
            stream.quitf(_wa, "edge %d (%d, %d) is repeated", i, u, v);
        }

        actualCost += it->second;
        dsu.unite(u, v);
    }

    stream.readEof();

    if (actualCost != claimedCost) {
        stream.quitf(_wa, "claimed cost %lld differs from selected edge cost %lld", claimedCost, actualCost);
    }

    int root = dsu.find(terminalA);
    if (dsu.find(terminalB) != root || dsu.find(terminalC) != root) {
        stream.quitf(_wa,
                     "selected links do not connect terminals %d, %d, and %d",
                     terminalA,
                     terminalB,
                     terminalC);
    }

    return {actualCost, r};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    for (int i = 0; i < m; ++i) {
        int u = inf.readInt();
        int v = inf.readInt();
        int w = inf.readInt();
        edgeCost[minmax(u, v)] = w;
    }
    terminalA = inf.readInt();
    terminalB = inf.readInt();
    terminalC = inf.readInt();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.cost < jury.cost) {
        quitf(_fail,
              "participant found a better valid network: participant=%lld jury=%lld",
              participant.cost,
              jury.cost);
    }
    if (participant.cost > jury.cost) {
        quitf(_wa, "participant cost %lld is worse than jury cost %lld", participant.cost, jury.cost);
    }

    quitf(_ok, "minimum cost %lld with %d selected links", participant.cost, participant.edgeCount);
}
