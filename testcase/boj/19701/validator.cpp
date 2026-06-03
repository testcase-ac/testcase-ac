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

    int v = inf.readInt(1, 100000, "V");
    inf.readSpace();
    int e = inf.readInt(1, 100000, "E");
    inf.readEoln();

    long long maxEdges = 1LL * v * (v - 1) / 2;
    ensuref(e <= maxEdges, "E=%d exceeds the number of simple undirected edges for V=%d", e, v);
    ensuref(e >= v - 1, "connected graph with V=%d needs at least V-1 edges, got E=%d", v, e);

    Dsu dsu(v);
    set<pair<int, int>> edges;

    for (int i = 1; i <= e; ++i) {
        int x = inf.readInt(1, v, "x");
        inf.readSpace();
        int y = inf.readInt(1, v, "y");
        inf.readSpace();
        int t = inf.readInt(1, 20000, "t");
        inf.readSpace();
        int k = inf.readInt(1, 1000000000, "k");
        inf.readEoln();

        ensuref(x != y, "edge %d is a self-loop at vertex %d", i, x);
        pair<int, int> edge = minmax(x, y);
        ensuref(edges.insert(edge).second, "edge %d duplicates edge (%d, %d)", i, edge.first, edge.second);
        dsu.unite(x, y);
    }

    int root = dsu.find(1);
    for (int city = 2; city <= v; ++city) {
        ensuref(dsu.find(city) == root, "city %d is not connected to city 1", city);
    }

    inf.readEof();
}
