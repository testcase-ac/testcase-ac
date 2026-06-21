#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

class Dsu {
public:
    explicit Dsu(int n) : parent(n + 1), rank(n + 1, 0) {
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
        if (rank[a] < rank[b]) {
            swap(a, b);
        }
        parent[b] = a;
        if (rank[a] == rank[b]) {
            ++rank[a];
        }
        return true;
    }

private:
    vector<int> parent;
    vector<int> rank;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 2000, "n");
    inf.readSpace();
    int m = inf.readInt(n - 1, 3000, "m");
    inf.readEoln();

    Dsu graph(n);
    Dsu initialTree(n);

    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readSpace();
        inf.readInt(1, 1000000000, "w");
        inf.readEoln();

        ensuref(u != v, "edge %d is a loop at vertex %d", i, u);
        graph.unite(u, v);

        if (i <= n - 1) {
            ensuref(initialTree.unite(u, v),
                    "the first n-1 edges are not a spanning tree; edge %d creates a cycle",
                    i);
        }
    }

    int graphRoot = graph.find(1);
    int treeRoot = initialTree.find(1);
    for (int vertex = 2; vertex <= n; ++vertex) {
        ensuref(graph.find(vertex) == graphRoot,
                "graph is not connected; vertex %d is disconnected from vertex 1",
                vertex);
        ensuref(initialTree.find(vertex) == treeRoot,
                "the first n-1 edges are not a spanning tree; vertex %d is disconnected from vertex 1",
                vertex);
    }

    inf.readEof();
}
