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

    const int maxHeader = (1 << 20) - 1;

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int x = inf.readInt(0, maxHeader, "X");
    inf.readEoln();

    DSU dsu(n);
    for (int i = 1; i <= n - 1; ++i) {
        int a = inf.readInt(1, n, "A");
        inf.readSpace();
        int b = inf.readInt(1, n, "B");
        inf.readSpace();
        int c = inf.readInt(0, maxHeader, "C");
        inf.readEoln();

        ensuref(dsu.unite(a, b),
                "edge %d creates a cycle or duplicate connection: %d %d", i, a, b);
    }

    ensuref(dsu.merges == n - 1, "edges do not form a connected tree");

    inf.readEof();
    return 0;
}
