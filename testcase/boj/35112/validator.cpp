#include "testlib.h"

#include <algorithm>
#include <cstdint>
#include <numeric>
#include <unordered_set>
#include <vector>

using namespace std;

struct DisjointSet {
    vector<int> parent;
    vector<int> size;

    explicit DisjointSet(int n) : parent(n + 1), size(n + 1, 1) {
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

    int n = inf.readInt(3, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(n - 1, 1000000, "M");
    inf.readEoln();

    DisjointSet dsu(n);
    unordered_set<uint64_t> edges;
    edges.reserve(static_cast<size_t>(m) * 2);

    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();

        ensuref(u != v, "loop at edge %d: (%d, %d)", i, u, v);
        int a = min(u, v);
        int b = max(u, v);
        uint64_t key = (static_cast<uint64_t>(a) << 32) | static_cast<uint32_t>(b);
        ensuref(edges.insert(key).second, "duplicate edge at edge %d: (%d, %d)", i, u, v);
        dsu.unite(u, v);
    }

    int root = dsu.find(1);
    for (int vertex = 2; vertex <= n; ++vertex) {
        ensuref(dsu.find(vertex) == root, "graph is not connected; vertex %d is disconnected", vertex);
    }

    inf.readEof();
}
