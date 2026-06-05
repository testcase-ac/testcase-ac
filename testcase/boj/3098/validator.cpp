#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Dsu {
    vector<int> parent;

    explicit Dsu(int n) : parent(n + 1) {
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
        }
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

    int n = inf.readInt(1, 50, "n");
    inf.readSpace();
    int maxM = n * (n - 1) / 2;
    int m = inf.readInt(0, maxM, "m");
    inf.readEoln();

    // CHECK: The statement says 1 <= M <= N*(N-1)/2, which makes N=1 impossible.
    ensuref(m >= 1, "m must be at least 1");

    Dsu dsu(n);
    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readEoln();

        ensuref(a < b, "edge %d must satisfy a < b, got %d %d", i, a, b);
        ensuref(edges.insert({a, b}).second, "duplicate edge at index %d: %d %d", i, a, b);
        dsu.unite(a, b);
    }

    int root = dsu.find(1);
    for (int v = 2; v <= n; ++v) {
        ensuref(dsu.find(v) == root, "initial friendship graph must be connected");
    }

    inf.readEof();
}
