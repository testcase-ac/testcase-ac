#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent;

    explicit DSU(int n) : parent(n + 1) {
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

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int maxM = n * (n - 1) / 2;
    int m = inf.readInt(1, maxM, "M");
    inf.readEoln();

    DSU dsu(n);
    set<pair<int, int>> edges;

    int entranceA = inf.readInt(0, n, "A_0");
    inf.readSpace();
    int entranceB = inf.readInt(0, n, "B_0");
    inf.readSpace();
    inf.readInt(0, 1, "C_0");
    inf.readEoln();

    ensuref(min(entranceA, entranceB) == 0 && max(entranceA, entranceB) == 1,
            "the entrance road must connect 0 and 1, got %d %d", entranceA, entranceB);
    edges.insert({0, 1});
    dsu.unite(entranceA, entranceB);

    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "A_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "B_i");
        inf.readSpace();
        inf.readInt(0, 1, "C_i");
        inf.readEoln();

        ensuref(a != b, "self-loop at road %d: %d %d", i, a, b);
        auto edge = minmax(a, b);
        ensuref(edges.insert(edge).second, "duplicate road at index %d: %d %d", i, a, b);
        dsu.unite(a, b);
    }

    for (int vertex = 1; vertex <= n; ++vertex) {
        ensuref(dsu.find(0) == dsu.find(vertex), "building %d is unreachable from entrance", vertex);
    }

    inf.readEof();
}
