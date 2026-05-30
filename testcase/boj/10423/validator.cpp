#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent;

    explicit DSU(int n) : parent(n + 1) {
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

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "M");
    inf.readSpace();
    int k = inf.readInt(1, n, "K");
    inf.readEoln();

    vector<bool> hasPlant(n + 1, false);
    for (int i = 0; i < k; ++i) {
        int city = inf.readInt(1, n, "plant_city");
        ensuref(!hasPlant[city], "duplicate plant city: %d", city);
        hasPlant[city] = true;
        if (i + 1 < k) {
            inf.readSpace();
        }
    }
    inf.readEoln();

    DSU dsu(n);
    for (int i = 0; i < m; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readSpace();
        inf.readInt(1, 10000, "w");
        inf.readEoln();

        ensuref(u != v, "self-loop at edge %d: %d %d", i + 1, u, v);
        dsu.unite(u, v);
    }

    vector<bool> componentHasPlant(n + 1, false);
    for (int city = 1; city <= n; ++city) {
        if (hasPlant[city]) {
            componentHasPlant[dsu.find(city)] = true;
        }
    }
    for (int city = 1; city <= n; ++city) {
        ensuref(componentHasPlant[dsu.find(city)],
                "city %d is not connected to any power plant", city);
    }

    inf.readEof();
}
