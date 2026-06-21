#include "testlib.h"
#include <numeric>
#include <vector>

using namespace std;

class DisjointSet {
public:
    explicit DisjointSet(int n) : parent(n + 1), size(n + 1, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (size[a] < size[b]) swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        return true;
    }

private:
    vector<int> parent;
    vector<int> size;
};

static string readProbability(const char* name) {
    return inf.readToken("0\\.[0-9][0-9]|1\\.00", name);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_N = 500000;
    const int MAX_Q = 500000;

    int n = inf.readInt(2, MAX_N, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        readProbability("p_i");
        if (i < n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    DisjointSet dsu(n);
    for (int i = 1; i <= n - 1; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();

        ensuref(u != v, "edge %d has a self-loop at vertex %d", i, u);
        ensuref(dsu.unite(u, v), "edge %d creates a cycle or duplicate edge: %d %d", i, u, v);
    }

    int root = dsu.find(1);
    for (int i = 2; i <= n; ++i) {
        ensuref(dsu.find(i) == root, "tree is disconnected; vertex %d is not connected to vertex 1", i);
    }

    int q = inf.readInt(1, MAX_Q, "Q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        inf.readInt(1, n, "u");
        inf.readSpace();
        readProbability("p");
        inf.readEoln();
    }

    inf.readEof();
}
