#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

class Dsu {
public:
    explicit Dsu(int n) : parent(n + 1), size(n + 1, 1) {
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

    int n = inf.readInt(2, 100000, "N");
    inf.readEoln();

    Dsu dsu(n);
    set<pair<int, int>> edges;
    for (int i = 1; i <= n - 1; ++i) {
        int a = inf.readInt(1, n, "A");
        inf.readSpace();
        int b = inf.readInt(1, n, "B");
        inf.readSpace();
        int v = inf.readInt(1, 1000, "V");
        inf.readEoln();

        ensuref(a != b, "edge %d is a self-loop at room %d", i, a);

        pair<int, int> edge = minmax(a, b);
        ensuref(edges.insert(edge).second,
                "edge %d duplicates rooms %d and %d", i, edge.first, edge.second);
        ensuref(dsu.unite(a, b), "edge %d creates a cycle between %d and %d", i, a, b);
    }

    int root = dsu.find(1);
    for (int room = 2; room <= n; ++room) {
        ensuref(dsu.find(room) == root, "room %d is not connected to room 1", room);
    }

    inf.readEof();
}
