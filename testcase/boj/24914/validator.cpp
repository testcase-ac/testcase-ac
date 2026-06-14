#include "testlib.h"

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

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return false;
        }
        if (size_[a] < size_[b]) {
            swap(a, b);
        }
        parent_[b] = a;
        size_[a] += size_[b];
        return true;
    }

private:
    vector<int> parent_;
    vector<int> size_;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200000, "N");
    inf.readSpace();
    int m = inf.readInt(2, 200000, "M");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    Dsu dsu(n);
    set<pair<int, int>> edges;
    for (int i = 1; i <= n - 1; ++i) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readSpace();
        inf.readInt(1, m, "w_i");
        inf.readEoln();

        ensuref(u < v, "edge %d does not satisfy u_i < v_i: %d %d", i, u, v);
        ensuref(edges.insert({u, v}).second, "duplicate edge at index %d: %d %d", i, u, v);
        ensuref(dsu.unite(u, v), "edge %d creates a cycle: %d %d", i, u, v);
    }

    int root = dsu.find(1);
    for (int vertex = 2; vertex <= n; ++vertex) {
        ensuref(dsu.find(vertex) == root, "graph is disconnected at vertex %d", vertex);
    }

    for (int i = 1; i <= q; ++i) {
        inf.readInt(1, n - 1, "p_i");
        inf.readSpace();
        inf.readInt(1, m, "t_i");
        inf.readEoln();
    }

    inf.readEof();
}
