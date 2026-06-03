#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <set>
#include <vector>
using namespace std;

struct DisjointSet {
    vector<int> parent;
    vector<int> rank;

    explicit DisjointSet(int n) : parent(n + 1), rank(n + 1, 0) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b) {
        int rootA = find(a);
        int rootB = find(b);
        if (rootA == rootB) {
            return false;
        }
        if (rank[rootA] < rank[rootB]) {
            swap(rootA, rootB);
        }
        parent[rootB] = rootA;
        if (rank[rootA] == rank[rootB]) {
            ++rank[rootA];
        }
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "N");
    inf.readSpace();
    int k = inf.readInt(1, n, "K");
    inf.readEoln();

    DisjointSet dsu(n);
    set<pair<int, int>> edges;
    for (int i = 1; i <= n - 1; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readEoln();

        ensuref(a != b, "loop at edge %d: (%d, %d)", i, a, b);
        auto edge = minmax(a, b);
        ensuref(edges.insert(edge).second,
                "duplicate undirected edge at edge %d: (%d, %d)", i, a, b);
        dsu.unite(a, b);
    }

    int root = dsu.find(1);
    for (int node = 2; node <= n; ++node) {
        ensuref(dsu.find(node) == root, "node %d is not connected to root 1", node);
    }

    inf.readEof();
    return 0;
}
