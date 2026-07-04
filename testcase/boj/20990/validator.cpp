#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

struct Dsu {
    vector<int> parent;
    vector<int> size;

    explicit Dsu(int n) : parent(n), size(n, 1) {
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

    int n = inf.readInt(2, 500000, "N");
    inf.readEoln();

    Dsu dsu(n);
    int components = n;
    for (int i = 1; i <= n - 1; ++i) {
        int u = inf.readInt(0, n - 1, "u");
        inf.readSpace();
        int v = inf.readInt(0, n - 1, "v");
        inf.readSpace();
        inf.readLong(0LL, 1000000000LL, "p");
        inf.readEoln();

        ensuref(u != v, "loop at edge %d: %d", i, u);
        ensuref(dsu.unite(u, v), "cycle or duplicate edge at edge %d: %d %d", i, u, v);
        --components;
    }

    ensuref(components == 1, "the provided streets must form a connected tree");
    inf.readEof();
}
