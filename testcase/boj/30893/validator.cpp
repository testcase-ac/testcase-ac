#include "testlib.h"

#include <numeric>
#include <utility>
#include <vector>

using namespace std;

class DisjointSet {
public:
    explicit DisjointSet(int n) : parent(n + 1), rank(n + 1, 0) {
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

private:
    vector<int> parent;
    vector<int> rank;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    int s = inf.readInt(1, n, "s");
    inf.readSpace();
    int e = inf.readInt(1, n, "e");
    inf.readEoln();
    ensuref(s != e, "s and e must be distinct: %d", s);

    DisjointSet dsu(n);
    for (int i = 1; i <= n - 1; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();

        ensuref(u != v, "self-loop at edge %d: %d", i, u);
        ensuref(dsu.unite(u, v), "cycle or duplicate edge at edge %d: (%d, %d)", i, u, v);
    }

    int root = dsu.find(1);
    for (int v = 2; v <= n; ++v) {
        ensuref(dsu.find(v) == root, "tree is disconnected: vertex %d is not connected to 1", v);
    }

    inf.readEof();
}
