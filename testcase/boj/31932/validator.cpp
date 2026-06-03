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

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            parent[b] = a;
        }
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "M");
    inf.readEoln();

    Dsu dsu(n);
    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readSpace();
        long long d = inf.readLong(1LL, 1000000000LL, "d");
        inf.readSpace();
        long long t = inf.readLong(1LL, 1000000000LL, "t");
        inf.readEoln();

        ensuref(u != v, "edge %d is a self-loop: %d", i, u);
        dsu.unite(u, v);
        (void)d;
        (void)t;
    }

    int root = dsu.find(1);
    for (int i = 2; i <= n; ++i) {
        ensuref(dsu.find(i) == root, "graph is disconnected: vertex %d is not reachable from 1", i);
    }

    inf.readEof();
}
