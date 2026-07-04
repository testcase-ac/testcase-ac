#include "testlib.h"

#include <numeric>
#include <vector>
using namespace std;

struct DSU {
    vector<int> parent;
    vector<int> size;

    explicit DSU(int n) : parent(n + 1), size(n + 1, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (size[a] < size[b]) swap(a, b);
        parent[b] = a;
        size[a] += size[b];
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int k = inf.readInt(1, 1000, "k");
    inf.readSpace();
    int m = inf.readInt(1, 30000, "m");
    inf.readEoln();

    for (int i = 1; i <= k; ++i) {
        inf.readInt(1, n, "restaurant_city");
        inf.readEoln();
    }

    DSU dsu(n);
    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readSpace();
        inf.readInt(1, 1000, "d");
        inf.readEoln();

        ensuref(a != b, "loop at highway %d: %d %d", i, a, b);
        dsu.unite(a, b);
    }

    int root = dsu.find(1);
    for (int city = 2; city <= n; ++city) {
        ensuref(dsu.find(city) == root, "city %d is not connected to city 1", city);
    }

    inf.readEof();
}
