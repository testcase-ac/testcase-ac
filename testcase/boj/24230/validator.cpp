#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

class DSU {
public:
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

private:
    vector<int> parent;
    vector<int> size;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readEoln();

    vector<int> color = inf.readInts(n, 0, n, "C_i");
    inf.readEoln();
    color.insert(color.begin(), 0);

    DSU dsu(n);
    vector<vector<int>> graph(n + 1);
    for (int i = 1; i <= n - 1; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readEoln();

        ensuref(a != b, "edge %d is a self-loop at vertex %d", i, a);
        ensuref(dsu.unite(a, b), "edge %d creates a cycle or duplicate connection: %d %d", i, a, b);

        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector<int> parent(n + 1, 0);
    vector<int> order;
    order.reserve(n);
    order.push_back(1);
    parent[1] = -1;
    for (int i = 0; i < static_cast<int>(order.size()); ++i) {
        int node = order[i];
        for (int next : graph[node]) {
            if (next == parent[node]) {
                continue;
            }
            ensuref(parent[next] == 0, "tree traversal reached vertex %d more than once", next);
            parent[next] = node;
            order.push_back(next);
        }
    }
    ensuref(static_cast<int>(order.size()) == n, "the graph is not connected from root 1");

    for (int node = 2; node <= n; ++node) {
        ensuref(color[parent[node]] == 0 || color[node] != 0,
                "vertex %d is white under non-white parent %d", node, parent[node]);
    }

    inf.readEof();
}
