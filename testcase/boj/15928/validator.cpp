#include "testlib.h"
#include <vector>
using namespace std;

struct DSU {
    vector<int> parent;
    vector<int> rank;
    int merges = 0;

    explicit DSU(int n) : parent(n + 1), rank(n + 1, 0) {
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
        }
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
            parent[rootA] = rootB;
        } else if (rank[rootA] > rank[rootB]) {
            parent[rootB] = rootA;
        } else {
            parent[rootB] = rootA;
            ++rank[rootA];
        }
        ++merges;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 250000, "N");
    inf.readSpace();
    int d = inf.readInt(0, 1000000, "D");
    inf.readEoln();

    DSU dsu(n);
    for (int i = 1; i <= n - 1; ++i) {
        int s = inf.readInt(1, n, "S_i");
        inf.readSpace();
        int e = inf.readInt(1, n, "E_i");
        inf.readSpace();
        int c = inf.readInt(-100000000, 100000000, "C_i");
        inf.readSpace();
        int a = inf.readInt(-1000, 1000, "A_i");
        inf.readEoln();

        (void)c;
        (void)a;
        ensuref(dsu.unite(s, e), "edge %d creates a cycle or duplicate: %d %d", i, s, e);
    }

    ensuref(dsu.merges == n - 1, "edges must form a connected tree");
    (void)d;

    inf.readEof();
    return 0;
}
