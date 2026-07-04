#include "testlib.h"
#include <numeric>
#include <set>
#include <utility>
#include <vector>
using namespace std;

class DSU {
public:
    explicit DSU(int n) : parent(n + 1), size(n + 1, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
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
        return true;
    }

private:
    vector<int> parent;
    vector<int> size;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2500, "N");
    inf.readSpace();
    int m = inf.readInt(1, 2500, "M");
    inf.readEoln();

    DSU dsu(n);
    set<pair<int, int>> edges;
    for (int i = 1; i <= n - 1; ++i) {
        int x = inf.readInt(1, n, "x");
        inf.readSpace();
        int y = inf.readInt(1, n, "y");
        inf.readSpace();
        inf.readInt(1, 10000, "l");
        inf.readEoln();

        ensuref(x != y, "self-loop at edge %d: %d", i, x);
        pair<int, int> edge = minmax(x, y);
        ensuref(edges.insert(edge).second, "duplicate edge at edge %d: %d %d", i, x, y);
        ensuref(dsu.unite(x, y), "cycle introduced at edge %d: %d %d", i, x, y);
    }

    int root = dsu.find(1);
    for (int v = 2; v <= n; ++v) {
        ensuref(dsu.find(v) == root, "tree is disconnected: vertex %d is not connected to 1", v);
    }

    inf.readEof();
}
