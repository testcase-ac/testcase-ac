#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <vector>
using namespace std;

class Dsu {
public:
    explicit Dsu(int n) : parent(n + 1), size(n + 1, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int v) {
        if (parent[v] == v) return v;
        return parent[v] = find(parent[v]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (size[a] < size[b]) swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        return true;
    }

private:
    vector<int> parent;
    vector<int> size;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 50000, "n");
    inf.readEoln();

    Dsu dsu(n);
    set<pair<int, int>> edges;

    for (int i = 1; i <= n - 1; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readEoln();

        ensuref(a != b, "loop at edge index %d: (%d, %d)", i, a, b);
        auto edge = minmax(a, b);
        ensuref(edges.insert(edge).second,
                "multiple edge at edge index %d: (%d, %d)", i, a, b);
        dsu.unite(a, b);
    }

    int root = dsu.find(1);
    for (int v = 2; v <= n; ++v) {
        ensuref(dsu.find(v) == root, "communications graph is not connected");
    }

    inf.readEof();
}
