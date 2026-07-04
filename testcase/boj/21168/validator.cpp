#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

struct Dsu {
    vector<int> parent;
    vector<int> size;

    explicit Dsu(int n) : parent(n + 1), size(n + 1, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
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

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    long long k = inf.readLong(1LL, 1000000000LL, "k");
    inf.readEoln();

    Dsu dsu(n);
    for (int i = 1; i <= n - 1; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readSpace();
        long long c = inf.readLong(1LL, 1000000000LL, "c");
        inf.readEoln();

        ensuref(u != v, "edge %d is a self-loop at vertex %d", i, u);
        ensuref(dsu.unite(u, v), "edge %d creates a cycle or duplicate edge: %d %d", i, u, v);
        (void)c;
    }

    (void)k;
    inf.readEof();
}
