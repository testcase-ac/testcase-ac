#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Dsu {
    vector<int> parent, size;

    explicit Dsu(int n) : parent(n + 1), size(n + 1, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        while (parent[x] != x) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
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

    int n = inf.readInt(2, 200000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 200000, "Q");
    inf.readEoln();

    Dsu dsu(n);
    for (int i = 1; i <= n - 1; ++i) {
        int u = inf.readInt(1, n, "U_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "V_i");
        inf.readSpace();
        int w = inf.readInt(1, 1000000000, "W_i");
        inf.readEoln();

        ensuref(u != v, "road %d is a loop at vertex %d", i, u);
        ensuref(dsu.unite(u, v), "road %d creates a cycle or duplicate edge: %d %d", i, u, v);
        (void)w;
    }

    int root = dsu.find(1);
    for (int i = 2; i <= n; ++i) {
        ensuref(dsu.find(i) == root, "transport network is disconnected at vertex %d", i);
    }

    vector<char> isAdd(q + 1, false), active(q + 1, false);
    for (int j = 1; j <= q; ++j) {
        int type = inf.readInt(1, 2, "scenario_type");
        inf.readSpace();
        if (type == 1) {
            int a = inf.readInt(1, n, "A_j");
            inf.readSpace();
            long long b = inf.readLong(1LL, 1000000000000000LL, "B_j");
            inf.readEoln();

            isAdd[j] = true;
            active[j] = true;
            (void)a;
            (void)b;
        } else {
            int c = inf.readInt(1, j - 1, "C_j");
            inf.readEoln();

            ensuref(isAdd[c], "scenario %d removes scenario %d, which is not an add scenario", j, c);
            ensuref(active[c], "scenario %d removes scenario %d, which was already removed", j, c);
            active[c] = false;
        }
    }

    inf.readEof();
    return 0;
}
