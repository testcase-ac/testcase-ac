#include "testlib.h"
#include <numeric>
#include <set>
#include <utility>
#include <vector>
using namespace std;

class Dsu {
public:
    explicit Dsu(int n) : parent_(n), size_(n, 1) {
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

    int n = inf.readInt(2, 100000, "N");
    inf.readEoln();

    Dsu dsu(n);
    set<pair<int, int>> edges;
    for (int i = 1; i <= n - 1; ++i) {
        int a = inf.readInt(0, n - 1, "a");
        inf.readSpace();
        int b = inf.readInt(0, n - 1, "b");
        inf.readEoln();

        ensuref(a != b, "self-loop at edge %d: (%d, %d)", i, a, b);

        pair<int, int> edge = minmax(a, b);
        ensuref(edges.insert(edge).second,
                "duplicate edge at edge %d: (%d, %d)", i, a, b);
        ensuref(dsu.unite(a, b),
                "cycle formed at edge %d: (%d, %d)", i, a, b);
    }

    int root = dsu.find(0);
    for (int vertex = 1; vertex < n; ++vertex) {
        ensuref(dsu.find(vertex) == root, "vertex %d is not connected to vertex 0", vertex);
    }

    inf.readEof();
}
