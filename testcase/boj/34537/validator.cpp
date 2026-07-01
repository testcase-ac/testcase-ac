#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

struct Dsu {
    vector<int> parent;
    vector<int> size;

    explicit Dsu(int n) : parent(n + 1), size(n + 1, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int v) {
        if (parent[v] == v) {
            return v;
        }
        return parent[v] = find(parent[v]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return;
        }
        if (size[a] < size[b]) {
            swap(a, b);
        }
        parent[b] = a;
        size[a] += size[b];
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 50000, "N");
    inf.readSpace();
    int m = inf.readInt(n - 1, 100000, "M");
    inf.readSpace();
    int b = inf.readInt(1, 1000000, "B");
    inf.readEoln();

    Dsu dsu(n);
    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readSpace();
        int w = inf.readInt(1, 100000, "w_i");
        inf.readSpace();
        int x = inf.readInt(1, 100000, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, 10, "y_i");
        inf.readEoln();

        ensuref(u != v, "self-loop at bridge %d: %d %d", i, u, v);
        dsu.unite(u, v);
        (void)w;
        (void)x;
        (void)y;
    }

    int root = dsu.find(1);
    for (int i = 2; i <= n; ++i) {
        ensuref(dsu.find(i) == root, "graph is not connected: island %d is disconnected", i);
    }

    inf.readEof();
}
