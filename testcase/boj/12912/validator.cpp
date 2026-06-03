#include "testlib.h"

#include <vector>

using namespace std;

struct Dsu {
    vector<int> parent;

    explicit Dsu(int n) : parent(n) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return false;
        }
        parent[b] = a;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 2000, "N");
    inf.readEoln();

    Dsu dsu(n);
    for (int i = 0; i < n - 1; ++i) {
        int from = inf.readInt(0, n - 1, "from");
        inf.readSpace();
        int to = inf.readInt(0, n - 1, "to");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "cost");
        inf.readEoln();

        ensuref(from != to, "edge %d is a self-loop at vertex %d", i + 1, from);
        ensuref(dsu.unite(from, to), "edge %d creates a cycle between %d and %d", i + 1, from, to);
    }

    inf.readEof();
}
