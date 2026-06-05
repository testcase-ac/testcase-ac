#include "testlib.h"

#include <numeric>
#include <utility>
#include <vector>

using namespace std;

class Dsu {
public:
    explicit Dsu(int n) : parent(n + 1), size(n + 1, 1), components(n) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int v) {
        if (parent[v] == v) {
            return v;
        }
        return parent[v] = find(parent[v]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return false;
        }
        if (size[a] < size[b]) {
            swap(a, b);
        }
        parent[b] = a;
        size[a] += size[b];
        --components;
        return true;
    }

    int componentCount() const {
        return components;
    }

private:
    vector<int> parent;
    vector<int> size;
    int components;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 50000, "N");
    inf.readEoln();

    Dsu dsu(n);
    for (int i = 1; i <= n - 1; ++i) {
        int from = inf.readInt(1, n, "from");
        inf.readSpace();
        int to = inf.readInt(1, n, "to");
        inf.readSpace();
        inf.readInt(1, 40000, "length");
        inf.readEoln();

        ensuref(from != to, "edge %d has identical endpoints: %d", i, from);
        ensuref(dsu.unite(from, to), "edge %d creates a cycle between %d and %d", i, from, to);
    }

    ensuref(dsu.componentCount() == 1, "road network is disconnected: %d components", dsu.componentCount());
    inf.readEof();
}
