#include "testlib.h"

#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int n, m;
vector<int> boundDegree;
map<pair<int, int>, int> edgeCost;

struct DSU {
    vector<int> parent;

    explicit DSU(int size) : parent(size + 1) {
        for (int i = 1; i <= size; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return false;
        }
        parent[b] = a;
        return true;
    }
};

struct Answer {
    bool exists;
    long long cost;
};

Answer readAnswer(InStream& stream) {
    string verdict = stream.readToken("[A-Z]+", "verdict");

    if (verdict == "NO") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after NO");
        }
        return {false, 0};
    }

    if (verdict != "YES") {
        stream.quitf(_wa, "verdict must be YES or NO, found '%s'", verdict.c_str());
    }

    DSU dsu(n);
    vector<int> degree(n + 1, 0);
    set<pair<int, int>> usedEdges;
    long long cost = 0;

    for (int i = 0; i < n - 1; ++i) {
        int a = stream.readInt(1, n, format("edge[%d].a", i + 1).c_str());
        int b = stream.readInt(1, n, format("edge[%d].b", i + 1).c_str());
        if (a >= b) {
            stream.quitf(_wa, "edge %d must be printed as a < b, found %d %d", i + 1, a, b);
        }

        pair<int, int> edge = {a, b};
        auto it = edgeCost.find(edge);
        if (it == edgeCost.end()) {
            stream.quitf(_wa, "edge %d (%d, %d) is not in the input graph", i + 1, a, b);
        }
        if (!usedEdges.insert(edge).second) {
            stream.quitf(_wa, "edge %d (%d, %d) is duplicated", i + 1, a, b);
        }
        if (!dsu.unite(a, b)) {
            stream.quitf(_wa, "edge %d (%d, %d) creates a cycle", i + 1, a, b);
        }

        ++degree[a];
        ++degree[b];
        if (degree[a] > boundDegree[a]) {
            stream.quitf(_wa, "degree of vertex %d is %d, exceeds bound %d",
                         a, degree[a], boundDegree[a]);
        }
        if (degree[b] > boundDegree[b]) {
            stream.quitf(_wa, "degree of vertex %d is %d, exceeds bound %d",
                         b, degree[b], boundDegree[b]);
        }
        cost += it->second;
    }

    if (n > 0) {
        int root = dsu.find(1);
        for (int v = 2; v <= n; ++v) {
            if (dsu.find(v) != root) {
                stream.quitf(_wa, "selected edges do not connect vertex %d to vertex 1", v);
            }
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after spanning tree");
    }
    return {true, cost};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    boundDegree.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        boundDegree[i] = inf.readInt();
    }
    for (int i = 0; i < m; ++i) {
        int a = inf.readInt();
        int b = inf.readInt();
        int c = inf.readInt();
        if (a > b) {
            swap(a, b);
        }
        edgeCost[{a, b}] = c;
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (!jury.exists) {
        if (!participant.exists) {
            quitf(_ok, "both outputs report NO");
        }
        quitf(_fail, "participant found a valid spanning tree with cost %lld while jury reports NO",
              participant.cost);
    }

    if (!participant.exists) {
        quitf(_wa, "jury has a valid spanning tree with cost %lld, participant reports NO", jury.cost);
    }

    if (participant.cost < jury.cost) {
        quitf(_fail, "participant found better spanning tree: participant=%lld jury=%lld",
              participant.cost, jury.cost);
    }
    if (participant.cost > jury.cost) {
        quitf(_wa, "participant spanning tree is not optimal: participant=%lld jury=%lld",
              participant.cost, jury.cost);
    }

    quitf(_ok, "valid optimal spanning tree with cost %lld", participant.cost);
}
