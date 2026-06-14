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

    int n = inf.readInt(2, 100000, "N");
    inf.readEoln();

    Dsu dsu(n);
    for (int i = 0; i < n - 1; ++i) {
        int p = inf.readInt(0, n - 1, "p");
        inf.readSpace();
        int q = inf.readInt(0, n - 1, "q");
        inf.readSpace();
        inf.readInt(1, 10000, "w");
        inf.readEoln();

        ensuref(p != q, "self-loop at edge %d: %d", i + 1, p);
        ensuref(dsu.unite(p, q), "cycle or duplicate edge at edge %d: %d %d", i + 1, p, q);
    }

    int root = dsu.find(0);
    for (int v = 1; v < n; ++v) {
        ensuref(dsu.find(v) == root, "node %d is not connected to node 0", v);
    }

    inf.readEof();
}
