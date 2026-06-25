#include "testlib.h"

#include <map>
#include <numeric>
#include <vector>

using namespace std;

struct Dsu {
    vector<int> parent;

    explicit Dsu(int n) : parent(n + 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) parent[b] = a;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 40000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "M");
    inf.readEoln();

    Dsu dsu(n);
    map<int, int> weightCount;
    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readSpace();
        int length = inf.readInt(1, 1000000, "n_i");
        inf.readEoln();

        dsu.unite(a, b);
        int count = ++weightCount[length];
        ensuref(count <= 3, "edge length %d occurs %d times", length, count);
    }

    int root = dsu.find(1);
    for (int v = 2; v <= n; ++v) {
        // CHECK: the statement asks for a spanning tree obtained from the farm graph, so require connectivity.
        ensuref(dsu.find(v) == root, "graph is disconnected at vertex %d", v);
    }

    inf.readEof();
}
