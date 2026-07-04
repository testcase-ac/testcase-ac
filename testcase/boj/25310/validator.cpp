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

    int Find(int x) {
        if (parent_[x] == x) {
            return x;
        }
        return parent_[x] = Find(parent_[x]);
    }

    bool Unite(int a, int b) {
        a = Find(a);
        b = Find(b);
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

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    Dsu dsu(n);
    set<pair<int, int>> edges;
    for (int i = 1; i <= n - 1; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();

        ensuref(u != v, "self-loop at edge %d: %d", i, u);
        pair<int, int> edge = minmax(u, v);
        ensuref(edges.insert(edge).second, "duplicate edge at edge %d: %d %d", i, u, v);
        ensuref(dsu.Unite(u, v), "cycle introduced by edge %d: %d %d", i, u, v);
    }

    int root = dsu.Find(1);
    for (int city = 2; city <= n; ++city) {
        ensuref(dsu.Find(city) == root, "city %d is not connected to city 1", city);
    }

    for (int i = 1; i <= q; ++i) {
        inf.readInt(1, n, "A");
        inf.readSpace();
        inf.readInt(1, n, "B");
        inf.readSpace();
        inf.readInt(1, n, "C");
        inf.readEoln();
    }

    inf.readEof();
}
