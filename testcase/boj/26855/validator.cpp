#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

struct Dsu {
    vector<int> parent;

    explicit Dsu(int n) : parent(n + 1) {
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

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readEoln();

    inf.readInts(n, 1, 1000000, "A_i");
    inf.readEoln();

    Dsu dsu(n);
    for (int i = 1; i <= n - 1; ++i) {
        int u = inf.readInt(1, n, "u_j");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_j");
        inf.readEoln();

        ensuref(u < v, "edge %d must satisfy u < v, got %d %d", i, u, v);
        ensuref(dsu.unite(u, v), "edge %d creates a cycle: %d %d", i, u, v);
    }

    int root = dsu.find(1);
    for (int node = 2; node <= n; ++node) {
        ensuref(dsu.find(node) == root, "tree is not connected; node %d is separate", node);
    }

    inf.readEof();
}
