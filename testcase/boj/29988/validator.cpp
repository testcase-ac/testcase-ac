#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

struct DSU {
    vector<int> parent;
    vector<int> rank;

    explicit DSU(int n) : parent(n + 1), rank(n + 1, 0) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
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

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    DSU dsu(n);
    int merges = 0;
    for (int i = 2; i <= n; ++i) {
        if (i > 2) {
            inf.readSpace();
        }
        int p = inf.readInt(1, n, "p_i");
        ensuref(p != i, "path %d is a self-loop: %d %d", i - 1, i, p);
        ensuref(dsu.unite(i, p), "path %d creates a cycle or duplicate edge: %d %d", i - 1, i, p);
        ++merges;
    }
    inf.readEoln();
    ensuref(merges == n - 1, "paths must form a tree with N - 1 successful connections");

    inf.readLongs(n, 1LL, 1000000000LL, "v_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
