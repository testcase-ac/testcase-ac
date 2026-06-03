#include "testlib.h"
#include <bits/stdc++.h>
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

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        parent[b] = a;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readEoln();

    Dsu dsu(n);
    set<pair<int, int>> edges;
    for (int i = 1; i <= n - 1; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readEoln();

        ensuref(a != b, "edge %d is a self-loop: %d %d", i, a, b);
        auto edge = minmax(a, b);
        ensuref(edges.insert(edge).second, "duplicate edge %d: %d %d", i, a, b);
        ensuref(dsu.unite(a, b), "edge %d creates a cycle: %d %d", i, a, b);
    }
    ensuref((int)edges.size() == n - 1, "expected exactly n - 1 tree edges");

    int root = dsu.find(1);
    for (int v = 2; v <= n; ++v) {
        ensuref(dsu.find(v) == root, "vertex %d is disconnected from vertex 1", v);
    }

    int q = inf.readInt(1, 100000, "q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        int t = inf.readInt(1, 2, "t");
        inf.readSpace();
        int k;
        if (t == 1) {
            k = inf.readInt(1, n, "k");
        } else {
            k = inf.readInt(1, n - 1, "k");
        }
        inf.readEoln();
        (void)k;
    }

    inf.readEof();
}
