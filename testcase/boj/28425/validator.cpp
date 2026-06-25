#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct DSU {
    vector<int> parent;
    vector<int> size;
    int components;

    explicit DSU(int n) : parent(n + 1), size(n + 1, 1), components(n) {
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
        --components;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_N = 100000;
    const int MAX_Q = 100000;
    const int MAX_SCORE = 10000;

    int n = inf.readInt(1, MAX_N, "N");
    inf.readSpace();
    int q = inf.readInt(1, MAX_Q, "Q");
    inf.readEoln();

    inf.readInts(n, 0, MAX_SCORE, "score_i");
    inf.readEoln();

    DSU dsu(n);
    for (int i = 1; i <= n - 1; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();

        ensuref(u != v, "edge %d is a self-loop at node %d", i, u);
        ensuref(dsu.unite(u, v), "edge %d creates a cycle or duplicate edge: %d %d", i, u, v);
    }
    ensuref(dsu.components == 1, "the given graph is not connected");

    for (int i = 1; i <= q; ++i) {
        int r = inf.readInt(1, n, "r");
        inf.readSpace();
        inf.readInt(1, n, "v");
        inf.readEoln();
    }

    inf.readEof();
}
