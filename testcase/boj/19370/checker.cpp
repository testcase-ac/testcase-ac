#include "testlib.h"

#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int n, k;

struct DSU {
    vector<int> parent;

    explicit DSU(int size) : parent(size + 1) {
        iota(parent.begin(), parent.end(), 0);
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
    bool impossible;
};

Answer readAnswer(InStream& stream) {
    int first = stream.readInt(-1, n, "first token");
    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true};
    }
    if (first == 0) {
        stream.quitf(_wa, "vertex 0 is outside range [1, %d]", n);
    }

    set<pair<int, int>> usedEdges;
    for (int tree = 1; tree <= k; ++tree) {
        DSU dsu(n);
        for (int edgeIndex = 1; edgeIndex <= n - 1; ++edgeIndex) {
            int u = first;
            if (!(tree == 1 && edgeIndex == 1)) {
                u = stream.readInt(1, n, format("tree %d edge %d endpoint u", tree, edgeIndex).c_str());
            }
            int v = stream.readInt(1, n, format("tree %d edge %d endpoint v", tree, edgeIndex).c_str());
            if (u == v) {
                stream.quitf(_wa, "tree %d edge %d is a self-loop at vertex %d", tree, edgeIndex, u);
            }

            pair<int, int> edge = minmax(u, v);
            if (!usedEdges.insert(edge).second) {
                stream.quitf(_wa, "edge (%d, %d) is reused", edge.first, edge.second);
            }
            if (!dsu.unite(u, v)) {
                stream.quitf(_wa, "tree %d contains a cycle at edge %d", tree, edgeIndex);
            }
        }

        int root = dsu.find(1);
        for (int vertex = 2; vertex <= n; ++vertex) {
            if (dsu.find(vertex) != root) {
                stream.quitf(_wa, "tree %d is disconnected: vertex %d is not connected to vertex 1", tree, vertex);
            }
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d spanning trees", k);
    }
    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    k = inf.readInt();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report impossible");
        }
        quitf(_fail, "participant provided valid spanning trees while jury reports impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "jury provides spanning trees but participant reports impossible");
    }
    quitf(_ok, "valid edge-disjoint spanning trees");
}
