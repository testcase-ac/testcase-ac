#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

class DisjointSet {
public:
    explicit DisjointSet(int n) : parent_(n + 1), rank_(n + 1, 0) {
        iota(parent_.begin(), parent_.end(), 0);
    }

    int find(int x) {
        if (parent_[x] == x) {
            return x;
        }
        return parent_[x] = find(parent_[x]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return;
        }
        if (rank_[a] < rank_[b]) {
            swap(a, b);
        }
        parent_[b] = a;
        if (rank_[a] == rank_[b]) {
            ++rank_[a];
        }
    }

private:
    vector<int> parent_;
    vector<int> rank_;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int vertexCount = inf.readInt(1, 1000, "vertex_count");
    inf.readSpace();
    int edgeCount = inf.readInt(0, 1000, "edge_count");
    inf.readEoln();

    // CHECK: A connected graph with one vertex and no edges is accepted; the
    // statement does not give positive lower bounds for either count.
    ensuref(edgeCount <= vertexCount * (vertexCount - 1) / 2,
            "too many edges for a simple graph: vertex_count=%d edge_count=%d",
            vertexCount,
            edgeCount);
    if (vertexCount > 1) {
        ensuref(edgeCount >= vertexCount - 1,
                "connected graph with %d vertices needs at least %d edges, got %d",
                vertexCount,
                vertexCount - 1,
                edgeCount);
    }

    DisjointSet dsu(vertexCount);
    set<pair<int, int>> edges;
    for (int i = 0; i < edgeCount; ++i) {
        int a = inf.readInt(1, vertexCount, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, vertexCount, "b_i");
        inf.readEoln();

        ensuref(a != b, "loop at edge index %d: (%d, %d)", i + 1, a, b);
        auto edge = minmax(a, b);
        ensuref(edges.insert(edge).second,
                "multiple edge at edge index %d: (%d, %d)",
                i + 1,
                a,
                b);
        dsu.unite(a, b);
    }

    int root = dsu.find(1);
    for (int v = 2; v <= vertexCount; ++v) {
        ensuref(dsu.find(v) == root, "graph is not connected; vertex %d is separate", v);
    }

    inf.readEof();
}
