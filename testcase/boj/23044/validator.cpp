#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

struct DSU {
    vector<int> parent;
    vector<int> size;

    explicit DSU(int n) : parent(n + 1), size(n + 1, 1) {
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

    int n = inf.readInt(2, 200000, "N");
    inf.readEoln();

    vector<int> c = inf.readInts(n, 0, 1, "C_i");
    inf.readEoln();

    int removed = 0;
    for (int value : c) {
        removed += value;
    }
    ensuref(removed > 0, "at least one vertex must be removed");
    ensuref(removed < n, "at least one vertex must remain");

    DSU dsu(n);
    for (int i = 1; i <= n - 1; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();

        ensuref(u != v, "loop at edge %d: (%d, %d)", i, u, v);
        ensuref(dsu.unite(u, v), "cycle or duplicate edge at edge %d: (%d, %d)", i, u, v);
    }

    int root = dsu.find(1);
    for (int i = 2; i <= n; ++i) {
        ensuref(dsu.find(i) == root, "tree is disconnected at vertex %d", i);
    }

    inf.readEof();
}
