#include "testlib.h"

#include <numeric>
#include <set>
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

    int t = inf.readInt(1, 50000, "t");
    inf.readEoln();

    int total_n = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 100000, "n");
        inf.readEoln();
        total_n += n;
        ensuref(total_n <= 100000, "sum of n exceeds 100000");

        Dsu dsu(n);
        set<pair<int, int>> edges;
        for (int i = 1; i <= n - 1; ++i) {
            int a = inf.readInt(1, n, "a");
            inf.readSpace();
            int b = inf.readInt(1, n, "b");
            inf.readEoln();

            ensuref(a < b, "edge %d must satisfy a < b, got %d %d", i, a, b);
            ensuref(edges.insert({a, b}).second,
                    "duplicate edge %d: %d %d", i, a, b);
            ensuref(dsu.Unite(a, b), "edge %d creates a cycle: %d %d", i, a, b);
        }

        int root = dsu.Find(1);
        for (int v = 2; v <= n; ++v) {
            ensuref(dsu.Find(v) == root, "tree is disconnected at vertex %d", v);
        }

        vector<bool> seen(n + 1, false);
        for (int i = 1; i <= n; ++i) {
            int p = inf.readInt(1, n, "p");
            inf.readEoln();
            ensuref(!seen[p], "permutation value %d appears more than once", p);
            seen[p] = true;
        }
    }

    inf.readEof();
}
