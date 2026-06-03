#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Dsu {
    vector<int> parent;
    vector<int> size;

    explicit Dsu(int n) : parent(n + 1), size(n + 1, 1) {
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
        if (size[a] < size[b]) {
            swap(a, b);
        }
        parent[b] = a;
        size[a] += size[b];
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 300000, "N");
    inf.readEoln();

    Dsu dsu(n);
    set<pair<int, int>> edges;
    for (int i = 0; i < n - 2; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readEoln();

        ensuref(a != b, "loop at edge index %d: (%d, %d)", i + 1, a, b);

        auto edge = minmax(a, b);
        ensuref(edges.insert(edge).second,
                "multiple edge at edge index %d: (%d, %d)", i + 1, a, b);

        ensuref(dsu.unite(a, b),
                "cycle introduced at edge index %d: (%d, %d)", i + 1, a, b);
    }

    int components = 0;
    for (int island = 1; island <= n; ++island) {
        if (dsu.find(island) == island) {
            ++components;
        }
    }
    ensuref(components == 2, "expected exactly 2 connected components, found %d",
            components);

    inf.readEof();
}
