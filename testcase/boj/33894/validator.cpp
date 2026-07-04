#include "testlib.h"

#include <numeric>
#include <vector>
using namespace std;

struct Dsu {
    vector<int> parent;
    vector<int> rank;

    explicit Dsu(int n) : parent(n + 1), rank(n + 1, 0) {
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
        if (rank[a] < rank[b]) {
            swap(a, b);
        }
        parent[b] = a;
        if (rank[a] == rank[b]) {
            ++rank[a];
        }
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200000, "N");
    inf.readSpace();
    int k = inf.readInt(1, n - 1, "K");
    inf.readEoln();

    Dsu dsu(n);
    for (int i = 1; i <= n - 1; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readSpace();
        int w = inf.readInt(2, 1000000000, "w_i");
        inf.readEoln();

        ensuref(a != b, "edge %d is a loop at vertex %d", i, a);
        ensuref(w % 2 == 0, "edge %d has odd weight %d", i, w);
        ensuref(dsu.unite(a, b), "edge %d creates a cycle between %d and %d", i, a, b);
    }

    int root = dsu.find(1);
    for (int v = 2; v <= n; ++v) {
        ensuref(dsu.find(v) == root, "vertex %d is not connected to vertex 1", v);
    }

    vector<bool> used(n + 1, false);
    for (int j = 1; j <= k; ++j) {
        int p = inf.readInt(2, n, "p_j");
        ensuref(!used[p], "defender position %d is repeated", p);
        used[p] = true;
        if (j < k) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    inf.readEof();
}
