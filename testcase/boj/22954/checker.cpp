#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

struct DSU {
    vector<int> parent;

    explicit DSU(int n) : parent(n + 1) {
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

struct Edge {
    int u;
    int v;
};

struct Answer {
    bool impossible;
};

int n, m;
vector<Edge> edges;

void validateTree(InStream& stream,
                  const vector<int>& vertices,
                  const vector<int>& edgeIds,
                  const vector<int>& owner,
                  int treeIndex) {
    DSU dsu(n);

    for (int edgeId : edgeIds) {
        const Edge& edge = edges[edgeId];
        if (owner[edge.u] != treeIndex || owner[edge.v] != treeIndex) {
            stream.quitf(_wa,
                         "tree %d edge %d has endpoint outside the tree: %d %d",
                         treeIndex,
                         edgeId,
                         edge.u,
                         edge.v);
        }
        if (!dsu.unite(edge.u, edge.v)) {
            stream.quitf(_wa, "tree %d contains a cycle at edge %d", treeIndex, edgeId);
        }
    }

    int root = dsu.find(vertices[0]);
    for (int vertex : vertices) {
        if (dsu.find(vertex) != root) {
            stream.quitf(_wa, "tree %d is not connected", treeIndex);
        }
    }
}

Answer readAnswer(InStream& stream) {
    int first = stream.readInt(-1, n, "first token");
    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true};
    }

    int n1 = first;
    int n2 = stream.readInt(1, n, "N2");
    if (n1 <= 0) {
        stream.quitf(_wa, "N1 must be positive, found %d", n1);
    }
    if (n1 == n2) {
        stream.quitf(_wa, "tree sizes must be different, found %d and %d", n1, n2);
    }
    if (n1 + n2 != n) {
        stream.quitf(_wa, "tree sizes sum to %d instead of %d", n1 + n2, n);
    }

    vector<int> owner(n + 1, 0);
    vector<int> vertices1(n1);
    vector<int> vertices2(n2);

    for (int i = 0; i < n1; ++i) {
        int vertex = stream.readInt(1, n, format("tree1 vertex[%d]", i + 1).c_str());
        if (owner[vertex] != 0) {
            stream.quitf(_wa, "vertex %d appears more than once", vertex);
        }
        owner[vertex] = 1;
        vertices1[i] = vertex;
    }

    vector<int> edgeOwner(m + 1, 0);
    vector<int> edgeIds1(n1 - 1);
    for (int i = 0; i < n1 - 1; ++i) {
        int edgeId = stream.readInt(1, m, format("tree1 edge[%d]", i + 1).c_str());
        if (edgeOwner[edgeId] != 0) {
            stream.quitf(_wa, "edge %d appears more than once", edgeId);
        }
        edgeOwner[edgeId] = 1;
        edgeIds1[i] = edgeId;
    }

    for (int i = 0; i < n2; ++i) {
        int vertex = stream.readInt(1, n, format("tree2 vertex[%d]", i + 1).c_str());
        if (owner[vertex] != 0) {
            stream.quitf(_wa, "vertex %d appears more than once", vertex);
        }
        owner[vertex] = 2;
        vertices2[i] = vertex;
    }

    vector<int> edgeIds2(n2 - 1);
    for (int i = 0; i < n2 - 1; ++i) {
        int edgeId = stream.readInt(1, m, format("tree2 edge[%d]", i + 1).c_str());
        if (edgeOwner[edgeId] != 0) {
            stream.quitf(_wa, "edge %d appears more than once", edgeId);
        }
        edgeOwner[edgeId] = 2;
        edgeIds2[i] = edgeId;
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after partition witness");
    }

    validateTree(stream, vertices1, edgeIds1, owner, 1);
    validateTree(stream, vertices2, edgeIds2, owner, 2);

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    edges.resize(m + 1);
    for (int i = 1; i <= m; ++i) {
        edges[i].u = inf.readInt();
        edges[i].v = inf.readInt();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible && participant.impossible) {
        quitf(_ok, "both outputs report impossible");
    }
    if (jury.impossible) {
        quitf(_fail, "participant found a valid partition while jury reports impossible");
    }
    if (participant.impossible) {
        quitf(_wa, "jury has a valid partition but participant reports impossible");
    }

    quitf(_ok, "valid partition");
}
