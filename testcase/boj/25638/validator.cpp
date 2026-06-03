#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

class DisjointSet {
public:
    explicit DisjointSet(int n) : parent(n + 1), size(n + 1, 1) {
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

private:
    vector<int> parent;
    vector<int> size;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    inf.readInts(n, 0, 1, "a_i");
    inf.readEoln();

    DisjointSet dsu(n);
    set<pair<int, int>> edges;
    for (int i = 1; i <= n - 1; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();

        ensuref(u != v, "edge %d has a loop at vertex %d", i, u);
        pair<int, int> edge = minmax(u, v);
        ensuref(edges.insert(edge).second, "duplicate edge %d: %d %d", i, u, v);
        ensuref(dsu.unite(u, v), "edge %d creates a cycle: %d %d", i, u, v);
    }

    int root = dsu.find(1);
    for (int vertex = 2; vertex <= n; ++vertex) {
        ensuref(dsu.find(vertex) == root, "tree is disconnected at vertex %d", vertex);
    }

    int q = inf.readInt(1, n, "Q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        inf.readInt(1, n, "query_u");
        inf.readEoln();
    }

    inf.readEof();
}
