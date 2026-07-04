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

    int n = inf.readInt(2, 10000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "m");
    inf.readEoln();

    Dsu dsu(n);
    for (int i = 0; i < m; ++i) {
        int a = inf.readInt(0, n - 1, "a_i");
        inf.readSpace();
        int b = inf.readInt(0, n - 1, "b_i");
        inf.readEoln();

        ensuref(a != b, "fiber link %d connects node %d to itself", i + 1, a);
        dsu.unite(a, b);
    }

    int root = dsu.find(0);
    for (int node = 1; node < n; ++node) {
        ensuref(dsu.find(node) == root,
                "node %d is not connected to node 0 in the existing network",
                node);
    }

    inf.readEof();
}
