#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
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

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return;
        }
        if (rank[a] < rank[b]) {
            swap(a, b);
        }
        parent[b] = a;
        if (rank[a] == rank[b]) {
            ++rank[a];
        }
    }

private:
    vector<int> parent;
    vector<int> rank;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(n - 1, 500000, "M");
    inf.readEoln();

    long long maxSimpleEdges = 1LL * n * (n - 1) / 2;
    ensuref(m <= maxSimpleEdges, "M exceeds the number of possible simple edges: %d", m);

    DisjointSet dsu(n);
    set<pair<int, int>> edges;
    set<int> days;

    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readSpace();
        int t = inf.readInt(1, 1000000000, "t_i");
        inf.readEoln();

        ensuref(u != v, "self-loop at edge %d: %d %d", i, u, v);
        auto edge = minmax(u, v);
        ensuref(edges.insert(edge).second, "duplicate edge at edge %d: %d %d", i, u, v);
        ensuref(days.insert(t).second, "duplicate day at edge %d: %d", i, t);
        dsu.unite(u, v);
    }

    int root = dsu.find(1);
    for (int i = 2; i <= n; ++i) {
        ensuref(dsu.find(i) == root, "graph is disconnected; vertex %d is unreachable from 1", i);
    }

    inf.readEof();
}
