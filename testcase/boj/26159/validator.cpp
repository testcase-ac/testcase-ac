#include "testlib.h"
#include <numeric>
#include <vector>
using namespace std;

struct DSU {
    vector<int> parent;
    vector<int> rank;
    int merges = 0;

    explicit DSU(int n) : parent(n + 1), rank(n + 1, 0) {
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
        ++merges;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readEoln();

    DSU dsu(n);
    for (int i = 1; i <= n - 1; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();

        ensuref(u != v, "edge %d has a self-loop at vertex %d", i, u);
        ensuref(dsu.unite(u, v), "edge %d creates a cycle or duplicate edge: %d %d", i, u, v);
    }
    ensuref(dsu.merges == n - 1, "edges do not form a tree");

    inf.readLongs(n - 1, 1LL, 1000000000LL, "a_i");
    inf.readEoln();
    inf.readEof();
}
