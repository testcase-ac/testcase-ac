#include "testlib.h"

#include <numeric>
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

    int n = inf.readInt(2, 200000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000000000, "m");
    inf.readSpace();
    int q = inf.readInt(1, 200000, "q");
    inf.readEoln();

    Dsu dsu(n);
    for (int i = 1; i <= n - 1; ++i) {
        int x = inf.readInt(1, n, "x");
        inf.readSpace();
        int y = inf.readInt(1, n, "y");
        inf.readEoln();

        ensuref(x != y, "edge %d is a self-loop: %d", i, x);
        ensuref(dsu.unite(x, y), "edge %d creates a cycle: %d %d", i, x, y);
    }
    for (int i = 2; i <= n; ++i) {
        ensuref(dsu.find(1) == dsu.find(i), "tree is disconnected at node %d", i);
    }

    for (int i = 1; i <= n; ++i) {
        inf.readInt(0, 9, "digit");
        inf.readEoln();
    }

    for (int i = 1; i <= q; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readEoln();
        (void)a;
        (void)b;
    }

    inf.readEof();
}
