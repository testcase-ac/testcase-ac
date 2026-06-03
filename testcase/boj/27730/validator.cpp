#include "testlib.h"

#include <numeric>
#include <set>
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

void readTree(int n, const char* name) {
    DisjointSet dsu(n);
    set<pair<int, int>> edges;

    for (int i = 1; i <= n - 1; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readSpace();
        inf.readInt(1, 10000, "c");
        inf.readEoln();

        ensuref(a != b, "%s edge %d is a self-loop: %d", name, i, a);
        pair<int, int> edge = minmax(a, b);
        ensuref(edges.insert(edge).second, "%s edge %d is duplicated: %d %d", name, i, a, b);
        ensuref(dsu.unite(a, b), "%s edge %d creates a cycle: %d %d", name, i, a, b);
    }

    int root = dsu.find(1);
    for (int v = 2; v <= n; ++v) {
        ensuref(dsu.find(v) == root, "%s is not connected", name);
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();
    readTree(n, "E");

    int m = inf.readInt(1, 100000, "m");
    inf.readEoln();
    readTree(m, "W");

    inf.readEof();
}
