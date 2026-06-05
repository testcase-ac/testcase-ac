#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

class Dsu {
public:
    explicit Dsu(int n) : parent_(n + 1), size_(n + 1, 1) {
        iota(parent_.begin(), parent_.end(), 0);
    }

    int find(int x) {
        if (parent_[x] == x) {
            return x;
        }
        return parent_[x] = find(parent_[x]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return;
        }
        if (size_[a] < size_[b]) {
            swap(a, b);
        }
        parent_[b] = a;
        size_[a] += size_[b];
    }

private:
    vector<int> parent_;
    vector<int> size_;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 200000, "M");
    inf.readSpace();
    int c = inf.readInt(1, 100000, "C");
    inf.readEoln();
    (void)c;

    ensuref(m >= n - 1, "connected graph with N=%d must have at least N-1 edges, found M=%d", n, m);

    Dsu dsu(n);
    set<pair<int, int>> edges;

    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "A_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "B_i");
        inf.readSpace();
        int d = inf.readInt(1, 100000, "D_i");
        inf.readEoln();

        ensuref(a != b, "self-loop at edge %d: %d %d", i, a, b);

        pair<int, int> edge = minmax(a, b);
        ensuref(edges.insert(edge).second, "duplicate undirected edge at edge %d: %d %d", i, a, b);

        dsu.unite(a, b);
        (void)d;
    }

    int root = dsu.find(1);
    for (int v = 2; v <= n; ++v) {
        ensuref(dsu.find(v) == root, "graph is disconnected: vertex %d is not reachable from vertex 1", v);
    }

    inf.readEof();
}
