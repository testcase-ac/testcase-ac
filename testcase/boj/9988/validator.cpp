#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Dsu {
    vector<int> parent;
    vector<int> rank;

    explicit Dsu(int n) : parent(n + 1), rank(n + 1, 0) {
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
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: the written lower bound says N >= 1, but M >= 1 plus non-loop
    // pathways between fields make N = 1 undefined for this graph format.
    int n = inf.readInt(2, 250, "N");
    inf.readSpace();
    int m = inf.readInt(1, 25000, "M");
    inf.readEoln();

    ensuref(m <= n * (n - 1) / 2,
            "M=%d exceeds the number of possible non-loop undirected edges for N=%d",
            m,
            n);

    Dsu dsu(n);
    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "A_j");
        inf.readSpace();
        int b = inf.readInt(1, n, "B_j");
        inf.readSpace();
        inf.readInt(1, 1000000, "L_j");
        inf.readEoln();

        ensuref(a != b, "pathway %d is a self-loop at field %d", i, a);
        pair<int, int> edge = minmax(a, b);
        ensuref(edges.insert(edge).second,
                "duplicate pathway at index %d between fields %d and %d",
                i,
                edge.first,
                edge.second);
        dsu.unite(a, b);
    }

    int root = dsu.find(1);
    for (int field = 2; field <= n; ++field) {
        ensuref(dsu.find(field) == root, "field %d is not connected to field 1", field);
    }

    inf.readEof();
}
