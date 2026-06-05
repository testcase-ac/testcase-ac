#include "testlib.h"

#include <numeric>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct Dsu {
    vector<int> parent;
    vector<int> size;

    explicit Dsu(int n) : parent(n + 1), size(n + 1, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        while (parent[x] != x) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
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
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "m");
    inf.readEoln();

    string breeds = inf.readToken("[GH]{1,100000}", "breeds");
    ensuref(static_cast<int>(breeds.size()) == n, "breed string length is %d, expected %d",
            static_cast<int>(breeds.size()), n);
    inf.readEoln();

    Dsu dsu(n);
    set<pair<int, int>> edges;
    for (int i = 1; i <= n - 1; ++i) {
        int x = inf.readInt(1, n, "x");
        inf.readSpace();
        int y = inf.readInt(1, n, "y");
        inf.readEoln();

        ensuref(x != y, "road %d has equal endpoints: %d", i, x);
        pair<int, int> edge = minmax(x, y);
        ensuref(edges.insert(edge).second, "duplicate road %d: (%d, %d)", i, x, y);
        ensuref(dsu.unite(x, y), "road %d creates a cycle: (%d, %d)", i, x, y);
    }

    int root = dsu.find(1);
    for (int i = 2; i <= n; ++i) {
        ensuref(dsu.find(i) == root, "farms are not connected; farm %d is separate", i);
    }

    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readSpace();
        inf.readToken("[GH]", "c");
        inf.readEoln();
        (void)a;
        (void)b;
    }

    inf.readEof();
}
