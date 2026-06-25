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
        int ra = find(a);
        int rb = find(b);
        if (ra == rb) {
            return false;
        }
        if (rank[ra] < rank[rb]) {
            parent[ra] = rb;
        } else if (rank[ra] > rank[rb]) {
            parent[rb] = ra;
        } else {
            parent[rb] = ra;
            ++rank[ra];
        }
        ++merges;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_N = 100000;
    const int MAX_Q = 100000;
    const int MAX_RZ = 1000000000;
    const long long MAX_E = 1000000000000000000LL;

    int n = inf.readInt(2, MAX_N, "N");
    inf.readEoln();

    DSU dsu(n);
    for (int i = 1; i <= n - 1; ++i) {
        int x = inf.readInt(1, n, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, n, "y_i");
        inf.readSpace();
        inf.readInt(1, MAX_RZ, "r_i");
        inf.readSpace();
        inf.readInt(1, MAX_RZ, "z_i");
        inf.readEoln();

        ensuref(x != y, "edge %d is a self-loop at vertex %d", i, x);
        ensuref(dsu.unite(x, y),
                "edge %d creates a cycle or duplicates an existing connection: %d %d",
                i, x, y);
    }
    ensuref(dsu.merges == n - 1, "the %d edges do not form a connected tree", n - 1);

    int q = inf.readInt(1, MAX_Q, "Q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readSpace();
        inf.readLong(1LL, MAX_E, "e");
        inf.readEoln();

        ensuref(a != b, "query %d has equal endpoints: %d", i, a);
    }

    inf.readEof();
}
